#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Lab 3 by Nafis Khan
*/

int main(void){	
    
	int status = 0, pID;

    // creating new child process
	pID = fork();

    // child
	if(pID == 0) {
		printf("Forked Successfully\n");
		printf("Child Process ID: %d\n", getpid()); 

        // prints all the necessary info
        // -l for cleaner view
        // -a for hidden files
		char *args[] = {"-a","-l", NULL};
		execvp("ls", args);
		printf("execvp Failed\n");	
	} 
    // parent
    else if (pID > 0) { 
        // waits for child to end
		waitpid(pID, &status, 0);
        // if there is an error
		if (wait < 0) {
			perror("wait");
			return 1;
		}

	} else { 
        // In case of fork error
		printf("Error occurred while creating the child process.\n");
		return 0;
	}
	return 0;

}