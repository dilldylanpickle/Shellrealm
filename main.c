#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("[DEBUG] Line to tokenize: %s", line);

    command = strtok(line, " \t\r\n\a");
    while (command != NULL) {
        arguments[index] = command;
        index++;
        command = strtok(NULL, " \t\r\n\a");
    }

    arguments[index] = NULL;
    return arguments;
}

void shellrealm(void)
{
    char *line;
    char **arguments;
    int status;

    do {
        printf("(shellrealm) ");
        line = shr_readline();
        arguments = shr_readargs(line);

        int index = 0;
        while (arguments[index] != NULL) {
            printf("[DEBUG] Argument %d: %s\n", index, arguments[index]);
            index++;
        }

        free(arguments);

    } while (status);
}

int main(int argc, char *argv[])
{
    shellrealm();

    return 0;
}