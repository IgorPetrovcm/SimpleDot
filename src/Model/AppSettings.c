# include "AppSettings.h"
# include "LoggingSettings.h"
# include <stdlib.h>

AppSettings* constructor_app_settings()
{
    AppSettings* appSettings = (AppSettings*)malloc(sizeof(AppSettings));

    appSettings->loggingSettings = constructor_logging_settings();

    return appSettings;
}