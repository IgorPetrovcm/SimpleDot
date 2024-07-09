# include "../Application/EnvironmentManager.h"
# include "../Model/AppSettings.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

char* const logging_modes[3] = { SMD_LOGGING_ERROR, SMD_LOGGING_INFO, SMD_LOGGING_WARNING };


EnvironmentManager constructor_environment_manager(AppSettings* appSettings, char* pathToAppSettingsFile)
{
    EnvironmentManager envMngr;

    envMngr.appSettings = appSettings;
    envMngr.pathToAppSettingsFile = pathToAppSettingsFile;

    envMngr.print_appsetting_to_buffer = print_appsetting_to_buffer;
    envMngr.print_variables_to_buffer = print_variables_to_buffer;
    envMngr.push_settings_from_file = push_settings_from_file;
    envMngr.get_logging_variable = get_logging_variable;
    envMngr.print_settings_to_file = print_settings_to_file;

    return envMngr;
}

int print_appsetting_to_buffer(char* buffer, char* name, char* value)
{
    if (sprintf(buffer, "%s=%s", name, value) < 0){
        return -1;
    }

    strcat(buffer, "\0");

    return 0;
}

int print_variables_to_buffer(void* self, char* buffer, char delimiter)
{
    if (self == NULL){
        return -1;
    }

    EnvironmentManager* envMngr = (EnvironmentManager*)self;

    int variablesCount = 3;
    char* variables[3] = { 
        envMngr->appSettings->loggingSettings.error, 
        envMngr->appSettings->loggingSettings.info,
        envMngr->appSettings->loggingSettings.warning
        };

    for (int i = 0; i < variablesCount; i++){
        char bufferSetting[256];
        envMngr->print_appsetting_to_buffer(bufferSetting, logging_modes[i], variables[i]);
        strcat(buffer, bufferSetting);
        strcat(buffer, &delimiter);
    }
    
    return 0;
}

int print_settings_to_file(void *self)
{
    errno = 0;
    int errNum;

    EnvironmentManager* envMngr = (EnvironmentManager*)self; 

    char settings[2048];
    print_variables_to_buffer(envMngr, settings, '\n');

    FILE* appSettingsFile = fopen(envMngr->pathToAppSettingsFile, "w+");

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

        printf("%s", envValue);

        // char* penvValue = envValue;
        // while ((strchr(penvValue, '\n') != NULL)){
        //     penvValue++;
        // }
        // *penvValue = ' ';

        setenv(envName, envValue, 1);
    }

    printf("%s", getenv(SMD_LOGGING_ERROR));
    printf("BYE");

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