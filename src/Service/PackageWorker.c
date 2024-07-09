# include "../Application/PackageWorker.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

static const char* sudo = "sudo";
static const char* package_manager = "pacman";
static const char* q_flag = "-Q";

PackageWorker* constructor_package_worker(ProcessesManager* processesManager)
{
    PackageWorker* packageWorker = (PackageWorker*)malloc(sizeof(PackageWorker));

    packageWorker->processesManager = processesManager;

    packageWorker->is_package_exists = is_package_exists;

    return packageWorker;
}

int is_package_exists(void* self, char* packageName)
{
    if (packageName == NULL){
        return -1;
    }

    errno = 0;
    int errNum = 0;

    PackageWorker* packageWorker = (PackageWorker*)self;

    if ((errNum = packageWorker->processesManager->open_pipes(2, packageWorker->outPipe, packageWorker->errPipe)) != 0){
        return errNum;
    }

    pid_t childProcessPID = fork();

    char options[100];

    strcpy(options, package_manager);
    strcat(options, " ");
    strcat(options, q_flag);
    strcat(options, "i ");
    strcat(options, packageName);

    if (childProcessPID == -1){
        errNum = errno;
        return errNum;
    }
    else if (childProcessPID == 0){
        int copyOfOutFileDescriptorID = packageWorker->outPipe[1];
        int copyOfErrFileDescriptorID = packageWorker->errPipe[1];

        dup2(copyOfOutFileDescriptorID, STDOUT_FILENO);
        dup2(copyOfErrFileDescriptorID, STDERR_FILENO);

        execl("/bin/sh", "sh", "-c", options);

        packageWorker->processesManager->close_fds(2, STDOUT_FILENO, STDERR_FILENO);
    }
    else {
        int childProcessStatus;
        waitpid(childProcessPID, &childProcessStatus, 0);

        if (!WIFEXITED(childProcessStatus)){
            errNum = WEXITSTATUS(childProcessPID);
            return errNum;
        }

        packageWorker->processesManager->close_fds(2, packageWorker->errPipe[1], packageWorker->outPipe[1]);

        int countReadErrSymbols = 0;
        char ch;
        while (read(packageWorker->errPipe[0], &ch, 1) > 0){
            countReadErrSymbols++;
        }   

        if (countReadErrSymbols > 0){
            return -1;
        }

        return 0;
    }
}