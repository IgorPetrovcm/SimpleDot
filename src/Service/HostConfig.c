# include "../Application/HostConfig.h"
# include "../Application/SettingHostConfig.h"
# include "../Application/Mapping.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/ProcessesManager.h"
# include "../Model/AppSettings.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>

HostConfig constructor_host_config()
{
    SettingHostConfig settingHost = constructor_setting_host_config();
    Mapping mapping = constructor_mapping();
    ProcessesManager procMngr = constructor_processes_manager();
    EnvironmentManager envMngr = constructor_environment_manager(mapping, procMngr);

    HostConfig hostConfig;

    hostConfig.settingHost = settingHost;
    hostConfig.mapping = mapping;
    hostConfig.envMngr = envMngr;
    hostConfig.pathToAppSettingsFile = settingHost.set_appsettings_file(&settingHost);
    hostConfig.appSettings = constructor_app_settings();

    return hostConfig;
}
