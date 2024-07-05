# include "../Application/PackageWorker.h"
# include <unistd.h>
# include <string.h>
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
    errno = 0;

    PackageWorker* ppackageWorker = (PackageWorker*)self;
    pipe(ppackageWorker->errPipe);
    pipe(ppackageWorker->outPipe);

    int errNum = errno;

    return errNum;
}

int is_package_exists(void* self, char* packageName)
{
    errno = 0;
    int errNum = 0;

    PackageWorker* ppackageWorker = (PackageWorker*)self;

    if ((errNum = ppackageWorker->open_std_pipes(ppackageWorker)) != 0){
        return errNum;
    }

    pid_t childProcessPID = fork();

    if (childProcessPID == -1){
        errNum = errno;
        return errNum;
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

        if (!WIFEXITED(childProcessStatus)){
            errNum = WEXITSTATUS(childProcessPID);
            return errNum;
        }

        close(ppackageWorker->errPipe[1]);
        close(ppackageWorker->outPipe[1]);

        int countReadErrSymbols = 0;
        char ch;
        while (read(ppackageWorker->errPipe[0], &ch, 1) > 0){
            // printf("%c", ch);
            countReadErrSymbols++;
        }   

        if (countReadErrSymbols > 0){
            return -1;
        }

        return 0;
    }
}