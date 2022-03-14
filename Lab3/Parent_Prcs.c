#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    Lab 3 by Nafis Khan
*/

int main (int argc, char* argv[]) {

    // Vars
    int forkOne = 0, forkTwo = 0, statOne = 0, statTwo = 0;

    // Forking First Child
    forkOne = fork();
    if (forkOne < 0) { 
        // fork error handling
        printf("Fork 1 Failed.\n");
        perror("fork");
        return 1;
    }
    // child process
    else if (forkOne == 0) {
        // executing compiled Prcs_P1 file
        char *args[] = {NULL};
        execv("./Prcs_P1.out", args);
    } 
    // parent process
    else {
        waitpid(forkOne, &statOne, 0);
    }

    // Make child process 2
    forkTwo = fork();
    if (forkTwo < 0) {
        // fork error handling
        printf("Fork 2 Failed.\n");
        perror("fork");
        return 1;
    } 
    // Child Process
    else if (forkTwo == 0) {
        // executing compiled Prcs_P2 file
        char *args[] = {NULL};
        execv("./Prcs_P2.out", args);
    } else {
        waitpid(forkTwo, &statTwo, 0);
    }

    return 0;
}