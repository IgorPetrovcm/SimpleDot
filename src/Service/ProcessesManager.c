# include "../Application/ProcessesManager.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <errno.h>

ProcessesManager* constructor_processes_manager()
{
    ProcessesManager* procMngr = (ProcessesManager*)malloc(sizeof(ProcessesManager));

    procMngr->open_pipes = open_pipes;

    return procMngr;
}

int open_pipes(int count , ...)
{
    errno = 0;
    int errNum;

    va_list ap;

    va_start(ap, count);

    for (int i = 0; i < count; i++){
        pipe(va_arg(ap, int*));
    }

    if ((errNum = errno) != 0){
        return errNum;
    }

    return 0;
}