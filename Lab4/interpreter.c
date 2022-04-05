#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Lab 4 - Nafis Khan

int main (int argc, char* argv[]) {

    // setting up variables
	int command;
	int cpid;

    // setting up a set size for the inputs
	char userInput[128];
	char *token;

    // holds upto 10 args
	char *arg[10] = {NULL};
	
    // reading command from user
	printf("Please enter command: ");
	scanf("%[^\n]s", userInput); 

    // terminating claus if user wants to exit, else keeps running
	while ((strcmp(userInput, "exit"))) { 

        // breaking input into series of tokens
		token = strtok(userInput, " ");
    
        // setting commands into an array seperately
		int index = 0;
		while(token != NULL) {
			arg[index] = token; 
	        token = strtok(NULL," ");  
			index++;
		}

        // creating the child fork 
		cpid = fork();
        wait(&command);

        // child process
		if (cpid == 0) {
            // executes command read
			if(execvp (arg[0], arg) == -1) {
                // error handling
                printf("Wrong command, try again.\nEnter command: ");
                scanf("%[^\n]s", userInput);
            }

		} 
		// parent process
        else {

			// clearing for next iteration in loop
			for (int i = 0; i < index; ++i){
				arg[i] = NULL; 
			}
            
            // Asks for a command again after executing the previous command
			printf("\nEnter command: ");
			scanf(" %[^\n]s", userInput);
		}		
	}

	return 0;
}