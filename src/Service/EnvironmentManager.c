# include "../Application/EnvironmentManager.h"
# include "../Application/Mapping.h"
# include "../Model/AppSettings.h"
# include <string.h>
# include <stdlib.h>

# define ENV_SMD "SIMPLEDOT_"
# define ENV_LOGGING "LOGGING_"
# define ENV_ERROR "ERROR"
# define ENV_INFO "INFO"
# define ENV_WARNING "WARNING"

EnvironmentManager constructor_environment_manager(Mapping mapping)
{
    EnvironmentManager envMngr;

    envMngr.mapping = mapping;
    envMngr.get_variables = get_variables;

    return envMngr;
}


char* get_variables(void* self, AppSettings* appSettings)
{
    EnvironmentManager* envMngr = (EnvironmentManager*)self;

    char* result = malloc(2048);

    char* errorStrDTO = envMngr->mapping.to_dto(appSettings->loggingSettings.error);
    char* infoStrDTO = envMngr->mapping.to_dto(appSettings->loggingSettings.info);
    char* warningStrDTO = envMngr->mapping.to_dto(appSettings->loggingSettings.warning);

    strcpy(result, envMngr->mapping.get_appsetting_string(WITH_N, errorStrDTO, 3, ENV_SMD, ENV_LOGGING, ENV_ERROR));
    strcat(result, envMngr->mapping.get_appsetting_string(WITH_N, infoStrDTO, 3, ENV_SMD, ENV_LOGGING, ENV_INFO));
    strcat(result, envMngr->mapping.get_appsetting_string(WITH_N, warningStrDTO, 3, ENV_SMD, ENV_LOGGING, ENV_WARNING));
    
    return result;
}