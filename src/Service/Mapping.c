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

char* get_appsetting_string(int mode, char* value, char* environmentVariable)
{
    size_t appSettingStrSize = 0;

    appSettingStrSize += strlen(environmentVariable);
    appSettingStrSize += sizeof("=");
    appSettingStrSize += strlen(value);
    if (mode == WITH_N){
        appSettingStrSize += sizeof("\n");
    }
    appSettingStrSize += sizeof("\0");

    char* appSettingStr = malloc(appSettingStrSize);

    strcat(appSettingStr, environmentVariable);
    strcat(appSettingStr, "=");
    strcat(appSettingStr, value);
    if (mode == WITH_N){
        strcat(appSettingStr, "\n");
    }
    strcat(appSettingStr, "\0");

    return appSettingStr;
}