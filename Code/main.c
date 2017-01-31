#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Graph.h"

int main(int argc, char *argv[]) {

   int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{1, 2, 3, -1},
                                                            {2, 4, -1},
                                                            {-1},
                                                            {-1},
                                                            {-1}};

   Graph g = readGraph(edges);

   int *dist = calcDist(g, 0);

   int i = 0;

   printf("\n");
   for(i = 0; i < (numV(g) - 1) * 2; i++) {
      printf("%d, ", dist[i]);
   }

   printf("\n");

   return EXIT_SUCCESS;
}