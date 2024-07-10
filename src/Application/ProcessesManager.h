# ifndef PROCESSES_MANAGER
# define PROCESSES_MANAGER

typedef struct {
    int (*adding_to_buffer)(char* buffer, int count, ...);
    int (*open_pipes)(int count, ...);
    int (*close_fds)(int count, ...);
    int (*write_process)(void* self, char* options);
} ProcessesManager;

int adding_to_buffer(char* buffer, int count, ...);

int open_pipes(int count, ...);

int close_fds(int count, ...);

int write_process(void* self, char* options);

ProcessesManager* constructor_processes_manager();

# endif