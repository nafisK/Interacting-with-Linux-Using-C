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
    int returnval;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0)
        printf ("\b%s file exists.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist.\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible.\n", filepath);
    }

    /* TASK 1.a */    

    // Checks read access
    returnval = access (filepath, R_OK);
    // Resetting Error Number
    errno = 0;
    if (returnval == 0)
        printf ("\b%s file is readable.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist. Cannot be read from.\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible.\n", filepath);
    }

    // Check write access
    returnval = access (filepath, W_OK);
    // Resetting Error Number
    errno = 0;
    if (returnval == 0)
        printf ("\b%s file is writeable.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist. Cannot be written to.\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible.\n", filepath);
    }

    printf ("\n ----------------\n| Ending Program |\n ----------------\n\n");
    return 0;
}