/*
 James L. Romero
 CPSC380 Operating Systems
 Dr. Springer
 Collabrated with Cam Wang
 Citations: https://www.includehelp.com/c/file-management-system-calls.aspx
            https://www.java-samples.com/showtutorial.php?tutorialid=569
 */
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main(int argc, char *argv[]) {

    ssize_t readN;
    ssize_t writeN;
    int input_FD, output_FD;
    char buf[BUF_SIZE];

    if (argc != 3) {
        printf("Usage: cp file1 file2");
        return 1;
    }


    input_FD = open(argv[1], O_RDONLY);
    if (input_FD == -1) {
        printf("Error Number % d\n", errno);
        perror("Program");
        perror("open");
        return 2;
    }

    output_FD = open(argv[2], O_WRONLY | O_CREAT);
    if (output_FD == -1) {
        printf("Error Number % d\n", errno);
        perror("Program");
        perror("write");
        return 3;
    }

    while ((readN = read(input_FD, buf, BUFSIZ)) > 0) {
        writeN = write(output_FD, buf, readN);
        if (readN != writeN) {
            printf("Error Number % d\n", errno);
            perror("Program");
            perror("write");
            return 4;
        }
    }

    close(input_FD);
    close(output_FD);

    return 0;
}

