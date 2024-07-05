# include "../Application/HostConfig.h"
# include "../Application/SettingHostConfig.h"
# include "../Application/Mapping.h"
# include "../Application/EnvironmentManager.h"
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
    EnvironmentManager envMngr = constructor_environment_manager(mapping);

    HostConfig hostConfig;

    hostConfig.settingHost = settingHost;
    hostConfig.mapping = mapping;
    hostConfig.envMngr = envMngr;
    hostConfig.pathToAppSettingsFile = settingHost.set_appsettings_file(&settingHost);
    hostConfig.appSettings = constructor_app_settings();

    hostConfig.write_default_settings_to_file = write_default_settings_to_file;

    return hostConfig;
}

int write_default_settings_to_file(void *self)
{
    errno = 0;
    int errNum;

    HostConfig* host = (HostConfig*)self;

    AppSettings* appSettings = &host->appSettings;

    char* settings = host->envMngr.get_variables(&host->envMngr, appSettings);

    FILE* appSettingsFile = fopen(host->pathToAppSettingsFile, "w+");

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
