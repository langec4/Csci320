/*
*
* Create a program that prints a prompt, reads the input one line at a time, parses the input into tokens
* creates a new process, makes the child process start the program specified by the first token, and wait 
* for the child process to terminate, then repeats the whole sequence. It will terminate eventually.
* Written By: Carter Lange
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char buff[1024];  
    char *args[64];   
    while (1) {
        printf("shell> ");                //Prints the prompt shell
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            break;  // End of file reached
        }
        // Removes the newline
        buff[strcspn(buff, "\n")] = 0;
        // This parses the input into tokens
        char *token = strtok(buff, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // This checks if there was an input to the command line, and will ask again if not
        if (args[0] == NULL) {
            continue;
        }

        
        int pid = fork();
        if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            // Parent process
            wait(NULL);  // This waits for the child process to finish
        } else {
            perror("fork failure"); //fork failed
        }
    }

    return 0;
}
