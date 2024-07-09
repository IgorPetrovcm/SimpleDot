# include "../Application/Host.h"
# include "../Application/SettingHost.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/ProcessesManager.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

Host* constructor_host()
{
    Host* host = (Host*)malloc(sizeof(Host));

    SettingHost* settingHost = constructor_setting_host();

    char appSettingsDirectory[256];
    sprintf(appSettingsDirectory, "%s/.simpledot/", getenv("HOME"));

    char appSettingsFileName[256];
    strcpy(appSettingsFileName, "appsettings.env");

    if (settingHost->set_appsettings_file(host->pathToAppSettingsFile, appSettingsDirectory, appSettingsFileName) < 0){
        exit(-1);
    }

    host->envMngr = constructor_environment_manager(host->pathToAppSettingsFile);
    host->processesManager = constructor_processes_manager();
    host->settingHost = settingHost;

    return host;
}
