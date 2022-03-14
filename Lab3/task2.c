#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Lab 3 by Nafis Khan
*/

int main(void){	
    
	int status, pID;

    // creating new child process
	pID = fork();

    // waits for child process to go first
	wait(&status);

    // parent
	if(pID == 0){
		printf("Child Forked Successfully, PID: %d\n", getpid());

        // prints all the necessary info
        // -l for cleaner view
        // -a for hidden files
        // -o for removing unnecessary info
		char *argv[] = {"ls", "-lao", NULL};
		execvp(argv[0], argv);
		printf("execvp Failed\n");	
	}
	return 0;

}