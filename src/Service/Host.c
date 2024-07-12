# include "../Application/Host.h"
# include "../Application/SettingHost.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/ProcessesManager.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

Host* constructor_host()
{
    Host* host = (Host*)malloc(sizeof(Host));

    SettingHost* settingHost = constructor_setting_host();

    char* baseFolderName = malloc(256);
    strcpy(baseFolderName, getenv("HOME"));
    strcat(baseFolderName, "/.simpledot/");

    char* appSettingsFileName = "appsettings.env";

    char* dotFilesFileName = "dotfiles";

    if (settingHost->set_appsettings_file(host->pathToAppSettingsFile, baseFolderName, appSettingsFileName) < 0){
        exit(-1);
    }

    host->envMngr = constructor_environment_manager(baseFolderName, appSettingsFileName, dotFilesFileName);
    host->processesManager = constructor_processes_manager();
    host->settingHost = settingHost;

    return host;
}
