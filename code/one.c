#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 

int main (int argc, char* argv[]) {

    printf ("\nStarting..\n\n");


    /* Task 1.a */

    char* filepath = argv[1];
    int returnval;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0)
        printf ("\b%s file exists\n", filepath);
    else {
        if (errno == ENOENT)
        printf ("%s does not exist\n", filepath);
        else if (errno == EACCES)
        printf ("%s is not accessible\n", filepath);
    }

    // Check read access
    returnval = access (filepath, R_OK);
    if (returnval == 0)
        printf ("\b%s file is readable.\n", filepath);
    else {
        if (errno == ENOENT)
        printf ("%s does not exist\n", filepath);
        else if (errno == EACCES)
        printf ("%s is not accessible\n", filepath);
    }

    // Check write access
    returnval = access (filepath, W_OK);
    if (returnval == 0)
        printf ("\b%s file is writeable.\n", filepath);
    else {
        if (errno == ENOENT)
        printf ("%s does not exist\n", filepath);
        else if (errno == EACCES)
        printf ("%s is not accessible\n", filepath);
    }


    /* Task 1.b */

    // Creates new file and opens it
    int fd;

    if(2 != argc) {
        printf("\n Usage : \n");
        return 1;
    }

    errno = 0;
    // opens and creates a file if it DNE
    fd = open(argv[1], O_RDONLY|O_CREAT);
    // fd = open(argv[1], O_RDONLY);

    if(-1 == fd) {
        printf("\n open() failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {
        printf("\n Open() Successful\n");
    
        /* open() succeeded, now one can do read operations on the file
        since we opened it in read-only mode. Also once done with
        processing, the file needs to be closed. */

    }




    close(fd);
    printf ("\n\nEnding..\n\n");
    return 0;
}