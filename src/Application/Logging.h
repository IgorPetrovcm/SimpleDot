# ifndef LOGGING
# define LOGGING

# define LOG_ERR 0
# define LOG_INF 1
# define LOG_WAR 2

# include "EnvironmentManager.h"

typedef struct {
    EnvironmentManager* envMngr;
    void (*log)(int mode, char* message, char* treeFileNames, int noFileStr, char* time);
} Logging;

void log(int mode, char* message, char* treeFileNames, int noFileStr, char* time);

Logging constructor_logging(EnvironmentManager* envMngr);

# endif