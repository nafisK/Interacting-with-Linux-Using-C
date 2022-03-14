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

int main(void) 
{
	int fd1, fd2;

	errno = 0;
    // Opens or Creates 'destination.txt' file with read and write permission
    char* file1 = "destination1.txt";
    char* file2 = "destination2.txt";

	fd1 = open(file1, O_CREAT | O_RDWR, S_IRWXU);
													
	if (fd1 == -1) {
		printf("Failed to open(): [%s]\n", strerror(errno));
	}
	else {
		printf("%s opened successfully\n", file1);
	}
	close(fd1);

	
	fd2 = open(file2, O_CREAT | O_RDWR, S_IRWXU); // Opens and creates "destination2.txt" with read-write permissions.

	if (fd2 == -1) {
		printf("Failed to open(): [%s]\n", strerror(errno));
	}
	else {
		printf("%s opened successfully\n", file2);
	}

	close(fd2);

return 0;
}
