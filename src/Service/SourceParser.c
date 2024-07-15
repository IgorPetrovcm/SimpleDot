# include "../Application/SourceParser.h"
# include "../Application/Logging.h"
# include "../Bottom/matches.h"
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
    sourceParser->get_directory_names = get_directory_names;

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

int get_directory_names(void* self, char*** names, int namesc, int* count)
{
    errno = 0;
    int errNum;

    SourceParser* sourceParser = (SourceParser*)self;

    char** pathToDotfiles = malloc(sizeof(char*));
    *pathToDotfiles = malloc(256);

    sourceParser->get_dir_by_matches(sourceParser, pathToDotfiles, 3, "config", ".config", "configs");

    if (*pathToDotfiles == NULL){
        sourceParser->logging->log(LOG_ERR, "Directory for dotfiles not found", __FILE__, __LINE__, __TIME__);
        sourceParser->logging->log(LOG_HINT, "The directory you specified \
         should contain a directory with dotfiles. \
         Available directory names with dotfiles: \"config\", \".config\", \"configs\".",
         __FILE__, __LINE__, __TIME__);

         return -1;
    }

    struct dirent* dirEntity;

    for (int i = 0; i < 1024; i++){
        names[i] = malloc(sizeof(char*));
    }
    for (int i = 0; i < 1024; i++){
        *names[i] = malloc(256 * sizeof(char));
    }

    DIR* dotfiles = opendir(*pathToDotfiles);

    if ((errNum = errno) != 0){
        return errNum;
    }

    int i = 0;
    while ((dirEntity = readdir(dotfiles)) != NULL){
        char* entName = dirEntity->d_name;
        unsigned char entType = dirEntity->d_type;
        if (entType != DT_DIR || is_match(entName, 2, ".", "..") == 0){
            continue;
        }

        *names[i] = dirEntity->d_name;

        *count += 1;
        
        i++;
    }

    if (*count == 0){
        *names = NULL; 
    }

    return 0;
}