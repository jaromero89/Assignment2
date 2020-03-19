/* James Romero
 * CPSC 380
 * 03/07/20
 * Simple Shell
 * */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int main(void)
{

    char write_IN[BUFFER_SIZE];
    char read_IN[BUFFER_SIZE];

    // Exit conditions
    char exitONE[3] = "q\n";
    char exitTWO[6] = "quit\n";

    pid_t pid;
    int fd[2];

    // Error handling for pipe creation
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    //Fork
    pid = fork();

    // Error handling for fork creation
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }


    if (pid > 0) { // Parent
        // Close unneeded pipe openings
        close(fd[0]);

        // terminal name
        printf("root$ ");

        // Continues until exit condition is hit
        while((strcmp(&exitONE,write_IN) != 0) &&
              (strcmp(&exitTWO,write_IN) != 0)) {
            // Get input
            fgets(write_IN, BUFFER_SIZE, stdin);

            // Sends information to child process
            write(fd[1], write_IN, strlen(write_IN)+1);
        }


        close(fd[1]);
    }
    else { // Child

        close(fd[1]);


        while(1) {

            read(fd[0], read_IN, BUFFER_SIZE);

            if((strcmp(&exitONE,read_IN) != 0) &&
               (strcmp(&exitTWO,read_IN) != 0)) {
                // Executes the command
                system(read_IN);

                printf("root$ \n");
            
            }
            else {
                break;
            }
        }
        close(fd[1]);
    }

    return 0;
}