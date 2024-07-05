# ifndef MAPPING
# define MAPPING

# define WITH_N 0
# define WITHOUT_N 1

typedef struct {
    char* (*to_dto)(char*);
    char* (*get_appsetting_string)(int, char*, int, ...);
} Mapping;

char* to_dto(char* value);

char* get_appsetting_string(int mode, char* value, int argc, ...);

Mapping constructor_mapping();

# endif