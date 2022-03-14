#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/*
    Lab 3 by Nafis Khan
*/

int main(int argc, char *argv[]) {
  
    // Name of files
    char* fileName1 = "destination1.txt";
    char* fileName2 = "destination2.txt";


    /* File One */

    // opens in read, write Or creates in read and write mode
    int fd1 = open(fileName1, O_RDONLY | O_WRONLY | O_CREAT, 00700);

    if (fd1 < 0) {
        // error with opening file
        printf("%s could not be opened.\n", fileName1);
        perror("open()"); /* This will explain why */
        return 1;
    } else {
        printf("%s opened Successfully.\n", fileName1);
    }

    // closing file 1
    int close1 = close(fd1);
    // error handling
    if (close1 < 0) {
        printf("Fail to close %i.", close1);
        perror("close");
        return 1;

    } else {
        printf("%s closed Successfully.\n", fileName1);
    }

    /* File Two */

    // opens in read, write Or creates in read and write mode
    int fd2 = open(fileName2, O_RDONLY | O_WRONLY | O_CREAT, 00700);

    if (fd2 < 0) {
        // error with opening file
        printf("%s could not be opened.\n", fileName2);
        perror("open()"); /* This will explain why */
        return 1;
    } else {
        printf("%s opened Successfully.\n", fileName2);
    }

    // closing file 1
    int close2 = close(fd2);
    // error handling
    if (close2 < 0) {
        printf("Fail to close %i.", close2);
        perror("close");
        return 1;

    } else {
        printf("%s closed Successfully.\n", fileName2);
    }

    return 0;
} 