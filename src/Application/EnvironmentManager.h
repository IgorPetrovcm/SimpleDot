# ifndef ENVIRONMENT_MANAGER
# define ENVIRONMENT_MANAGER

# include "../Model/AppSettings.h"

# define SMD_LOGGING_ERROR "SIMPLEDOT_LOGGING_ERROR"
# define SMD_LOGGING_INFO "SIMPLEDOT_LOGGING_INFO"
# define SMD_LOGGING_WARNING "SIMPLEDOT_LOGGING_WARNING"

# define LOGGING_ERROR_MODE 0
# define LOGGING_INFO_MODE 1
# define LOGGING_WARNING_MODE 2

typedef struct {
    AppSettings* appSettings;
    char* baseFolderName;
    char* appSettingsFileName;
    char* dotFilesFileName;

    int (*write_full_path)(void* self, char* buffer, char* fileName);
    int (*print_appsetting_to_buffer)(char* buffer, char* name, char* value);
    int (*print_variables_to_buffer)(void* self, char* buffer, char* delimiter);
    int (*push_settings_from_file)(void* self);
    char* (*get_logging_variable)(int);
    int (*print_settings_to_file)(void*);
} EnvironmentManager;

int write_full_path(void* self, char* buffer, char* fileName);

int print_appsetting_to_buffer(char* buffer, char* name, char* value);

int print_variables_to_buffer(void* self, char* buffer, char* delimiter);

int push_settings_from_file(void* self);

char* get_logging_variable(int mode);

int print_settings_to_file(void* self);

EnvironmentManager* constructor_environment_manager(char* baseFolderName, char* appSettingsFileName, char* dotFilesFileName);

# endif