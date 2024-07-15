# include "matches.h"
# include <stdarg.h>
# include <string.h>

int is_match(char* str, int count, ...)
{
    va_list ap;

    va_start(ap, count);

    int match = -1;
    for (int i = 0; i < count; i++){
        if (strcmp(str, va_arg(ap, char*)) == 0){
            match++;
        }

        if (match == 0){
            break;
        }
    }

    return match;
}