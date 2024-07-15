# ifndef SOURCE_PARSER
# define SOURCE_PARSER

# include "Logging.h"
# include <dirent.h>

typedef struct {
    char* sources;

    Logging* logging;

    int (*get_dir_by_matches)(void* self, char** pathToMatch, int matchesCount, ...);
    int (*get_directory_names)(void* self, char*** names, int namesc, int* count);
} SourceParser;

int get_dir_by_matches(void* self, char** pathToMatch, int matchesCount, ...);

int get_directory_names(void* self, char*** names, int namesc, int* count);

SourceParser* constructor_source_parser(char* sources, Logging* logging);

# endif