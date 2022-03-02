#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/*
Assignment 2 by Nafis Khan
*/

int main (int argc, char* argv[]) {

    // printf("Parent Process, PID: %d\n", getpid());
    pid_t statusOne, statusTwo;

    // forking to create a new child process
    int childOne = fork();
    if(childOne == 0) {
        // print that you are the child
        printf("I am child one, my PID is: %d\n", getpid());
    }
    else {
        
        // creates child two
        int childTwo = fork();

        // waits for childTwo to be terminated
        waitpid(childTwo, &statusTwo, 0);

        // if childTwo == 0, then it is the child, else parent
        if (childTwo == 0) {
            printf("I am child two, my PID is: %d\n", getpid());
        }
        else {
            // wait for child one to be terminated
            waitpid(childOne, &statusOne, 0);
            // this will get executed after both children have been terminated
            printf("I am the parent with PID %d\n", getpid());
        }
    }

   
    
    return 0;
}
