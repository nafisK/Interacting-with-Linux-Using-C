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

int main (int argc, char* argv[]) {

    printf("\nRunning Prcs_P2.c.\n");

    char* sourceFile = "source.txt";
    char* fileName1 = "destination1.txt";
    char* fileName2 = "destination2.txt";

    /* creating file descriptors for all necessary files */

    // Opening to read
    int source = open(sourceFile, O_RDONLY);
    // Opening to write
    int fd1 = open(fileName1, O_WRONLY);
    int fd2 = open(fileName2, O_WRONLY);

    // error handling all the fd's
    if(source < 0){
        printf("%s could not be opened.\n", sourceFile);
        perror("open()");
        return 1;
    } 
    if (fd1 < 0) {
        printf("%s could not be opened.\n", fileName1);
        perror("open()"); 
        return 1;

    } 
    if (fd2 < 0){
        printf("%s could not be opened.\n", fileName2);
        perror("open()");
        return 1;
    }


    /* Reading and Writing to all files using FD's */
    int read_file;
    char mainBuffer[150];
    char destOneBuffer[100];
    char destTwoBuffer[50];

    // 0 - 99 goes into destination 1
    // 100 - 149 goes into destination 2
    while(read(source, mainBuffer, 150) != 0) {

        // copying first 100 chars to separate buffer
        for(int i = 0; i < 100; i++) {
            if(mainBuffer[i] == '1') 
                destOneBuffer[i] = 'L';
            else 
                destOneBuffer[i] = mainBuffer[i];
        }

        // writing 100 chars to destination 1 
        if (write(fd1, destOneBuffer, sizeof(destOneBuffer)) < 0) {
            printf("Could not write to %s.\n", fileName1);
            perror("write()\n");
            return 1;
        }

        // copying next 50 chars to separate buffer
        int destIndex = 0;
        for(int i = 100; i < 150; i++) {
            if(mainBuffer[i] == '3') 
                destTwoBuffer[destIndex] = 'E';
            else 
                destTwoBuffer[destIndex] = mainBuffer[i];
            destIndex++;
        }

        // writing 50 chars to destination 2
        if (write(fd2, destTwoBuffer, sizeof(destTwoBuffer)) < 0) {
            printf("Could not write to %s.\n", fileName2);
            perror("write()\n");
            return 1;
        }

    }

    // Closing/Unlinking files
    if (close(source) < 0) {
        printf("Failed to close %s file.", sourceFile);
        perror("close");
        return 1;

    } 
    if (close(fd1) < 0) {
        printf("Failed to close %s file.", fileName1);
        perror("close");
        return 1;

    } 
    if (close(fd2) < 0) {
        printf("Failed to close %s file.", fileName2);
        perror("close");
        return 1;

    } 
    
    printf("Successfully Copied Data and Files Closed Successfully.\n");

    return 0;
}

