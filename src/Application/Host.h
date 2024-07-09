# ifndef HOST_
# define HOST_

# include "SettingHost.h"
# include "EnvironmentManager.h"
# include "Logging.h"
# include "../Model/AppSettings.h"

typedef struct {
    char* pathToAppSettingsFile;
    AppSettings* appSettings;
    SettingHost* settingHost;
    Logging* logging;
    EnvironmentManager* envMngr;
} Host;

Host* constructor_host();

# endif