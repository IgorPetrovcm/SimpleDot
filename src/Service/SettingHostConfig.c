# include "../Application/SettingHostConfig.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>

SettingHostConfig constructor_setting_host_config()
{
    SettingHostConfig settingHost;

    settingHost.set_appsettings_file = set_appsettings_file;

    char* appSettingsDirectoryName = getenv("HOME");
    strcat(appSettingsDirectoryName, "/.simpledot\0");

    settingHost.appSettingsDirectoryName = appSettingsDirectoryName;

    return settingHost;
}

char* set_appsettings_file(void* self)
{
    errno = 0;
    int errNum;

    SettingHostConfig* settingHost = (SettingHostConfig*)self;
    
    char* appSettingsFileName = malloc(127);
    strcat(appSettingsFileName, settingHost->appSettingsDirectoryName);
    strcat(appSettingsFileName, "/");
    strcat(appSettingsFileName, APPSET_NAME);
    strcat(appSettingsFileName, "\0");

    if (access(settingHost->appSettingsDirectoryName, F_OK) != 0){
        mkdir(settingHost->appSettingsDirectoryName, 0777);
    }
    FILE* appSettingsFile = fopen(appSettingsFileName, "a");
    fclose(appSettingsFile);

    if ((errNum = errno) != 0){
        /*
        * Need to log
        */
        char* buffer = strerror(errNum);
        fprintf(stderr, "%s", buffer);
    }

    return appSettingsFileName;
}