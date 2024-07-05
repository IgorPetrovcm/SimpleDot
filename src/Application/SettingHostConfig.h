# ifndef SETTING_HOST_CONFIG
# define SETTING_HOST_CONFIG

# define APPSET_NAME "appsettings.env"

typedef struct {
    char* appSettingsDirectoryName;
    char* (*set_appsettings_file)(void*);
} SettingHostConfig;

char* set_appsettings_file(void* self);

SettingHostConfig constructor_setting_host_config();

# endif