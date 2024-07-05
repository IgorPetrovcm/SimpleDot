# include "LoggingSettings.h"

LoggingSettings constructor_logging_settings()
{
    LoggingSettings loggingSettings;

    loggingSettings.error = "Error from";
    loggingSettings.info = "Info from";
    loggingSettings.warning = "Warning from";

    return loggingSettings;
}