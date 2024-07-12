# include "../Application/NetworkWorker.h"
# include "../Application/Logging.h"
# include <curl/curl.h>
# include <stdlib.h>
# include <stdio.h>
# include <curl/curl.h>
# include <errno.h>
# include <string.h>
# include <zip.h>

NetworkWorker* constructor_network_worker(Logging* logging)
{
    NetworkWorker* nw = (NetworkWorker*)malloc(sizeof(NetworkWorker));

    nw->logging = logging;

    nw->get_archive_from_remote_repo = get_archive_from_remote_repo;
    nw->write_file = write_file;

    return nw;
}

size_t write_file(void* ptr, size_t size, size_t nmemb, void* stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);

    return written;
}

int get_archive_from_remote_repo(void* self, char* url)
{
    errno = 0;
    int errNum;
    
    NetworkWorker* nw = (NetworkWorker*)self;

    CURL* handle;

    FILE* archive;
    
    char filename[406];
    sprintf(filename, "%s/.simpledot/dotfiles.zip", getenv("HOME"));

    char errorBuffer[1048];

    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, nw->write_file);

    // curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorBuffer);

    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);

    archive = fopen(filename, "wb");

    if (archive == NULL){
        errNum = errno;
        char* strerrorBuffer = strerror(errNum);
        nw->logging->log(LOG_ERR, strerrorBuffer, __FILE__, __LINE__, __TIME__);
        return -1;
    }

    curl_easy_setopt(handle, CURLOPT_WRITEDATA, archive);

    CURLcode result;
    result = curl_easy_perform(handle);

    if (result != 0){
        nw->logging->log(LOG_ERR, errorBuffer, __FILE__, __LINE__, __TIME__);
        return -1;
    }

    fclose(archive);

    curl_easy_cleanup(handle);

    return 0;
}