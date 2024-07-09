# ifndef PROCESSES_MANAGER
# define PROCESSES_MANAGER

typedef struct {
    int (*open_pipes)(int count, ...);
    int (*close_fds)(int count, ...);
} ProcessesManager;

int open_pipes(int count, ...);

int close_fds(int count, ...);

ProcessesManager* constructor_processes_manager();

# endif