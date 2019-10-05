#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    pid_t pid;
    int stat;
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }
        else 
        {
          char *token = strtok(command_line, delimiters);
          do {
            arguments[0] = token;
            token = strtok(NULL, delimiters);
            
          }while (token!=NULL);
        }
        pid = fork();
        if (pid < 0)
          // error forking
        {
          printf("There is a failure");
          stat = -1;
        }
        else if (pid == 0) {
          if (execve(arguments[0], arguments, environ) == -1) {
            printf("There is a failure");
        }
        }
      // parent process
        else if(waitpid (pid, &stat, 0) != pid) {
          return;
         
        }
    }
    
    return -1;
}
