# ifndef PACKAGE_WORKER
# define PACKAGE_WORKER

# include "ProcessesManager.h" 

typedef struct {
    int outPipe[2];
    int errPipe[2];

    ProcessesManager* processesManager;

    // int (*open_std_pipes) (void*);
    int (*is_package_exists) (void*, char*);
} PackageWorker;

int is_package_exists(void* self, char* packageName);

// int open_std_pipes(void* self);

PackageWorker* constructor_package_worker(ProcessesManager* processesManager);

# endif 