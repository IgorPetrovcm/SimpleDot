# include "../Application/Host.h"
# include "../Application/SettingHost.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/ProcessesManager.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>

Host* constructor_host()
{
    Host* host = (Host*)malloc(sizeof(Host));

    SettingHost* settingHost = constructor_setting_host();

    char appSettingsDirectory[256];
    sprintf(appSettingsDirectory, "%s", getenv("HOME"));

    char appSettingsFileName[256];
    sprintf(appSettingsFileName, "%s", "appsettings");

    host->pathToAppSettingsFile = malloc(256);

    if (settingHost->set_appsettings_file(host->pathToAppSettingsFile, appSettingsDirectory, appSettingsFileName) < 0){
        exit(-1);
    }

    host->envMngr = constructor_environment_manager(host->pathToAppSettingsFile);
    host->processesManager = constructor_processes_manager();
    host->settingHost = settingHost;

    return host;
}
