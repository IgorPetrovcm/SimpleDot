# include "../Application/EnvironmentManager.h"
# include "../Model/AppSettings.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

char* const logging_modes[4] = { SMD_LOGGING_ERROR, SMD_LOGGING_INFO, SMD_LOGGING_WARNING, SMD_LOGGING_HINT };


EnvironmentManager* constructor_environment_manager(char* baseFolderName, char* appSettingsFileName, char* dotFilesFileName)
{
    EnvironmentManager* envMngr = malloc(sizeof(EnvironmentManager));

    envMngr->appSettings = constructor_app_settings();
    envMngr->baseFolderName = baseFolderName;
    int endNameNumber = strlen(envMngr->baseFolderName);

    if (envMngr->baseFolderName[endNameNumber - 1] == '/'){
        envMngr->baseFolderName[endNameNumber - 1] = '\0';
    }

    envMngr->appSettingsFileName = appSettingsFileName;
    envMngr->dotFilesFileName = dotFilesFileName;

    envMngr->write_full_path = write_full_path;
    envMngr->print_appsetting_to_buffer = print_appsetting_to_buffer;
    envMngr->print_variables_to_buffer = print_variables_to_buffer;
    envMngr->push_settings_from_file = push_settings_from_file;
    envMngr->get_logging_variable = get_logging_variable;
    envMngr->print_settings_to_file = print_settings_to_file;

    return envMngr;
}

int write_full_path(void* self, char* buffer, char* fileName)
{
    if (self == NULL){
        return -1;
    }
    
    EnvironmentManager* envMngr = (EnvironmentManager*)self;

    strcpy(buffer, envMngr->baseFolderName);
    strcat(buffer, "/");
    strcat(buffer, fileName);

    return 0;
}

int print_appsetting_to_buffer(char* buffer, char* name, char* value)
{
    if (sprintf(buffer, "%s=%s", name, value) < 0){
        return -1;
    }

    return 0;
}

int print_variables_to_buffer(void* self, char* buffer, char* delimiter)
{
    if (self == NULL){
        return -1;
    }

    EnvironmentManager* envMngr = (EnvironmentManager*)self;

    int variablesCount = 4;
    char* variables[4] = { 
        envMngr->appSettings->loggingSettings->error, 
        envMngr->appSettings->loggingSettings->info,
        envMngr->appSettings->loggingSettings->warning,
        envMngr->appSettings->loggingSettings->hint
        };

    for (int i = 0; i < variablesCount; i++){
        char* bufferSetting = malloc(256);
        envMngr->print_appsetting_to_buffer(bufferSetting, logging_modes[i], variables[i]);

        if (i == 0){
            sprintf(buffer, "%s\n", bufferSetting);
        }
        else{
            strcat(buffer, bufferSetting);
            strcat(buffer, delimiter);
        }

        free(bufferSetting);
    }
    
    return 0;
}

int print_settings_to_file(void *self)
{
    errno = 0;
    int errNum;

    EnvironmentManager* envMngr = (EnvironmentManager*)self; 

    char* settings = malloc(2048);
    envMngr->print_variables_to_buffer(envMngr, settings, "\n");

    char* pathToAppSettingsFile = malloc(1024);
    envMngr->write_full_path(envMngr, pathToAppSettingsFile, envMngr->appSettingsFileName);

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

int push_settings_from_file(void* self)
{
    errno = 0;
    int errNum;

    EnvironmentManager* envMngr = (EnvironmentManager*)self;

    char* pathToAppSettingsFile = malloc(1024);
    envMngr->write_full_path(envMngr, pathToAppSettingsFile, envMngr->appSettingsFileName);

    FILE* appSettingsFile = fopen(pathToAppSettingsFile, "r");

    char lineBuffer[256];

    if ((errNum = errno) != 0){
        char* errStr = strerror(errNum);
        fprintf(stderr, "%s", errStr);
        return -1;
    }

    while (fgets(lineBuffer, sizeof(lineBuffer), appSettingsFile) != NULL){
        char* delim = "=";
        char* envName = strtok(lineBuffer, delim);
        char* envValue = strtok(NULL, delim);

        char* penvValue = envValue;
        while ((strchr(penvValue, '\n') != NULL)){
            penvValue++;
        }
        *(penvValue - 1) = '\0';

        setenv(envName, envValue, 1);
    }

    if ((errNum = errno) != 0){
        char* errStr = strerror(errNum);
        fprintf(stderr, "%s", errStr);
    }

    fclose(appSettingsFile);

    return 0;
}

char* get_logging_variable(int mode)
{
    return getenv(logging_modes[mode]);
}