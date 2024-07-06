# include "../Application/EnvironmentManager.h"
# include "../Application/Mapping.h"
# include "../Model/AppSettings.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

char* const logging_modes[3] = { SMD_LOGGING_ERROR, SMD_LOGGING_INFO, SMD_LOGGING_WARNING };


EnvironmentManager constructor_environment_manager(Mapping mapping, ProcessesManager procMngr)
{
    EnvironmentManager envMngr;

    envMngr.mapping = mapping;
    envMngr.procMngr = procMngr;

    envMngr.get_variables = get_variables;
    envMngr.push_settings_from_file = push_settings_from_file;
    envMngr.get_logging_variable = get_logging_variable;
    envMngr.write_default_settings_to_file = write_default_settings_to_file;

    return envMngr;
}

char* get_variables(void* self, AppSettings* appSettings)
{
    EnvironmentManager* envMngr = (EnvironmentManager*)self;

    char* result = malloc(2048);

    char* errorStrDTO = envMngr->mapping.to_dto(appSettings->loggingSettings.error);
    char* infoStrDTO = envMngr->mapping.to_dto(appSettings->loggingSettings.info);
    char* warningStrDTO = envMngr->mapping.to_dto(appSettings->loggingSettings.warning);

    strcpy(result, envMngr->mapping.get_appsetting_string(WITH_N, errorStrDTO, logging_modes[0]));
    strcat(result, envMngr->mapping.get_appsetting_string(WITH_N, infoStrDTO, logging_modes[1]));
    strcat(result, envMngr->mapping.get_appsetting_string(WITH_N, warningStrDTO, logging_modes[2]));
    
    return result;
}

int write_default_settings_to_file(void *self, AppSettings* appSettings, char* pathToAppSettingsFile)
{
    errno = 0;
    int errNum;

    EnvironmentManager* envMngr = (EnvironmentManager*)self; 

    char* settings = envMngr->get_variables(envMngr, appSettings);

    FILE* appSettingsFile = fopen(pathToAppSettingsFile, "w+");

    if ((errNum = errno) != 0){
        return errNum;
    }

    fwrite(settings, sizeof(char), strlen(settings), appSettingsFile);

    if ((errNum = errno) != 0){
        char* buffer = strerror(errNum);
        fprintf(stderr, "%s", buffer);
    }

    fclose(appSettingsFile);

    return 0;
}

int push_settings_from_file(char* pathToAppSettingsFile)
{
    errno = 0;
    int errNum;

    char lineBuffer[256];

    FILE* appSettingsFile = fopen(pathToAppSettingsFile, "r");

    if ((errNum = errno) != 0){
        char* errStr = strerror(errNum);
        fprintf(stderr, "%s", errStr);
    }


    while (fgets(lineBuffer, sizeof(lineBuffer), appSettingsFile) != NULL){
        char* delim = "=";
        char* envName = strtok(lineBuffer, delim);
        char* envValue = strtok(NULL, delim);

        setenv(envName, envValue, 1);
    }

    if ((errNum = errno) != 0){
        char* errStr = strerror(errNum);
        fprintf(stderr, "%s", errStr);
    }

    fclose(appSettingsFile);
}

char* get_logging_variable(int mode)
{
    return getenv(logging_modes[mode]);
}