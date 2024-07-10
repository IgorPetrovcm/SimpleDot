# include "../Application/ProcessesManager.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <errno.h>

ProcessesManager* constructor_processes_manager()
{
    ProcessesManager* procMngr = (ProcessesManager*)malloc(sizeof(ProcessesManager));

    procMngr->adding_to_buffer = adding_to_buffer;
    procMngr->open_pipes = open_pipes;
    procMngr->close_fds = close_fds;
    procMngr->write_process = write_process;

    return procMngr;
}

int adding_to_buffer(char* buffer, int count, ...)
{
    errno = 0;
    int errNum;
    
    va_list ap;

    va_start(ap, count);

    for (int i = 0; i < count; i++){
        if (i == 0){
            strcpy(buffer, va_arg(ap, char*));
        }
        else {
            strcat(buffer, va_arg(ap, char*));
        }
    }
    va_end(ap);

    if ((errNum == errno) != 0){
        return errNum;
    }

    return 0;
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
    va_end(ap);

    if ((errNum = errno) != 0){
        return errNum;
    }

    return 0;
}

int close_fds(int count, ...)
{
    errno = 0;
    int errNum;

    va_list ap;

    va_start(ap, count);

    for (int i = 0; i < count; i++){
        close(va_arg(ap, int));
    }
    va_end(ap);

    if ((errNum = errno) != 0){
        return errNum;
    }

    return 0;
}

int write_process(void* self, char* options)
{
    errno = 0;
    int errNum = 0;

    ProcessesManager* procMngr = (ProcessesManager*)self;

    int outPipe[2], errPipe[2];

    if ((errNum = procMngr->open_pipes(2,outPipe, errPipe)) != 0){
        return errNum;
    }

    pid_t childProcessPID = fork();

    if (childProcessPID == -1){
        errNum = errno;
        return errNum;
    }
    else if (childProcessPID == 0){
        int copyOfOutFileDescriptorID = outPipe[1];
        int copyOfErrFileDescriptorID = errPipe[1];

        dup2(copyOfOutFileDescriptorID, STDOUT_FILENO);
        dup2(copyOfErrFileDescriptorID, STDERR_FILENO);

        execl("/bin/sh", "sh", "-c", options);

        procMngr->close_fds(2, STDOUT_FILENO, STDERR_FILENO);
    }
    else {
        free(options);
        
        int childProcessStatus;
        waitpid(childProcessPID, &childProcessStatus, 0);

        if (!WIFEXITED(childProcessStatus)){
            errNum = WEXITSTATUS(childProcessPID);
            return errNum;
        }

        procMngr->close_fds(2, errPipe[1], outPipe[1]);

        int countReadErrSymbols = 0;
        char ch;
        while (read(errPipe[0], &ch, 1) > 0){
            countReadErrSymbols++;
        }   

        if (countReadErrSymbols > 0){
            return -1;
        }

    }
    return 0;
}