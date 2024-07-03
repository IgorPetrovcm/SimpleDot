# include "PackageWorker.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>

static const char* sudo = "sudo";
static const char* package_manager = "pacman";
static const char* q_flag = "-Q";

PackageWorker constructor_package_worker()
{
    PackageWorker packageWorker;
    packageWorker.is_package_exists = is_package_exists;
    packageWorker.open_std_pipes = open_std_pipes;

    return packageWorker;
}

int open_std_pipes(void* self)
{
    PackageWorker* ppackageWorker = (PackageWorker*)self;
    pipe(ppackageWorker->errPipe);
    pipe(ppackageWorker->outPipe);

    return errno;
}

int is_package_exists(void* self, char* packageName)
{
    PackageWorker* ppackageWorker = (PackageWorker*)self;

    if (!ppackageWorker->open_std_pipes(ppackageWorker)){
        strerror(errno);
    }

    pid_t childProcessPID = fork();

    if (childProcessPID == -1){
        strerror(errno);
    }
    else if (childProcessPID == 0){
        int copyOfOutFileDescriptorID = ppackageWorker->outPipe[1];
        int copyOfErrFileDescriptorID = ppackageWorker->errPipe[1];

        dup2(copyOfOutFileDescriptorID, STDOUT_FILENO);
        dup2(copyOfErrFileDescriptorID, STDERR_FILENO);

        char options[100];

        strcpy(options, package_manager);
        strcat(options, " ");
        strcat(options, q_flag);
        strcat(options, "i ");
        strcat(options, packageName);

        execl("/bin/sh", "sh", "-c", options);

        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }
    else {
        int childProcessStatus;
        waitpid(childProcessPID, &childProcessStatus, 0);

        close(ppackageWorker->errPipe[1]);
        close(ppackageWorker->outPipe[1]);

        int countReadErrSymbols = 0;
        char ch;
        while (read(ppackageWorker->errPipe[0], &ch, 1) > 0){
            printf("%c", ch);
            countReadErrSymbols++;
        }   

        if (countReadErrSymbols > 0){
            return -1;
        }

        return 0;
    }
}