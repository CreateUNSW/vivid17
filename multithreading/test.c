#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "c11threads.h"
//#include <SFML/Graphics.h>

#define NUM_THREADS 8
#define TASK_SIZE 10000 * 10000// * NUM_THREADS

static int threadData[NUM_THREADS];
int *arrayToSearch;

int threadFunction(void * data) {
   printf("%d-th thread up\n", *(int*)data);

   printf("%d - %d\n", (TASK_SIZE/NUM_THREADS)*(*(int*)data), (TASK_SIZE/NUM_THREADS)*(*(int*)data + 1) - 1);

   for(int i = (TASK_SIZE/NUM_THREADS)*(*(int*)data); i < (TASK_SIZE/NUM_THREADS)*(*(int*)data + 1) - 1; i++) {
      if(arrayToSearch[i] == 99999999) {
         abort();
      }
   }
   return 0;
}

int main(void) {

   int i = 0;
   thrd_t threadId[NUM_THREADS];

   // init thread data
   for(i = 0; i < NUM_THREADS; ++i) {
      threadData[i] = i;
   }

   // Creates data to search through
   arrayToSearch = malloc(sizeof(int) * TASK_SIZE);

   for(i = 0; i < TASK_SIZE; i++) {
      arrayToSearch[i] = i;
   }

   // start NUM_THREADS amount of threads
   for(i = 0; i < NUM_THREADS; ++i) {
      if(thrd_create(threadId+i, threadFunction, threadData+i) != thrd_success) {
         printf("%d-th thread create error\n", i);
         return 0;
      }
   }

   // wait until all threads terminates
   for(i=0; i < NUM_THREADS; ++i) {
      thrd_join(threadId[i], NULL);
   }

   return 0;
}