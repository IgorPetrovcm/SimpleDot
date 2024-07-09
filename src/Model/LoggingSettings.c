# include "LoggingSettings.h"
# include <stdlib.h>

LoggingSettings* constructor_logging_settings()
{
    LoggingSettings* loggingSettings = (LoggingSettings*)malloc(sizeof(LoggingSettings));

    loggingSettings->error = "Error from";
    loggingSettings->info = "Info from";
    loggingSettings->warning = "Warning from";

    return loggingSettings;
}