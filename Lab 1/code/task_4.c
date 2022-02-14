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

    printf ("\n ------------------\n| Starting Program |\n ------------------\n\n");

    // Vars needed for creating file, deleting and opening file 
    int fd;
    int destination;
    int prevFile;

    // delete destination file if already exists
    prevFile = access(argv[2], F_OK);
	if (prevFile == 0) {
        unlink(argv[2]);
        printf("~Deleting prev file~\n");
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

        // Reads a 100 characters at a time while changing '1' to 'L' 
        // and also adding 'XYZ' at the end of the 100th Char
        char buffer[BUFSIZ]; 
        int length;
        
        // looping 100 chars at a time
		while ((length = read(fd, buffer, 100)) > 0) {	

            // changing all '1' to 'L' upto the data read
            for(int i = 0; i < length; i++) {
                if (buffer[i] == '1')
                    buffer[i] = 'L';
            }

            // adding 'XYZ' to the end of the 100th Char
            buffer[length] = 'X';
            buffer[length + 1] = 'Y';
            buffer[length + 2] = 'Z';

            // writing data to file
			write(destination, buffer, length + 3);

		}

        // pushing curser to new line since bash/zsh terminal reads it as an unfinished line 
        // and prints a "%" at the end.
        write(destination, "\n", 1);
        printf ("~Completed Copy~\n");
    }

    // closing both source and destination file descriptor
    close(fd);
    close(destination);

    printf ("\n ----------------\n| Ending Program |\n ----------------\n\n");
    return 0;
}