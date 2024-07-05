# include "../Application/Mapping.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>

Mapping constructor_mapping()
{
    Mapping mapping;

    mapping.to_dto = to_dto;
    mapping.get_appsetting_string = get_appsetting_string;

    return mapping;
}

char* to_dto(char* value)
{
    size_t resultSize = 0;

    resultSize += strlen(value) + (2 * sizeof("\"")) + sizeof("\0");

    char* result = malloc(resultSize);

    strcat(result, "\"");
    strcat(result, value);
    strcat(result, "\"\0");

    return result;
}

char* get_appsetting_string(int mode, char* value, int argc, ...)
{
    size_t appSettingStrSize = 0;
    va_list ap;

    va_start(ap, argc);
    for (int i = 0; i < argc; i++){
        appSettingStrSize += strlen(va_arg(ap, char*));
    }
    va_end(ap);

    appSettingStrSize += sizeof("=");
    appSettingStrSize += strlen(value);
    if (mode == WITH_N){
        appSettingStrSize += sizeof("\n");
    }
    appSettingStrSize += sizeof("\0");

    char* appSettingStr = malloc(appSettingStrSize);

    va_start(ap, argc);
    for (int i = 0; i < argc; i++){
        strcat(appSettingStr, va_arg(ap, char*));
    }
    va_end(ap);

    strcat(appSettingStr, "=");
    strcat(appSettingStr, value);
    if (mode == WITH_N){
        strcat(appSettingStr, "\n");
    }
    strcat(appSettingStr, "\0");

    return appSettingStr;
}