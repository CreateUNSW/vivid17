#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include "c11threads.h"
//#include <SFML/Graphics.h>

#define TASK_SIZE 10000 * 10000

int numThreads = 1;
int *arrayToSearch;


int threadFunction(void * data) {
   printf("%d-th thread up\n", *(int*)data);

   for(int i = (TASK_SIZE/numThreads)*(*(int*)data); i < (TASK_SIZE/numThreads)*(*(int*)data + 1); i++) {
      if(arrayToSearch[i] == 99999999) {
         printf("\nTASKS FINISHED\n");
         return 0;
      }
   }
   return 0;
}

int main(int argc, char *argv[]) {

   if(argc > 1 && atoi(argv[1]) > 0) {
      numThreads = atoi(argv[1]);
   } else {
      if(atoi(argv[1]) < 1) {
         printf("Number of threads must be > 0\n");
         numThreads = 0;
      }
      while(numThreads < 1) {
         printf("Enter number of threads: ");
         scanf("%d", &numThreads);
      }
   }

   // Keeps track of the threads used
   int threadData[numThreads];

   int i = 0;
   thrd_t threadId[numThreads];

   printf("\nUSING %d/%ld CORES\n"
          "--------------\n", numThreads, sysconf(_SC_NPROCESSORS_ONLN));

   // init thread data
   for(i = 0; i < numThreads; ++i) {
      threadData[i] = i;
   }

   // Creates data to search through
   arrayToSearch = malloc(sizeof(int) * TASK_SIZE);

   for(i = 0; i < TASK_SIZE; i++) {
      arrayToSearch[i] = i;
   }


   struct timeval  tv1, tv2;
   gettimeofday(&tv1, NULL);

   // start numThreads amount of threads
   for(i = 0; i < numThreads; ++i) {
      if(thrd_create(threadId+i, threadFunction, threadData+i) != thrd_success) {
         printf("%d-th thread create error\n", i);
         return 0;
      }
   }

   // wait until all threads terminates
   for(i=0; i < numThreads; ++i) {
      thrd_join(threadId[i], NULL);
   }

   gettimeofday(&tv2, NULL);

   printf("--------------\n");

   printf("t(%d): %fs\n\n", numThreads,
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

   return 0;
}


/*
// For some reason, this code scales better with more threads
// USE #DEFINE FOR FINAL CODE, could have something to do with the
//                             precompiler working better with threads

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "c11threads.h"
//#include <SFML/Graphics.h>

#define NUM_THREADS 8
#define TASK_SIZE 10000 * 10000// * NUM_THREADS

int *arrayToSearch;

int threadFunction(void * data) {
   printf("%d-th thread up\n", *(int*)data);

   //printf("%d - %d\n", (TASK_SIZE/NUM_THREADS)*(*(int*)data), (TASK_SIZE/NUM_THREADS)*(*(int*)data + 1) - 1);

   for(int i = (TASK_SIZE/NUM_THREADS)*(*(int*)data); i < (TASK_SIZE/NUM_THREADS)*(*(int*)data + 1) - 1; i++) {
      if(arrayToSearch[i] == 99999999) {
         printf("RETURNED\n");
         return 0;
      }
   }
   return 0;
}

int main(void) {
   
   // Keeps track of the threads used
   static int threadData[NUM_THREADS];

   int i = 0;
   thrd_t threadId[NUM_THREADS];

   printf("--------------\n");

   // init thread data
   for(i = 0; i < NUM_THREADS; ++i) {
      threadData[i] = i;
   }

   // Creates data to search through
   arrayToSearch = malloc(sizeof(int) * TASK_SIZE);

   for(i = 0; i < TASK_SIZE; i++) {
      arrayToSearch[i] = i;
   }


   struct timeval  tv1, tv2;
   gettimeofday(&tv1, NULL);

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

   gettimeofday(&tv2, NULL);

   printf("--------------\n");

   printf("Time = %fs\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

   return 0;
}
*/