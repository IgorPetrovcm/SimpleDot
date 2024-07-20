# include "../Application/ArchiveWorker.h"
# include "../Application/Logging.h"
#include <bits/getopt_core.h>
# include <smdbottom/fullstrs.h>
# include <curl/curl.h>
# include <stdlib.h>
# include <stdio.h>
# include <curl/curl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

ArchiveWorker* constructor_archive_worker(Logging* logging, EnvironmentManager* envMngr)
{
    ArchiveWorker* aw = (ArchiveWorker*)malloc(sizeof(ArchiveWorker));

    aw->logging = logging;
    aw->envMngr = envMngr;

    aw->extract_archive = extract_archive;
    aw->get_remote_archive = get_remote_archive;
    aw->write_file = write_file;

    return aw;
}

int extract_archive(void* self, char* archivePath)
{
    errno = 0;
    int errNum;

    ArchiveWorker* aw = self;

    char*  outDir = malloc(500 * sizeof(char));
    aw->envMngr->write_full_path(aw->envMngr, outDir, aw->envMngr->dotFilesDirName);

    char* buffer = malloc(2048 * sizeof(char));
    char* options = malloc(256 * sizeof(char));

    if ((errNum = lbufferadder(options, 4, "tar -zxf ", archivePath, " -C ", aw->envMngr->baseFolderPath)) != 0){
        buffer = strerror(errNum);
        aw->logging->log(LOG_ERR, buffer, __FILE__, __LINE__, __TIME__);
        return -1;
    }

    if (system(options) != 0){
        return -1;
    }
    
    return 0;
}


size_t write_file(void* ptr, size_t size, size_t nmemb, void* stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);

    return written;
}

int get_remote_archive(void* self, char* url)
{
    errno = 0;
    int errNum;
    
    ArchiveWorker* aw = (ArchiveWorker*)self;

    CURL* handle;

    FILE* archive;

    char* temp = qlastchars(url, '.');

    char* archiveExtension = malloc(12);

    if (strcmp(temp, "zip") == 0){
        archiveExtension = ".zip";
    }
    else {
        archiveExtension = ".tar.gz";
    }
    
    char archivePath[406];
    aw->envMngr->write_full_path(aw->envMngr, archivePath, aw->envMngr->dotFilesDirName);

    strcat(archivePath, archiveExtension);

    char errorBuffer[1048];

    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, aw->write_file);

    curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorBuffer);

    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);

    archive = fopen(archivePath, "wb");

    if (archive == NULL){
        errNum = errno;
        char* strerrorBuffer = strerror(errNum);
        aw->logging->log(LOG_ERR, strerrorBuffer, __FILE__, __LINE__, __TIME__);
        return -1;
    }

    curl_easy_setopt(handle, CURLOPT_WRITEDATA, archive);

    CURLcode result;
    result = curl_easy_perform(handle);

    if (result != 0){
        aw->logging->log(LOG_ERR, errorBuffer, __FILE__, __LINE__, __TIME__);
        return -1;
    }

    curl_easy_cleanup(handle);

    fclose(archive);

    aw->extract_archive(aw, archivePath);

    return 0;
}

