# include "../Application/Logging.h"
# include "../Application/EnvironmentManager.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

static char* const headers[3] = { "\033[1m\033[31mERROR\033[0m", "\033[1m\033[32mINFO\033[0m", "\033[1m\033[33mWARNING\033[0m"};

static char* const startMessageVariables[3] = { SMD_LOGGING_ERROR, SMD_LOGGING_INFO, SMD_LOGGING_WARNING };

Logging constructor_logging(EnvironmentManager *envMngr)
{
    Logging logging;

    logging.envMngr = envMngr;

    logging.log = log;

    return logging;
}

void log(int mode, char* message, char* treeFileNames, int noFileStr, char* time)
{
    char noFileStrToStr[8];
    sprintf(noFileStrToStr, "%d", noFileStr);
    
    size_t logMessageSize = 0;
    
    char* logMessage = malloc(2048);

    sprintf(logMessage, "%s\t\t%s\t\033[35m%s:\033[0m \033[33m%s:%s\033[0m\t%s", headers[mode],time, getenv(startMessageVariables[mode]), treeFileNames, noFileStrToStr, message);
    
    printf("%s", logMessage);
}