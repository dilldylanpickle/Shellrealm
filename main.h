#define debug_on 1

#if debug_on
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...)
#endif

int shr_exit(char **arguments);
int shr_version(char **arguments);
int shr_help(char **arguments);
int shr_infect(char **arguments);
int shr_payload(char **arguments);
int shr_send(char **arguments);
int shr_rootkit(char **arguments);
int shr_access(char **arguments);

typedef struct {
    char *name;
    int (*func)(char **);
} shrcmds;

shrcmds commands[] = {
    {"exit", shr_exit},
    {"version", shr_version},
    {"help", shr_help},
    {"infect", shr_infect},
    {"payload", shr_payload},
    {"send", shr_send},
    {"rootkit", shr_rootkit},
    {"access", shr_access},
};

int cmds = sizeof(commands) / sizeof(shrcmds);