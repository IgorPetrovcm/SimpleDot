# include "../Application/SourceParser.h"
# include "../Application/Logging.h"
# include <stdlib.h>
# include <stdarg.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

SourceParser* constructor_source_parser(char *sources, Logging* logging)
{
    SourceParser* sourceParser = (SourceParser*)malloc(sizeof(SourceParser));

    sourceParser->logging = logging;
    sourceParser->sources = sources;

    sourceParser->get_dir_by_matches = get_dir_by_matches;
    // sourceParser->get_directory_names = get_directory_names;

    return sourceParser;
}

int get_dir_by_matches(void* self, char** pathToMatch, int matchesCount, ...)
{
    errno = 0;
    int errNum;
    
    SourceParser* sourceParser = (SourceParser*)self;

    char** argvs = malloc(matchesCount * sizeof(char*));
    for (int i = 0; i < matchesCount; i++){
        argvs[i] = malloc(256);
    }

    va_list ap;

    va_start(ap, matchesCount);
    for (int i = 0; i < matchesCount; i++){
        argvs[i] = va_arg(ap, char*);
    }
    va_end(ap);

    if ((errNum = errno) != 0){
        sourceParser->logging->log(LOG_ERR, strerror(errNum), __FILE__, __LINE__, __TIME__);
        return -1;
    }

    struct dirent* dirEntity;

    DIR* sourceDirectory = opendir(sourceParser->sources);

    if ((errNum = errno) != 0){
        sourceParser->logging->log(LOG_ERR, strerror(errNum), __FILE__, __LINE__, __TIME__);
        return -1;
    }

    int signal = -1;

    int i = 0;

    while ((dirEntity = readdir(sourceDirectory)) != NULL){
        if (dirEntity->d_type != DT_DIR || strcmp(dirEntity->d_name, ".") == 0 || strcmp(dirEntity->d_name, "..") == 0){
            continue;
        }
        for (int j = 0; j < matchesCount; j++){
            if (strcmp(dirEntity->d_name, argvs[j]) == 0){
                signal = 0;
                break;
            }
        }
        if (signal == 0){
            char* matchDir = malloc(256);

            strcpy(matchDir,sourceParser->sources);
            strcat(matchDir, "/");
            strcat(matchDir, dirEntity->d_name);

            strcpy(*pathToMatch, matchDir);

            return 0;
        }
    }

    *pathToMatch = NULL;

    return 0;
}

// ##########################################################################################################################
// ###                                                                                                                    ###
// ###                                            doesn't work yet                                                        ###
// ###                                                                                                                    ###
// ##########################################################################################################################

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// char** get_directory_names(void* self, int* count)
// {
//     errno = 0;
//     int errNum;

//     SourceParser* sourceParser = (SourceParser*)self;

//     DIR* sourceDirectory = opendir(sourceParser->sources);

//     if ((errNum = errno) != 0){
//         char* errBuffer = strerror(errNum);
//         sourceParser->logging->log(LOG_ERR, errBuffer, __FILE__, __LINE__, __TIME__);
//         return NULL;
//     }

//     struct dirent* fd;

//     char** result = malloc(1024 * sizeof(char*));
//     for (int i = 0; i < 256; i++){
//         result[i] = malloc(256 * sizeof(char));
//     }

//     int i = 0;
//     while ((fd = readdir(sourceDirectory)) != NULL){
//         if (fd->d_type != DT_DIR){
//             continue;
//         }
//         if (strcmp(fd->d_name, ".config") == 0 || strcmp(fd->d_name, "config") == 0 || strcmp(fd->d_name, "configs") == 0){
//             DIR* configDirectory = opendir(fd->d_name);

//             if ((errNum = errno) != 0){
//                 char* errBuffer = strerror(errNum);
//                 sourceParser->logging->log(LOG_ERR, errBuffer, __FILE__, __LINE__, __TIME__);
//                 return NULL;
//             }

//             struct dirent* fdFromConfigs;
//             int j = 0;
//             while ((fdFromConfigs = readdir(configDirectory)) != NULL){
//                 if (fdFromConfigs->d_type != DT_DIR){
//                     continue;
//                 }
//                 result[j] = fdFromConfigs->d_name;

//                 j++;
//                 *count += 1;
//             }
//         }
//         i++;
//     }

//     if ((errNum = errno) != 0){
//         char* errBuffer = strerror(errNum);
//         sourceParser->logging->log(LOG_ERR, errBuffer, __FILE__, __LINE__, __TIME__);
//         return NULL;
//     }

//     return result;
// }