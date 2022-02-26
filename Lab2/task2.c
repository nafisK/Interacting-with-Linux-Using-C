#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/*
Assignment 2 by Nafis Khan
*/

int main (int argc, char* argv[]) {

    // checks if correct arguments are given
    if(1 != argc) {
        printf("\nPlease provide appropriate arguments.\n");
        return 1;
    }

    int a = 10,
        b = 25,
        fq = 0,
        fr = 0;

    fq = fork();

    if (fq == 0) {
        a = a + b;
        // print vals of a, b and process_id

        fr = fork();
        if (fr != 0) {
            b = b + 20;
            // print values of a, b and process_id

        } 
        else {
        a = (a * b) + 30;
        // print values of a, b and process_id

        }   
    }
    else {
        b = (a + b) - 5;
        // print values of a, b and process_id
        
    }
    



    return 0;
}
