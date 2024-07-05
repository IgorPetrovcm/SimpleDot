# include "AppSettings.h"
# include "LoggingSettings.h"

AppSettings constructor_app_settings()
{
    AppSettings appSettings;

    appSettings.loggingSettings = constructor_logging_settings();

    return appSettings;
}