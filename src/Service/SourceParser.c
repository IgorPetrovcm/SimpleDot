# include "../Application/SourceParser.h"
# include "../Application/Logging.h"
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

SourceParser* constructor_source_parser(char *sources, Logging* logging)
{
    SourceParser* sourceParser = (SourceParser*)malloc(sizeof(SourceParser));

    sourceParser->logging = logging;
    sourceParser->sources = sources;

    sourceParser->get_directory_names = get_directory_names;

    return sourceParser;
}

char** get_directory_names(void* self, int* count)
{
    errno = 0;
    int errNum;

    SourceParser* sourceParser = (SourceParser*)self;

    DIR* sourceDirectory = opendir(sourceParser->sources);

    if ((errNum = errno) != 0){
        char* errBuffer = strerror(errNum);
        sourceParser->logging->log(LOG_ERR, errBuffer, __FILE__, __LINE__, __TIME__);
        return NULL;
    }

    struct dirent* fd;

    char** result = malloc(1024 * sizeof(char*));
    for (int i = 0; i < 256; i++){
        result[i] = malloc(256 * sizeof(char));
    }

    int i = 0;
    while ((fd = readdir(sourceDirectory)) != NULL){
        if (fd->d_type != DT_DIR){
            continue;
        }
        result[i] = fd->d_name;
        *count += 1;
        i++;
    }

    if ((errNum = errno) != 0){
        char* errBuffer = strerror(errNum);
        sourceParser->logging->log(LOG_ERR, errBuffer, __FILE__, __LINE__, __TIME__);
        return NULL;
    }

    return result;
}