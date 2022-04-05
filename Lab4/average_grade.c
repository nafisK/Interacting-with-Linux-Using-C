#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Lab 4 - Nafis Khan

int main(int argc, char* argv[]) {

    if(2 != argc) {
        printf("\nPlease add the grades file name as an argument. Retry.\n");
        return 1;
    }

    // x = num of chapts || y = num of hw's in each chapter || numStudents = total number of students in file
    int x;                                  
    int y;                                  
    int numStudents = 10;

    // member vars needed for program
    int currentHomework = 0;
    int plv;
    double total_score = 0; 

    // User input
    printf("\nEnter the number of chapters is the file: ");
    scanf("%d", &x);
    printf("Enter the number of homeworks in each chapter: "); 
    scanf("%d", &y);
    printf("\n");

    // Main Program Process
    const int numHomeworks = x * y;                         // finding number of columns
    double hwGrades[numHomeworks][numStudents];             // 2D array for storing the grades    
    double avgGrade[numHomeworks];                          // stores all the final average grades

    
    char* fileName = argv[1];
    FILE *file = fopen(fileName, "read");

    // reading and storing grades into array
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < numHomeworks; j++) {
            fscanf(file, "%lf", &hwGrades[j][i]);
        }
    }

    // looping through each chapter and each hw
    for (int chapterCounter = 0; chapterCounter < x; chapterCounter++) {
        wait(&plv);

        // creating manager process. x number of processes are created
        pid_t managerProcess = fork();
        if(managerProcess == 0) {

            // current hw val
            currentHomework = y * chapterCounter;

            for(int homeworkCounter = 0; homeworkCounter < y; homeworkCounter++) {
                wait(&plv);

                // creating worker process. y number of processes are created
                pid_t workerProcess = fork();
                if(workerProcess == 0) {

                    for (int i = 0; i < numStudents; i++){
                        // total of each column vals or homework
                        total_score += hwGrades[currentHomework][i];
                    }

                    // calculating the average of each homework and storing in array
                    avgGrade[currentHomework] = total_score / numStudents;
                    printf("Chapter: %d, Homework: %d \nAverage Grade: %.2f.\n\n", (chapterCounter + 1), (homeworkCounter + 1), avgGrade[currentHomework]);
                    exit(0); 
                } 
                // error handling for worker process
                else if (workerProcess < 0) {
                    perror("Error with worker process.");
                }
                // error handling with the wait() function
                else {
                    if(wait(&plv) == -1) {
                        perror("Error with worker process.");
                    }
                }
                // incrementing to the next homework in the chapter
                currentHomework++;
            }
            exit(0);
        }
        else if(managerProcess < 0) { // Manager process failed
                perror("Manager Error");
            return 1;
        }
        else {
            if(wait(&plv) == -1) { // At wrong level
                printf("Manager Error\n");
            }
        }
    }

    // closes file
    fclose(file); 
    return 0;
}