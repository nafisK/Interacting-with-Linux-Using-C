#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> 


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipeFd[2];
    pid_t frk;
    // int fileDescriptor;
    char buffer[BUFSIZ];
    
    // error handling pipe
    if (pipe(pipeFd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    frk = fork();

    // error handling the fork
    if (frk == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (frk == 0) {
        // closing reading end of pipe since nothing is being read from parent
        close(pipeFd[0]);

        // opening file descriptor for given arg
        int fileDescriptor = open(argv[1], O_RDONLY);

        // reading and storing data into the buffer
        int n = read(fileDescriptor, buffer, sizeof(buffer));
        close(fileDescriptor);

        // writing buffer to the pipe;
        write(pipeFd[1], buffer, n);
        close(pipeFd[1]);
        exit(0);
        // exit(EXIT_SUCCESS);
    } 
    else if (frk > 0){

        // nothing to write to pipe, only read
        close(pipeFd[1]);

        // waiting for child to read all data from file
        wait(NULL);

        // opening the file again in write mode
        int fileDescriptor = open(argv[1], O_WRONLY);

        // writing msg to file
        int n = sprintf(buffer, "Parent is writing: \n");
        write(fileDescriptor, buffer, n);

        // reading data sent from parent through pipe
        int reading = read(pipeFd[0], buffer, sizeof(buffer));
        buffer[reading] = 0;

        write(fileDescriptor, buffer, reading);
        close(fileDescriptor);
        close(pipeFd[0]);
    
    }


    return 0;
}