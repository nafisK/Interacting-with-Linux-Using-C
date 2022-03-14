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

    char* sourceFile = "source.txt";
    char* fileName1 = "destination1.txt";
    char* fileName2 = "destination2.txt";

    /* creating file descriptors for all necessary files */

    // Only read needed
    int source = open(sourceFile, O_RDONLY);
    // only write needed
    int fd1 = open(fileName1, O_WRONLY);
    int fd2 = open(fileName2, O_WRONLY);

    // error handling the fd's
    if(source < 0){
        printf("%s could not be opened.\n", sourceFile);
        perror("open()");
        return 1;

    } else if (fd1 < 0) {
        printf("%s could not be opened.\n", fileName1);
        perror("open()"); 
        return 1;

    } else if (fd2 < 0){
        printf("%s could not be opened.\n", fileName2);
        perror("open()");
        return 1;

    }



    int read_file;
    char buffer[150];
    char buffer2[150];

    // 150 at a time
    // 0 - 99 goes into destination 1
    // 100 - 149 goes into destination 2
    while((read_file = read(source,buffer,150)) != 0) {
      // Error message if failed to read
      if (read_file < 0) {
        printf("Fail to read.");
        perror("read \n");
        return 1;
      }

      // 1. Read the next 100 characters from source.txt, and among characters read, replace each char-acter ’1’ with character ’L’ and all characters are then written in destination1.txt
      for(int i = 0; i < 100; i++) {
        if(buffer[i] == '1') {
          buffer[i] = 'L';
        }
      }
      for(int i = 100; i < 150; i++) {
        if(buffer[i] == '1') {
          buffer[i] = '1';
        }
      }
      read_file = write(fd1, buffer, read_file); // Write to destination1.txt
      if (read_file < 0) { // Error message if failed to write
        printf("Fail to write to destination1.txt");
        perror("write \n");
        return 1;
      }


      // 2. Then the next 50 characters are read from source.txt, and among characters read, replace each character ’3’ with character ’E’ and all characters are then written in destination2.txt.
      for(int i = 0; i < 100; i++) {
        buffer2[i] = buffer[i];
        if (buffer2[i] == 'L'){
          buffer2[i] = '1';
        }
      }
      for(int i = 100; i < 150; i++) {
        buffer2[i] = buffer[i];
        if (buffer2[i] == '3') {
          buffer2[i] = 'E';
        }
      }
      read_file = write(fd2, buffer2, read_file); // Write to destination1.txt
      if (read_file < 0) { // Error message if failed to write
        printf("Fail to write to destination2.txt");
        perror("write \n");
        return 1;
      }

    }

    

    // Closing files
    if (close(source) < 0) {
        printf("Fail to close source file");
        perror("close");
        return 1;

    } else if (close(fd1) < 0) {
        printf("Fail to close destination1.txt");
        perror("close");
        return 1;

    } else if (close(fd2) < 0) {
        printf("Fail to close destination2.txt");
        perror("close");
        return 1;

    } else {
        printf("\nClosed Successfully. \n");
    }

    return 0;
}

