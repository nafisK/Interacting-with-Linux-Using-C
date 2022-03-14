#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Lab 3 by Nafis Khan
*/

int main(void){	
    
	int pID, status = 0;

    // creating new child process
	pID = fork();

    // For Parent
	if(pID != 0){ 
        // waits for child process to go first
        waitpid(pID, &status, 0);
        // error handling
		if (wait < 0) {
			perror("wait");
			return 1;
		}
		printf("Parent Process ID: %d\n", getpid());   
	}
    // For Child
    else if (pID > 0) {  
		printf("Forked Successfully\n");
		printf("Child Process ID: %d\n", getpid()); 

        // executes 'date' command via path
        execl("/bin/date", "date", NULL);
		printf("'excel' failed!\n");
	} 
	else { 
        // In case of fork error
		printf("Error occurred while creating the child process.\n");
		return 0;
	}

	return 0;
}