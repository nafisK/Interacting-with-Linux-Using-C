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
        printf("\nPlease provide appropriate arguments.\n");
        return 1;
    }

    printf ("\n ------------------\n| Starting Program |\n ------------------\n");

    // Vars needed for creating file, deleting and opening file 
    int fd;
    int destination;
    int prevFile;

    // delete destination file if already exists
    prevFile = access(argv[2], F_OK);
	if (prevFile == 0) {
        unlink(argv[2]);
        printf("\n~Deleting prev file~\n");
    }

    // opens and creates a file if it DNE
    // Sets file to read and write mode for CURRENT owner/usr
    fd = open(argv[1], O_RDONLY);

    // error handling FD
    if(fd < 0) {
        printf("Filename could not be opened.\n");
        perror("open");
        return 1;  
    }

    // opens file or creates a new one with read & write access
    destination = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
    
    if(-1 == fd) {
        printf("\nOpen failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {
      
        // Declaring buffer to BUFFSIZE (macro constant)
        char buffer[BUFSIZ]; 
        // holds length of each buffer read
        int length;
        
        // reads data with BUFFSIZE in increments until end of file is reached
		while ((length = read(fd, buffer, BUFSIZ)) > 0) {	
            // 1 as the first argument represents a print to terminal function which can also be achieved using printf(data) 
			write(destination, buffer, length);						
		}
        printf ("\n~Data Copied to New File~\n");


    }

    close(fd);
    printf ("\n ----------------\n| Ending Program |\n ----------------\n\n");
    return 0;
}