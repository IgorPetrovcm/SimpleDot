# ifndef HOST_
# define HOST_

# include "SettingHost.h"
# include "EnvironmentManager.h"
# include "Logging.h"

typedef struct {
    char pathToAppSettingsFile[426];
    AppSettings* appSettings;
    SettingHost* settingHost;
    Logging* logging;
    EnvironmentManager* envMngr;
} Host;

Host* constructor_host();

# endif