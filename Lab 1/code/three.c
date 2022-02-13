#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 

int main (int argc, char* argv[]) {

    // checks if correct arguments are given
    if(3 != argc) {
        printf("\nInccorrect Number of Arguments Provided.\n");
        return 1;
    }

    printf ("\nStarting Program..\n\n");

    // Creates new file and opens it
    int fd;
    int destination;


    // opens and creates a file if it DNE
    // Sets file to read and write mode for CURRENT owner/usr
    fd = open(argv[1], O_RDONLY);

    destination = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
    
    if(-1 == fd) {
        printf("\nOpen failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {

        printf("\nFile Opened Successfully.\n");


        char buffer[BUFSIZ]; // Declare an array of char called buffer that has a size of BUFSIZE (a macro constant)
        int length;
        
		while ((length = read(fd, buffer, BUFSIZ)) > 0) {	// rd is assigned the return value of read, # of characters that are read from fd
			write(destination, buffer, length);						// This write to the terminal whatever the 'read' syscall reads from the file
		}
    

    }

    close(fd);
    printf("\n\n\bFile Closed Successfully.\n");

    printf ("\nEnding Program..\n\n");
    return 0;
}