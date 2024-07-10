# include "../Application/PackageWorker.h"
#include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

static const char* sudo = "sudo";
static const char* package_manager = "pacman";
static const char* q_flag = "-Q";
static const char* s_flag = "-S";
static const char* unis_flag = "-Runs";
static const char* no_confirm_flag = "--noconfirm";

char* (*get_options[3])(void* self, char* packageName) = {get_check_str, get_install_str, get_unistall_str};

PackageWorker* constructor_package_worker(ProcessesManager* processesManager)
{
    PackageWorker* packageWorker = (PackageWorker*)malloc(sizeof(PackageWorker));

    packageWorker->processesManager = processesManager;

    packageWorker->get_check_str = get_check_str;
    packageWorker->get_install_str = get_install_str;
    packageWorker->get_unistall_str = get_unistall_str;
    packageWorker->launch_package_manager = launch_package_manager;

    return packageWorker;
}

char* get_check_str(void* self, char* packageName)
{
    PackageWorker* packageWorker = (PackageWorker*)self;

    char* options = malloc(256);

    packageWorker->processesManager->adding_to_buffer(options, 5, package_manager, " ", q_flag, "i ", packageName);

    return options;
}

char* get_install_str(void* self, char* packageName)
{
    PackageWorker* packageWorker = (PackageWorker*)self;

    char* options = malloc(256);

    packageWorker->processesManager->adding_to_buffer(options, 9, sudo, " ", package_manager, " ", s_flag, " ", no_confirm_flag, " ", packageName);

    return options;
}

char* get_unistall_str(void* self, char* packageName)
{
    PackageWorker* packageWorker = (PackageWorker*)self;

    char* options = malloc(256);

    packageWorker->processesManager->adding_to_buffer(options, 9, sudo, " ", package_manager, " ", unis_flag, " ", no_confirm_flag, " ", packageName);

    return options;
}

int launch_package_manager(void* self, int mode, char* packageName)
{
    if (packageName == NULL){
        return -1;
    }

    PackageWorker* packageWorker = (PackageWorker*)self;

    char* options = get_options[mode](packageWorker, packageName);

    if (packageWorker->processesManager->write_process(packageWorker->processesManager, options) != 0){
        return -1;
    }

    return 0;
}
