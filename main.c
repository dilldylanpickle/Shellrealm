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

void shr_title()
{
    printf("███████╗██╗  ██╗███████╗██╗     ██╗     ██████╗ ███████╗ █████╗ ██╗     ███╗   ███╗\n");
    printf("██╔════╝██║  ██║██╔════╝██║     ██║     ██╔══██╗██╔════╝██╔══██╗██║     ████╗ ████║\n");
    printf("███████╗███████║█████╗  ██║     ██║     ██████╔╝█████╗  ███████║██║     ██╔████╔██║\n");
    printf("╚════██║██╔══██║██╔══╝  ██║     ██║     ██╔══██╗██╔══╝  ██╔══██║██║     ██║╚██╔╝██║\n");
    printf("███████║██║  ██║███████╗███████╗███████╗██║  ██║███████╗██║  ██║███████╗██║ ╚═╝ ██║\n");
    printf("╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝\n");

    printf("\nYou have entered the shellrealm!\n\n");

}

char *shr_readline(void)
{
  char *line = NULL;
  ssize_t bufsize = 0;

  getline(&line, &bufsize, stdin);

  return line;
}

char **shr_readargs(char *line)
{
    int index = 0;
    char **arguments = malloc(64 * sizeof(char*));
    char *command;

    command = strtok(line, " \t\r\n\a");
    while (command != NULL) {
        arguments[index] = command;
        index++;
        command = strtok(NULL, " \t\r\n\a");
    }

    arguments[index] = NULL;
    return arguments;
}

int shr_execve(char *arguments[]) 
{
    int status = 1;
    pid_t pid;

    if (arguments[0] == NULL) {
        debugf("\t[DEBUG] No arguments provided\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        execvp(arguments[0], arguments);
        perror("shr");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shr");
        return 1;
    } else {
        wait(NULL);
    }

    return status;
}

void shellrealm(void)
{
    char *line;
    char **arguments;
    int status;

    shr_title();

    do {
        printf("(shellrealm) ");
        line = shr_readline();
        arguments = shr_readargs(line);
        status = shr_execve(arguments);

        free(line);
        free(arguments);

    } while (status);
}

int main(int argc, char *argv[])
{
    shellrealm();

    return 0;
}