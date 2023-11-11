#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug_on 1

#if debug_on
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...)
#endif

int shr_exit(char **arguments);
int shr_version(char **arguments);
int shr_help(char **arguments);

typedef struct {
    char *name;
    int (*func)(char **);
} shrcmds;

shrcmds commands[] = {
    {"exit", shr_exit},
    {"version", shr_version},
    {"help", shr_help},
};

int cmds = sizeof(commands) / sizeof(shrcmds);

void shr_title() {
    printf("\n");
    printf("███████╗██╗  ██╗███████╗██╗     ██╗     ██████╗ ███████╗ █████╗ ██╗     ███╗   ███╗\n");
    printf("██╔════╝██║  ██║██╔════╝██║     ██║     ██╔══██╗██╔════╝██╔══██╗██║     ████╗ ████║\n");
    printf("███████╗███████║█████╗  ██║     ██║     ██████╔╝█████╗  ███████║██║     ██╔████╔██║\n");
    printf("╚════██║██╔══██║██╔══╝  ██║     ██║     ██╔══██╗██╔══╝  ██╔══██║██║     ██║╚██╔╝██║\n");
    printf("███████║██║  ██║███████╗███████╗███████╗██║  ██║███████╗██║  ██║███████╗██║ ╚═╝ ██║\n");
    printf("╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝\n");
    printf("\nYou have entered the shellrealm!\n\n");
}

int shr_help(char **arguments) {
    printf("Shellrealm commands:\n");
    for (int i = 0; i < sizeof(commands) / sizeof(shrcmds); i++) {
        printf(" - %s\n", commands[i].name);
    }
    return 1;
}

int shr_exit(char **arguments) {
    printf("Exiting Shellrealm...\n");
    return 0;
}

int shr_version(char **arguments) {
    printf("Shellrealm version 1.0\n");
    return 1;
}

char *shr_readline(void) {
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (!feof(stdin)) {
            perror("getline failed");
        }
        free(line);
        return NULL;
    }

    return line;
}

char **shr_readargs(char *line) {
    int bufsize = 64, index = 0;
    char **arguments = malloc(bufsize * sizeof(char*));
    char *command;

    if (!arguments) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    command = strtok(line, " \t\r\n\a");
    while (command != NULL) {
        arguments[index] = command;
        index++;

        if (index >= bufsize) {
            bufsize += 64;
            arguments = realloc(arguments, bufsize * sizeof(char*));
            if (!arguments) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        command = strtok(NULL, " \t\r\n\a");
    }

    arguments[index] = NULL;
    return arguments;
}

int shr_execve(char *arguments[]) {

    if (arguments[0] == NULL) {
        debugf("\t[DEBUG] No arguments provided\n");
        return 1;
    }

    for (int i = 0; i < cmds; i++) {
        if (strcmp(arguments[0], commands[i].name) == 0) {
            return commands[i].func(arguments);
        }
    }

    printf("%s: command not found\n", arguments[0]);
    return 1;
}

void shellrealm(void) {
    char *line;
    char **arguments;
    int status;

    shr_title();

    do {
        printf("(shellrealm) ");
        line = shr_readline();
        if (!line) {
            break;
        }

        arguments = shr_readargs(line);
        status = shr_execve(arguments);

        free(line);
        free(arguments);
    } while (status);
}

int main(int argc, char *argv[]) {
    shellrealm();
    return 0;
}
