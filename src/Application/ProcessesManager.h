# ifndef PROCESSES_MANAGER
# define PROCESSES_MANAGER

typedef struct {
    int (*open_pipes)(int, ...);
} ProcessesManager;

int open_pipes(int, ...);

ProcessesManager constructor_processes_manager();

# endif