#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/*
Assignment 2 by Nafis Khan
*/

int main (int argc, char* argv[]) {

    // checks if correct arguments are given
    if(2 != argc) {
        printf("\nPlease provide appropriate arguments.\n");
        return 1;
    }

    int num, sum = 0;
    pid_t pidChildOne, pidChildTwo;
    num = atoi(argv[1]);

    // forking to create a new child process
    int childOne = fork();
    if(childOne == 0) {
        // print that you are the child
        printf("\nChild One:\n");
        for (int i = 1; i <= num; i += 2) {
                sum += i;
                printf("%d + ", i);
            }
        printf("\b\b= %d\n\n", sum);       

    }
    else {
        
        // creates child two
        int childTwo = fork();

        // waits for childTwo to be terminated
        waitpid(childTwo, NULL, 0);

        // if childTwo == 0, then it is the child, else parent
        if (childTwo == 0) {
            // printf("I am child two, my PID is: %d\n", getpid());
            printf("Child Two:\n");
            for (int i = 2; i <= num; i += 2) {
                    sum += i;
                    printf("%d + ", i);
                }
            printf("\b\b= %d\n\n", sum);   
        }
        else {
            // wait for child one to be terminated
            waitpid(childOne, NULL, 0);
            // this will get executed after both children have been terminated
            printf("Parent:\n");
            for (int i = 1; i <= num; i++) {
                sum += i;
                printf("%d + ", i);
            }
            printf("\b\b= %d\n", sum);        
        }
    }
    

    return 0;
}