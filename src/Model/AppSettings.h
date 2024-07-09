# ifndef APP_SETTINGS
# define APP_SETTINGS

# include "LoggingSettings.h"

typedef struct{
    LoggingSettings* loggingSettings;
} AppSettings;

AppSettings* constructor_app_settings();

# endif