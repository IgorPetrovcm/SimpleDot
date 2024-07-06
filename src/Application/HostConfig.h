# ifndef HOST_CONFIG
# define HOST_CONFIG

# include "SettingHostConfig.h"
# include "Mapping.h"
# include "EnvironmentManager.h"
# include "../Model/AppSettings.h"

typedef struct {
    char* pathToAppSettingsFile;
    AppSettings appSettings;
    SettingHostConfig settingHost;
    Mapping mapping;
    EnvironmentManager envMngr;
} HostConfig;

HostConfig constructor_host_config();

# endif