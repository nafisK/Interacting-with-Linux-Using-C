#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "sem.h"

/*
  Assignment 5 by Nafis Khan
*/

int main() {
  // Setting up variables
  int pid, status;
  int counter = 0;

  // semaphores needed
  int matches_sem = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
  int paper_sem   = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
  int tobacco_sem = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
  int agent_sem   = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
  int lock_sem    = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);

  /* creating all semaphores */
  // initialized to 0
  sem_create(matches_sem, 0);
  sem_create(paper_sem, 0);
  sem_create(tobacco_sem, 0);
  sem_create(agent_sem, 0);

  // initialized to 1
  sem_create(lock_sem, 1);

  // error handling
  if ((pid = fork()) == -1) {
		perror("fork");
		exit(1);
	}
  
  // First child - Agent process
  if (pid == 0) { 

    // repeats x number of times as mentioned in the prompt
    while (counter < 10) {
      // locking semaphore
      P(lock_sem);

      // getting a random number between 1 - 3 to pick what to put on table as the Agent
      int random_number = (rand() % 3) + 1;

      // tobacco and paper
      if (random_number == 1) {

        // agent actions
        printf("\nAgent places tobacco on the table.\n");
        printf("Agent places paper on the table.\n");
        // waking up smoker with match
        V(matches_sem);

      } 
      // tobacco and match
      else if (random_number == 2) {

        // agent actions
        printf("\nAgent places tobacco on the table.\n");
        printf("Agent places match on the table.\n");
        // waking up smoker with paper
        V(paper_sem);

      } 
      // match and paper
      else {

        // agent actions
        printf("\nAgent places match on the table.\n");
        printf("Agent places paper on the table.\n");
        // waking up smoker with tobacco
        V(tobacco_sem);

      }

      // lock_sem wakes up and putting agent to sleep
      V(lock_sem); 
      P(agent_sem);
      counter += 1;
    }
  } 

  // parent process
  else {

    // error handling
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(1);
    }
  
    // second child - tobacco process 
    if (pid == 0) {
      while(1) {

        // tobacco and lock sem sleeps
        P(tobacco_sem);
        P(lock_sem);

        // action texts
        printf("Smoker with Tobacco picks up matches from the table.\n");
        printf("Smoker with Tobacco picks up paper from the table.\n");

        // waking up agent and lock_sem
        V(agent_sem);
        V(lock_sem);

        // action text
        printf("Smoker with Tobacco makes a cigarette and then smokes it.\n");
      }
    } else {

      // parent process, forking for another child process.
      if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
      }
    
      // third child - paper smoker process 
      if (pid == 0) {
        while(1) {

          // paper and lock_sem sleeps
          P(paper_sem);
          P(lock_sem);

          // action texts
          printf("Smoker with Paper picks up tobacco from the table.\n");
          printf("Smoker with Paper picks up matches from the table.\n");

          // paper and lock_sem wakes up
          V(agent_sem);
          V(lock_sem);

          // action text
          printf("Smoker with Paper makes a cigarette and then smokes it.\n");
        }
      } else {

        // parent process, forking for another child process.
        if ((pid = fork()) == -1) {
          perror("fork");
          exit(1);
        }
      
        // fourth child - matches smoker process 
        if (pid == 0) {
          while(1){

            // matches and lock_sem sleeps
            P(matches_sem); 
            P(lock_sem);

            // action texts
            printf("Smoker with Matches picks up tobacco from the table.\n");
            printf("Smoker with Matches picks up paper from the table.\n");
            
            // matches and lock_sem wakes up
            V(agent_sem);
            V(lock_sem);

            // action text
            printf("Smoker with Matches makes a cigarette and then smokes it.\n");
          }
        } else {
          
          // End process printout
          pid = wait(&status);
          printf("\nProcess with pid = %d exited with the status %d. \n", pid, status);
        }
      }
    }
  }
}
