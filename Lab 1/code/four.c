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
        printf("\nPLease provide a source and destination location.\n");
        return 1;
    }

    printf ("\nStarting Program..\n------------------\n\n");

    // Creates new file and opens it
    int fd;
    int destination;
    int prevFile;

    // delete destination file if exists
    prevFile = access(argv[2], F_OK);
	if (prevFile == 0) {
        unlink(argv[2]);
        printf("\nDeleting prev file.\n");
    }
		

    // opens and creates a file if it DNE
    // Sets file to read and write mode for CURRENT owner/usr
    fd = open(argv[1], O_RDONLY);

        destination = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
    
    if(-1 == fd) {
        printf("\nOpen failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {

        char buffer[100]; 
        int length;
        
		while ((length = read(fd, buffer, 100)) > 0) {	

            for(int i = 0; i < length; i++) {
                if (buffer[i] == '1')
                    buffer[i] = 'L';
            }

            buffer[length] = 'X';
            buffer[length + 1] = 'Y';
            buffer[length + 2] = 'Z';

			write(destination, buffer, length + 3);
            


		}
        write(destination, "\n", 1);
        printf ("\nCompleted Copy\n");



    }

    close(fd);
    close(destination);

    printf ("\n\nEnding Program..\n----------------\n\n");
    return 0;
}