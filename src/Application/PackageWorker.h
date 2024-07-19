# ifndef PACKAGE_WORKER
# define PACKAGE_WORKER

# define CHECK_PACKAGE 0
# define INSTALL_PACKAGE 1
# define UNISTALL_PACKAGE 2

typedef struct {
    int outPipe[2];
    int errPipe[2];

    char* (*get_check_str)(void* self, char* packageName);
    char* (*get_install_str)(void* self, char* packageName);
    char* (*get_unistall_str)(void* self, char* packageName);

    int (*launch_package_manager)(void* self, int mode, char* packageName);
} PackageWorker;

char* get_check_str(void* self, char* packageName);

char* get_install_str(void* self, char* packageName);

char* get_unistall_str(void* self, char* packageName);

int launch_package_manager(void* self, int mode, char* packageName);

PackageWorker* constructor_package_worker();

# endif 