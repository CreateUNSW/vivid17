#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "Graph.h"

int main(int argc, char *argv[]) {

   int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{-1},
                                                            {3, 4, 2, 7, 6, 5, 16, 15, 18, -1},
                                                            {4, 9, 8, 7, 6, 1, 3, -1},
                                                            {12, 11, 4, 2, 1, 16, 15, 18, 13, -1},
                                                            {11, 10, 9, 2, 1, 3, 12, -1},
                                                            {1, 6, 16, -1},
                                                            {1, 2, 7, 5, -1},
                                                            {2, 9, 8, 6, 1, -1},
                                                            {9, 7, 2, -1},
                                                            {10, 8, 7, 2, 4, 11, -1},
                                                            {9, 4, 11, -1},
                                                            {10, 9, 4, 3, 12, -1},
                                                            {11, 4, 3, 18, 13, -1},
                                                            {12, 3, 18, 17, -1},
                                                            {16, 5, -1},
                                                            {18, 3, 1, 16, -1},
                                                            {15, 18, 3, 1, 6, 5, 14, -1},
                                                            {13, 18, -1},
                                                            {17, 13, 12, 3, 1, 16, 15, -1}};

   Graph g = readGraph(edges);

   int i = 0;
   int src = 0;
   int *dist = NULL;
   printf("INDEX: ");
   for(i = 0; i < numV(g); i++) {
      printf("%2d ", i);
   }
   printf("\n");


   for(src = 0; src < MAX_CRYSTALS_NUM; src++) {
      printf("OG %2d: ", src);
      dist = calcDist(g, src);
      for(i = 0; i < numV(g); i++) {
         if(dist[i] != INT_MAX) {
            printf("%2d ", dist[i]);
         } else {
            printf(" - ");
         }
      }
      printf("\n");
      free(dist);
   }

   return EXIT_SUCCESS;
}