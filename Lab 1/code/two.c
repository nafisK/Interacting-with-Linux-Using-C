#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 
#include <limits.h>


int main (int argc, char* argv[]) {

    printf ("\nStarting..\n\n");

    /* TODO 
        1. takes file as argv
        2. reports if it doesn't exist or cant be opened(no read perm)
        3. use open() -> read() -> write() -> close()
    */


    /* Task 2 */

    char* filepath = argv[1];
    int returnval;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0) 
        printf ("\b%s file exists.\n", filepath);
    else {
        if (errno == ENOENT) {
        printf ("%s does not exist\nEnding Program", filepath);
        }
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
            printf ("%s is not accessible for read.\n", filepath);
    }

    // Check write access
    returnval = access (filepath, W_OK);
    if (returnval == 0)
        printf ("\b%s file is writeable.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible for write.\n", filepath);
    }


    /* Task 2 */

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
        printf("\nOpen() failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {
        printf("\nFile Opened Succesfully.\n");
        
        char data[1024]; 
        int num_bytes = 1024;
        int length;

        /* open() succeeded, now one can do read operations on the file
        since we opened it in read-only mode. Also once done with
        processing, the file needs to be closed. */
        read(fd, data, num_bytes);
        // write(fd, data, num_bytes);
        // printf("\nData in File:\n%s", data);
        while ((length = read (fd, data, num_bytes)) > 0 ) {
            printf("\nData in File:\n%s", data);
        }

    }

    close(fd);
    printf ("\n\nEnding..\n\n");
    return 0;
}