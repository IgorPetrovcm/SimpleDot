# ifndef SETTING_HOST_CONFIG
# define SETTING_HOST_CONFIG

# define APPSET_NAME "appsettings.env"

typedef struct {
    int (*set_appsettings_file)(char* buffer, char* appSettingsDirectory, char* appSettingsFileName);
} SettingHost;

int set_appsettings_file(char* buffer, char* appSettingsDirectory, char* appSettingsFileName);

SettingHost constructor_setting_host();

# endif