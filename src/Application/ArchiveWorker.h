# ifndef ARCHIVE_WORKER
# define ARCHIVE_WORKER

# include "EnvironmentManager.h"
# include "Logging.h"
# include <stdio.h>

typedef struct {
    Logging* logging;
    EnvironmentManager* envMngr;
    
    int (*extract_archive)(void* self, char* archivePath);
    size_t (*write_file)(void* ptr, size_t size, size_t nmemb, void* stream);
    int (*get_remote_archive)(void* self, char* url);
} ArchiveWorker;

int extract_archive(void* self, char* archivePath);

int get_remote_archive(void* self, char* url);

size_t write_file(void* ptr, size_t size, size_t nmemb, void* stream);

ArchiveWorker* constructor_archive_worker(Logging* logging, EnvironmentManager* envMngr);

# endif