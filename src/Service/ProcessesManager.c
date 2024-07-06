# include "../Application/ProcessesManager.h"
# include <stdarg.h>
# include <unistd.h>
# include <errno.h>

ProcessesManager constructor_processes_manager()
{
    ProcessesManager procMngr;

    procMngr.open_pipes = open_pipes;
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