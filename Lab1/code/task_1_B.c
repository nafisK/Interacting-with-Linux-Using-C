#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 

int main (int argc, char* argv[]) {

    // checks if correct arguments are given
    if(2 != argc) {
        printf("\nPlease provide appropriate arguments.\n");
        return 1;
    }

    printf ("\n ------------------\n| Starting Program |\n ------------------\n\n");

    char* filepath = argv[1];
    // Creates a file descriptor for the file given
    int fd;
    // setting a no problem error value
    errno = 0;

    // opens and creates a file if it DNE
    // Sets file to read and write mode for CURRENT owner/usr
    fd = open(argv[1], O_RDONLY|O_CREAT, S_IRWXU);

    // error handling FD
    if(fd < 0) {
        printf("Filename could not be opened.\n");
        perror("open");
        return 1;  
    }
    
    // error handling if file does not open as expected
    if(-1 == fd) {
        printf("\nOpen failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {
        printf("\bFile Opened Successfully.\n");
    }

    // closing/removing fd from memory
    close(fd);

    printf("\bFile Closed Successfully.\n");
    printf ("\n ----------------\n| Ending Program |\n ----------------\n\n");
    return 0;
}