# ifndef ENVIRONMENT_MANAGER
# define ENVIRONMENT_MANAGER

# include "Mapping.h"
# include "../Model/AppSettings.h"

typedef struct {
    Mapping mapping;
    char* (*get_variables)(void*, AppSettings*);
} EnvironmentManager;

char* get_variables(void* self, AppSettings* appSettings);

EnvironmentManager constructor_environment_manager(Mapping mapping);

# endif