#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/*
Assignment 2 by Nafis Khan
*/

int main (int argc, char* argv[]) {

    int a = 10,
        b = 25,
        fq = 0,
        fr = 0;

    printf("Starting Parent Process: %d\n\n", getpid());


    fq = fork();    // fork a child - call it Process Q

    if (fq == 0) {  // child successfully created
        a = a + b;
        // print vals of a, b and process_id
        printf("Q Child:\na: %d, b: %d, and child process id: %d\n", a, b, getpid());
        printf("Value of Parent Currently: %d\n\n", getppid());

        fr = fork();
        if (fr != 0) {
            b = b + 20;
            // print values of a, b and process_id
            printf("R Parent:\na: %d, b: %d, and child process id: %d\n", a, b, getpid());
            printf("Value of Parent Currently: %d\n\n", getppid());

        } 
        else {
            a = (a * b) + 30;
            // print values of a, b and process_id
            printf("R Child:\na: %d, b: %d, and child process id: %d\n", a, b, getpid());
            printf("Value of Parent Currently: %d\n\n", getppid());

        }   
    }
    else {
        b = (a + b) - 5;
        // print values of a, b and process_id
        printf("Q Parent:\na: %d, b: %d, and child process id: %d\n", a, b, getpid());
        printf("Value of Parent Currently: %d\n\n", getppid());

    }
    



    return 0;
}
