# ifndef HOST_
# define HOST_

# include "SettingHost.h"
# include "EnvironmentManager.h"
# include "Logging.h"
# include "ProcessesManager.h"

typedef struct {
    char pathToAppSettingsFile[426];
    ProcessesManager* processesManager;
    AppSettings* appSettings;
    SettingHost* settingHost;
    Logging* logging;
    EnvironmentManager* envMngr;
} Host;

Host* constructor_host();

# endif