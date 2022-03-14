#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> 

/*
Assignment 2 by Nafis Khan
*/

int main(int argc, char *argv[]) {

    // FOR TESTING PURPOSES, FEEL FREE TO USE THE SOURCE FILE INCLUDED TO SEE THE CHANGE

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // vars needed
    pid_t childProcess;
    int pipeFd[2];
    char buffer[BUFSIZ];
    
    // error handling pipe
    if (pipe(pipeFd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    childProcess = fork();

    // error handling the fork
    if (childProcess == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (childProcess == 0) {
        /* child process reads from file and feeds/writes to pipe */  

        // reading end of pipe not needed
        close(pipeFd[0]);

        // opening file descriptor from given argument
        int fileDescriptor = open(argv[1], O_RDONLY);

        // reading and storing data into the buffer | n = num of bytes read
        int n = read(fileDescriptor, buffer, sizeof(buffer));

        // writing buffer to the pipe;
        write(pipeFd[1], buffer, n);

        // file descriptor not needed after this
        close(fileDescriptor);
        // closed both ends of pipe in child process
        close(pipeFd[1]);
        exit(EXIT_SUCCESS);
    } 
    else if (childProcess > 0){

        // nothing to write to pipe, only read
        close(pipeFd[1]);

        // waiting for child to read all data from file
        wait(NULL);

        // opening the file again in write mode
        int fileDescriptor = open(argv[1], O_WRONLY);

        // writing msg to file
        int msg = sprintf(buffer, "Parent is writing: \n");
        write(fileDescriptor, buffer, msg);

        // reading data sent from parent through pipe
        int reading = read(pipeFd[0], buffer, sizeof(buffer));
        buffer[reading] = 0;

        // writing all the text from the pipe back into the file.
        write(fileDescriptor, buffer, reading);

        // closing the file descriptor and write pipe
        close(fileDescriptor);
        close(pipeFd[0]);
        exit(EXIT_SUCCESS);

    }


    return 0;
}