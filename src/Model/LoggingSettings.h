# ifndef LOGGING_SETTINGS
# define LOGGING_SETTINGS

typedef struct {
    char* error;
    char* info;
    char* warning;
} LoggingSettings;

LoggingSettings* constructor_logging_settings();

# endif