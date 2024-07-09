# include "../Application/Host.h"
# include "../Application/SettingHost.h"
# include "../Application/Logging.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/ProcessesManager.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>

Host* constructor_host_config()
{
    Host* host = (Host*)malloc(sizeof(Host));

    SettingHost* settingHost = constructor_setting_host();

    char appSettingsDirectory[256];
    sprintf(appSettingsDirectory, "%s", getenv("HOME"));

    char appSettingsFileName[256];
    sprintf(appSettingsFileName, "%s", "appsettings");

    if (settingHost->set_appsettings_file(host->pathToAppSettingsFile, appSettingsDirectory, appSettingsFileName) < 0){
        exit(-1);
    }

    EnvironmentManager* envMngr = constructor_environment_manager(host->pathToAppSettingsFile);

    host->settingHost = settingHost;
    host->envMngr = envMngr;

    return host;
}
