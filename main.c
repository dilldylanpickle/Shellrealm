#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "main.h"
#include "error.h"

void shr_title() {
    printf("\n");
    printf("███████╗██╗  ██╗███████╗██╗     ██╗     ██████╗ ███████╗ █████╗ ██╗     ███╗   ███╗\n");
    printf("██╔════╝██║  ██║██╔════╝██║     ██║     ██╔══██╗██╔════╝██╔══██╗██║     ████╗ ████║\n");
    printf("███████╗███████║█████╗  ██║     ██║     ██████╔╝█████╗  ███████║██║     ██╔████╔██║\n");
    printf("╚════██║██╔══██║██╔══╝  ██║     ██║     ██╔══██╗██╔══╝  ██╔══██║██║     ██║╚██╔╝██║\n");
    printf("███████║██║  ██║███████╗███████╗███████╗██║  ██║███████╗██║  ██║███████╗██║ ╚═╝ ██║\n");
    printf("╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝\n");
    printf("\n");
    printf("You have entered the shellrealm!\n");
}

int shr_infect(char **arguments) {
    if (arguments[1] == NULL || !is_valid_ip(arguments[1])) {
        printf("[-] Error: Invalid IP address.\n");
        printf("Usage: infect [IP Address] [optional payload]\n");
        return 1;
    }

    if (arguments[2] != NULL) {
        if (arguments[3] != NULL) {
            printf("[/] Attempting to infect %s with payload %s...\n", arguments[1], arguments[3]);
        } else {
            printf("[+] Attempting to infect %s with payload %s...\n", arguments[1], arguments[2]);
        }
    } else {
        printf("[+] Attempting to infect %s...\n", arguments[1]);
    }
    
    printf("[+] Victim %s has been compromised!\n", arguments[1]);

    return 1;
}

int shr_access(char **arguments) {
    
    if (arguments[1] == NULL || !is_valid_ip(arguments[1])) {
        printf("[-] Error: Invalid IP address.\n");
        printf("Usage: access [IP Address]\n");
        return 1;
    }

    printf("[/] Attempting to access %s...\n", arguments[1]);
    
    //printf("[+] Now accessing %s...\n", arguments[1]);
    //printf("[+] Spawning shell!\n\n");
    //system("/bin/sh");

    return 1;
}


int shr_send(char **arguments) {
    if (arguments[1] == NULL || arguments[2] == NULL || arguments[3] == NULL) {
        printf("[-] Error: Insufficient arguments.\n");
        printf("Usage: send [rootkit] [name] [IP Address]\n");
        return 1;
    }

    if (strcmp(arguments[1], "rootkit") == 0 ) {
        if (!is_valid_ip(arguments[3])) {
            printf("[-] Error: Invalid IP address.\n");
            return 1;
        }
        printf("[/] Sending %s %s to %s\n", arguments[1], arguments[2], arguments[3]);
        printf("[+] The rootkit %s has been planted\n", arguments[2]);
    } else {
        printf("[-] Error: Unknown type '%s'. Only 'rootkit' is supported.\n", arguments[1]);
        return 1;
    }

    return 1;
}


int shr_rootkit(char **arguments) {
    if (arguments[1] == NULL) {
        printf("[-] Error: No rootkit name provided.\n");
        printf("Usage: rootkit [rootkit name]\n");
        return 1;
    }

    printf("[+] Deploying rootkit: %s\n", arguments[1]);

    return 1;
}

int shr_payload(char **arguments) {

    printf("A very real exploit :)\n");

    return 1;
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
    char *line = readline("\n(shellrealm) ");
    if (line && *line) {
        add_history(line);
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
