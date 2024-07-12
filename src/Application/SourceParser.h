# ifndef SOURCE_PARSER
# define SOURCE_PARSER

# include "Logging.h"

typedef struct {
    char* sources;

    Logging* logging;

    char** (*get_directory_names)(void* self, int* count);
} SourceParser;

char** get_directory_names(void* self, int* count);

SourceParser* constructor_source_parser(char* sources, Logging* logging);

# endif