#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Lab 3 by Nafis Khan
*/

int main(void){	
    
	int pID, status;

    // creating new child process
	pID = fork();

    // waits for child process to go first
	wait(&status);

    // For Parent
	if(pID != 0){ 
		printf("Parent Process ID: %d\n", getpid());   
	}
    // For Child
    else{  
		printf("Child Process ID: %d\n", getpid()); 

        // executes 'date' command via path
        execl("/bin/date", "date", NULL);
		printf("'excel' failed!\n");
	}
	return 0;
}