# ifndef ENVIRONMENT_MANAGER
# define ENVIRONMENT_MANAGER

# include "Mapping.h"
# include "ProcessesManager.h"
# include "../Model/AppSettings.h"

# define SMD_LOGGING_ERROR "SIMPLEDOT_LOGGING_ERROR"
# define SMD_LOGGING_INFO "SIMPLEDOT_LOGGING_INFO"
# define SMD_LOGGING_WARNING "SIMPLEDOT_LOGGING_WARNING"

# define LOGGING_ERROR_MODE 0
# define LOGGING_INFO_MODE 1
# define LOGGING_WARNING_MODE 2

typedef struct {
    Mapping mapping;
    ProcessesManager procMngr;
    int outPipe[2];
    int errPipe[2];
    char* (*get_variables)(void*, AppSettings*);
    int (*push_settings_from_file)(char*);
    char* (*get_logging_variable)(int);
    int (*write_default_settings_to_file)(void*, AppSettings*, char*);
} EnvironmentManager;

char* get_variables(void* self, AppSettings* appSettings);

int push_settings_from_file(char* pathToAppSettingsFile);

char* get_logging_variable(int mode);

int write_default_settings_to_file(void* self, AppSettings* appSettings, char* pathToAppSettingsFile);

EnvironmentManager constructor_environment_manager(Mapping mapping, ProcessesManager procMngr);

# endif