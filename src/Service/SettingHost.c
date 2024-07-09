# include "../Application/SettingHost.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>

SettingHost* constructor_setting_host()
{
    SettingHost* settingHost = (SettingHost*)malloc(sizeof(SettingHost));

    settingHost->set_appsettings_file = set_appsettings_file;

    return settingHost;
}

int set_appsettings_file(char* buffer, char* appSettingsDirectory, char* appSettingsFileName)
{
    errno = 0;
    int errNum;

    if (access(appSettingsDirectory, F_OK) != 0){
        mkdir(appSettingsDirectory, 0777);
    }

    strcpy(buffer, appSettingsDirectory);
    strcat(buffer, appSettingsFileName);

    FILE* appSettingsFileRead = fopen(buffer, "r");
    if (appSettingsFileRead == NULL){
        errno = 0;
        FILE* appSettingsFile = fopen(buffer, "w");
        fclose(appSettingsFile);
    }

    if ((errNum = errno) != 0){
        char* buffer = strerror(errNum);
        fprintf(stderr, "%s", buffer);
        return -1;
    }

    return 0;
}