# ifndef NETWORK_WORKER
# define NETWORK_WORKER

# include "Logging.h"
# include <stdio.h>

typedef struct {
    Logging* logging;
    
    size_t (*write_file)(void* ptr, size_t size, size_t nmemb, void* stream);
    int (*get_archive_from_remote_repo)(void* self, char* url);
} NetworkWorker;

int get_archive_from_remote_repo(void* self, char* url);

size_t write_file(void* ptr, size_t size, size_t nmemb, void* stream);

NetworkWorker* constructor_network_worker(Logging* logging);

# endif