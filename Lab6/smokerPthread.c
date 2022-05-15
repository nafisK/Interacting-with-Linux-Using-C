#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h> 
#include <sys/wait.h>	
#include <sys/types.h>	

/*
  Assignment 5 by Nafis Khan
*/

// smokers
void *smokers(void *arg);
void *agent();

// mutexes to be used
pthread_mutex_t match_mutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t paper_mutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tobacco_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t agent_mutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_mutex    = PTHREAD_MUTEX_INITIALIZER;

// all pthreads needed
pthread_t match_pthread, paper_pthread, tobacco_pthread, agent_pthread;

int main() {

  // randomizer using time initialized
  srand(time(0));

  // creating needed locks and unlocks
  pthread_mutex_unlock(&lock_mutex);
  pthread_mutex_lock(&match_mutex);
  pthread_mutex_lock(&paper_mutex);
  pthread_mutex_lock(&tobacco_mutex);
  pthread_mutex_lock(&agent_mutex);
  
  // creating new threads for each process
  // agent() and smokers() are defined below
  pthread_create(&agent_pthread, NULL, agent, NULL);
  pthread_create(&match_pthread, NULL, smokers, (void *) 1); 
  pthread_create(&paper_pthread, NULL, smokers, (void *) 2);
  pthread_create(&tobacco_pthread, NULL, smokers, (void *) 3);
  
  // waiting for agent thread
  pthread_join(agent_pthread, NULL);
  
  // removing or destroying un-needed threads before program ends
  pthread_mutex_destroy(&agent_mutex);
  pthread_mutex_destroy(&tobacco_mutex);
  pthread_mutex_destroy(&paper_mutex);
  pthread_mutex_destroy(&match_mutex);
  pthread_mutex_destroy(&lock_mutex);
  return 0;
  
}

// handles all agent behavior 
void *agent(){

  // runs 10 times using the example given in the question
  int counter = 0; 
  while (counter < 10) {

    // locks the mutex for using singularly 
    pthread_mutex_lock(&lock_mutex);

    // finds a number between 1 to 3 
    int random_number = (rand() % 3) + 1; 

    /* output based on random number */

    // Smoker with match selected
    if (random_number == 1) { 
      printf("\nAgent places tobacco on the table.\n");
      printf("Agent places paper on the table.\n");
      pthread_mutex_unlock(&match_mutex);
    } 
    // Smoker with Paper selected
    else if (random_number == 2) {
      printf("\nAgent places tobacco on the table.\n");
      printf("Agent places match on the table.\n");
      pthread_mutex_unlock(&paper_mutex);
    } 
    // Smoker with Tobacco selected
    else {
      printf("\nAgent places match on the table.\n");
      printf("Agent places paper on the table.\n");
      pthread_mutex_unlock(&tobacco_mutex); 
    }

    // removing the mutex lock and locking the agent so that it waits
    pthread_mutex_unlock(&lock_mutex);
    pthread_mutex_lock(&agent_mutex);
    counter += 1;
  }

  pthread_mutex_lock(&lock_mutex);

  // cancellation request to a thread
  pthread_cancel(paper_pthread);
  pthread_cancel(tobacco_pthread);
  pthread_cancel(match_pthread);
  pthread_mutex_unlock(&lock_mutex);
  return 0;
}

// handles all smoker behavior 
void *smokers(void *arg) {

  // gets the process id to run
  int process_id = (int) arg;
  
  // for smoker with matches
  if (process_id == 1) {
    while(1) {

      // blocking other threads interference
      pthread_mutex_lock(&match_mutex);
      pthread_mutex_lock(&lock_mutex);

      // smoker actions
      printf("Smoker with Matches picks up tobacco from the table.\n");
      printf("Smoker with Matches picks up paper from the table.\n");
      printf("Smoker with Matches makes a cigarette and then smokes it.\n");

      // unblocking other threads interference
      pthread_mutex_unlock(&agent_mutex);
      pthread_mutex_unlock(&lock_mutex);
    }
    
  } 
  // for smoker with paper
  else if (process_id == 2) {
    while(1){
        
      // blocking other threads interference
      pthread_mutex_lock(&paper_mutex);
      pthread_mutex_lock(&lock_mutex);

      // smoker actions
      printf("Smoker with paper picks up tobacco from the table.\n");
      printf("Smoker with paper picks up matches from the table.\n");
      printf("Smoker with paper makes a cigarette and then smokes it.\n");

      // unblocking other threads interference
      pthread_mutex_unlock(&agent_mutex);
      pthread_mutex_unlock(&lock_mutex);
    }

  } 
  // for smoker with tobacco
  else {
    while(1) {

      // blocking other threads interference
      pthread_mutex_lock(&tobacco_mutex);
      pthread_mutex_lock(&lock_mutex);

      // smoker actions
      printf("Smoker with Tobacco picks up matches from the table.\n");
      printf("Smoker with Tobacco picks up paper from the table.\n");
      printf("Smoker with Tobacco makes a cigarette and then smokes it.\n");
      
      // unblocking other threads interference
      pthread_mutex_unlock(&agent_mutex);
      pthread_mutex_unlock(&lock_mutex);

    }
  }
  return 0;
}