// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Graph function implementations for COMP1927 17x1 AE2.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"
#include "Agent.h"
#include "Queue.h"
#include "PQ.h"
#include "Item.h"

#define OFF 0
#define ON 1
#define DEBUGGING OFF

#define NRM "\x1B[0m"
#define BLD "\x1B[1m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"

#define NO_EDGE INT_MAX
#define DO_ABORT 1
#define NO_ABORT 0
#define MALLOC_ERR "Out of memory. Exiting program."

struct graphRep { 
   // Stores number of vertices in graph (doubles as storing
   // dimensions of the 2d array, adj)
   int nV;
   // Stores number of edges in graph, doubles as max size for es
   // arrat in edges() function
   int nE;
   // 2d array storing weights of edges between edge v and w
   // eg. Weight of edge between v and w would be adj[v][w]
   // NOTE: if no edge is present, matrix entry will be 
   //       NO_EDGE, which equals INT_MAX
   int **adj;
   // An array of cities (structs containing information on each vert)
   // NOTE: each index contains information on that vert,
   //       ie. cities[4] contains information on vert 4
   City *cities;
};

// -------------------------
// Internal helper functions
// -------------------------
City static mkCity(int informant, char *name);

void static dfs(Graph g, Edge e, Vertex *pre, int count,
                int *planProgress, Vertex *plan);
void static bfs(Graph g, Edge e, Vertex *pre, Vertex *st, int count,
                int *planProgress, Vertex *planint, int currStamina,
                int maxStamina);

void static createMatrix(Graph g, int nV);
void static printMatrix(Graph g);


// --------------
// City functions
// --------------
City static mkCity(int informant, char *name) {

   if(name == NULL) {
      printError("Valid name string must be passed in.", DO_ABORT);
   }

   City c;
   c.informant = informant;
   c.name = strdup(name);

   return c;
}

void insertCity(Graph g, Vertex v, char informant, char *name) {

   if(v >= numV(g)) {
      printError("Vertex for city must be valid.", DO_ABORT);
   }

   if(informant == 'n') {
      g->cities[v] = mkCity(OFF, name);
   } else if(informant == 'i') {
      g->cities[v] = mkCity(ON, name);
   } else {
      printError("Informant flag must be 0 or 1.", DO_ABORT);
   }
}

int hasInformant(Graph g, Vertex v) {
   if(g->cities[v].informant == ON) {
      return 1;
   } else {
      return 0;
   }
}

char *getCityName(Graph g, Vertex v) {

   return g->cities[v].name;
}

// ---------------
// Graph functions
// ---------------

// Create an edge from v to w (allowing for self-edges)
Edge mkEdge(Vertex v, Vertex w, int weight) { 
   // NOTE: weight != INT_MAX check is done as INT_MAX is used as a
   //       magic number for NO_EDGE, and hence no edge would be
   //       created if the function were to proceed
   if(weight == NO_EDGE) {
      printError("No edge created.", NO_ABORT);
      // NOTE: abort() is not used as the error is not critical,
      //       that weight would just be interpreted as NO_EDGE in
      //       the matrix
   }
   if(v < 0 || w < 0 ) {
      printError("'v' and/or 'w' invalid.", DO_ABORT);
   }
   Edge e = {v, w, weight}; 
   return e; 
} 

// Creates g's adjacency matrix
void static createMatrix(Graph g, int nV) {

   int i = 0;
   int j = 0;

   // malloc's the array to store the column arrays for each row entry
   g->adj = malloc(sizeof(int *) * nV);
   mallocCheck(g->adj);
   // malloc's each column array and attaches it to the row array
   // NOTE: this is done as C doesn't have native support for 
   //       dynamically allocated matrices
   for(i = 0; i < nV; i++) {
      g->adj[i] = malloc(sizeof(int) * nV);
      mallocCheck(g->adj[i]);
      for(j = 0; j < nV; j++) {
         g->adj[i][j] = NO_EDGE;
      }
      // Also initialises name strings in cities array to NULL
      g->cities[i].name = NULL;
   }
}

//Initialise a new graph
Graph newGraph(int nV) {
   // Ensures nV is valid, ie is greater than 0
   // NOTE: if nV == 0, function with just create an empty graph, with
   //       its adj matrix malloc'd 0 space.
   if(nV < 0) {
      printError("Number of vertices must be >= 0.", DO_ABORT);
   }

   // Creates graph wrapper struct
   Graph g = malloc(sizeof(*g));
   mallocCheck(g);
   // Initialises graph info
   g->nV = nV;
   g->nE = 0;

   g->cities = malloc(sizeof(City) * nV);
   mallocCheck(g->cities);

   // Allocates memory to g's adjacency matrix, and initialises all
   // its entries to NO_EDGE
   createMatrix(g, nV);

   return g;
}

// Insert an edge into a graph the edge must not be inserted if the 
// vertices are not valid it would create a self loop there already 
// exists an edge between the vertices
void insertE(Graph g, Edge e) { 
   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   // Silently skips insertion if edge would create self-loop,
   //                          if vertices are invalid, or
   //                          if edge already exists.
   if(e.v == e.w || e.v >= numV(g) || e.w >= numV(g) ||
         g->adj[e.v][e.w] != NO_EDGE || g->adj[e.w][e.v] != NO_EDGE) {
      return;
   }

   g->adj[e.v][e.w] = e.weight;
   g->adj[e.w][e.v] = e.weight;
   g->nE++;

   if(DEBUGGING == ON) {
      printMatrix(g);
      show(g);
   }
} 

//returns 1 if there is an edge from v to w
//returns 0 otherwise
int isAdjacent(Graph g, Vertex v, Vertex w){

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   } else if((v < 0 || v >= numV(g)) || (w < 0 || w >= numV(g))) {
      if(v < 0 || v >= numV(g)) {
         printf(BLD"v: %d, numV(g): %d\n", v, numV(g));
         printError("'v' is invalid.", NO_ABORT);
      }
      if(w < 0 || w >= numV(g)) {
         printf(BLD"w: %d, numV(g): %d\n", w, numV(g));
         printError("'w' is invalid.", NO_ABORT);
      }
      abort();
   }

   if(g->adj[v][w] != NO_EDGE || g->adj[v][w] != NO_EDGE) {
      return 1;
   } else {
      return 0;
   }
}

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]) {

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   } else if(v < 0 || v >= numV(g)) {
      printError("'v' is invalid.", DO_ABORT);
   } else if(adj == NULL) {
      printError("'adj' array passed in must be valid.", DO_ABORT);        
   }

   int i = 0;
   int adjV = 0;
   for(i = 0; i < numV(g); i++) {
      if(g->adj[v][i] != NO_EDGE) {
         adj[adjV] = g->adj[v][i];
         adjV++;
      }
   }

   return adjV;
}

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]) {

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   } else if(v < 0 || v >= numV(g)) {
      printError("'v' is invalid.", DO_ABORT);
   } else if(edges == NULL) {
      printError("'edges' array passed in must be valid.", DO_ABORT);        
   }

   int w = 0;
   int incidentE = 0;

   for(w = 0; w < g->nV; w++) {
      if(g->adj[v][w] != NO_EDGE) {
         edges[incidentE] = mkEdge(v, w, g->adj[v][w]);
         incidentE++;
      }
   }

   return incidentE;
}

void destroyGraph(Graph g) {

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   int i = 0;
   for(i = 0; i < g->nV; i++) {
      // Frees memory malloc'd for city names
      if(g->cities[i].name != NULL) {
         free(g->cities[i].name);
      }
      // Frees columns of adjacency matrix
      free(g->adj[i]);
   }
   // Frees rows of adjacency matrix
   free(g->adj);
   // Frees cities array
   free(g->cities);

   // Frees the graph itself
   free(g);
}

//return the number of vertices in the graph
int numV(Graph g){

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   return g->nV;
}

//return the number of edges in the graph
int numE(Graph g){

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   return g->nE;
}

// Returns the weight of an edge
int weightE(Graph g, Vertex v, Vertex w) {
   return g->adj[v][w];
}

// returns the number of edges and fills the array of edges.
// nE is the max size of the es array
// The edges in the edges function should be in ascending order and not 
// contain duplicates. 
int edges(Edge es[], int nE, Graph g) {

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   } else if(es == NULL) {
      printError("'es' array passed in must be valid.", DO_ABORT);
   }

   int i = 0;
   int j = 0;
   int edgeCount = 0;

   for(i = 0; i < numV(g); i++) {
      for(j = i; j < numV(g); j++) {
         if(g->adj[i][j] != NO_EDGE) {
            // Only fills es[] if there's enough room, else just
            // skips and keeps counting the correct num of edges
            if(edgeCount < nE) {
               es[edgeCount] = mkEdge(i, j, g->adj[i][j]);
            }
            edgeCount++;
         }
      }
   }
   return edgeCount;
}

// Recursive element of dfSearch function (note this adds)
void static dfs(Graph g, Edge e, Vertex *pre, int count,
                int *planProgress, Vertex *plan) {

   int i = 0;

   // Marks the vertex as visited with its visit order
   pre[e.w] = count++;

   // Prevents writing to the plan if it's visiting the first vertex
   if(pre[e.w] != 0) {
      plan[*planProgress] = e.w;
      (*planProgress)++;
   }

   for(i = 0; i < numV(g); i++) {
      // If i is adjacent to e.w, and has not yet been visited
      if(isAdjacent(g, e.w, i) == 1 && pre[i] == -1) {
         // Does a DFS on it
         dfs(g, mkEdge(e.w, i, weightE(g, e.w, i)), pre, count, 
             planProgress, plan);
      }
   }

   // Prevents writing to the plan at the final stack frame exit
   if(pre[e.w] != 0) {
      plan[*planProgress] = e.v;
      (*planProgress)++;
   }

}

// NOTE: Assumes that graph is entirely connected, so the
//       maximum moves (including backtracks) it will have to
//       make is numE(g) * 2, which the Vertex arrays will
//       have to be malloc'd to accommodate.
//
//       It should also be noted that legal moves are not considered
//       in plan generation (if 6->7 is in a plan, and the weight 
//       exceeds the agent's max stamina, it WILL get stuck)
// Returns the length of the plan
int dfSearch(Graph g, Vertex start, Vertex *plan) {

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   int i = 0;
   int count = 0;
   int planProgress = 0;

   Vertex *pre = malloc(sizeof(int) * numV(g));
   mallocCheck(pre);

   // Initialises all to "unfilled" state
   for(i = 0; i < numV(g); i++) {
      pre[i] = -1;
   }

   // NOTE: DFS only needs to go to all vertices connected to start and
   //       mkEdge(start, start, 0) creates a dummy edge to work from
   dfs(g, mkEdge(start, start, 0), pre, count, &planProgress, plan);

   free(pre);

   return planProgress;
}

void static bfs(Graph g, Edge e, Vertex *pre, Vertex *st, int count,
                int *planProgress, Vertex *plan, int currStamina,
                int maxStamina) {

   int i = 0;
   // Creates the bfs queue
   Queue q = newQueue();
   // Makes the dummy edge join the queue to work off
   joinQueue(q, e);
   // Keeps going until the queue is emptied
   while(queueSize(q) != 0) {
      // Pulls the earliest-in edge from the queue
      e = leaveQueue(q);
      printf("Visit %d\n",e.w);
      // Searches for adjacent edges
      for (i = 0; i < numV(g); i++) {
         // If i is adjacent to e.w, and has not yet been visited
         if(isAdjacent(g, e.w, i) == 1 && pre[i] == -1) {
            // Insertes move e.w->i into the queue
            joinQueue(q, mkEdge(e.w, i, weightE(g, e.w, i)));
            pre[i] = count++;
            st[i] = e.w;
         }
      }
   }
}

int leastTurnsPath(Graph g, Vertex start, Vertex dest, Vertex *plan,
                   int currStamina, int maxStamina) {

// REWRITE THIS ALL TO USE dijkstra INSTEAD, AND WRITE pq.c

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   int i = 0;
   int count = 0;
   int planProgress = 0;

   Vertex *pre = malloc(sizeof(Vertex) * numV(g));
   mallocCheck(pre);
   Vertex *st = malloc(sizeof(Vertex) * numV(g));
   mallocCheck(st);

   // Initialises all to "unfilled" state
   for(i = 0; i < numV(g); i++) {
      pre[i] = -1;
      st[i] = -1;
   }

   bfs(g, mkEdge(start, start, 0), pre, st, count, &planProgress, plan,
       currStamina, maxStamina);

   for(i = 0; i < numV(g); i++) {
      printf("%d, ", pre[i]);
   }
   printf("\n");

   for(i = 0; i < numV(g); i++) {
      printf("%d, ", st[i]);
   }
   printf("\n");

   return planProgress;
}

void dijkstra(Graph g,Vertex s,int st[],int dist[]){
    int v,t;
    PriQ pq = initPriQ(g->nV);
    Item temp;
    //insert each vertex into the pq
    for(v=0;v< g->nV;v++){
        st[v] = -1;
        dist[v] = NO_EDGE; //represents infinity
        Item i = newItem(dist[v],v);
        insert(pq,i);
    } 
    dist[s] = 0.0; //set start veretex dist to 0 
    decreaseWeight(pq,s,dist[s]); // update pq
    while(!isEmpty(pq)){
         temp = delMin(pq);
         v = value(temp);
         if(dist[v] != NO_EDGE)
             for(t = 0;t < g->nV;t++){
            if(g->adj[v][t] != NO_EDGE){
                if(dist[v] + g->adj[v][t] < dist[t]){                    
                    dist[t] = dist[v] + g->adj[v][t];
                         decreaseWeight(pq,t,dist[t]);
                         st[t] = v;
                }
             }
         }
         free(temp);
    }

    destroyPriQ(pq);
}

//Display the graph
void show(Graph g) { 

   if(g == NULL) {
      printError("The graph passed in must exist.", DO_ABORT);
   }

   printf("V=%d, E=%d\n", numV(g), numE(g)); 
   int i, j; 
   for (i = 0; i < numV(g); i++) { 
      int nshown = 0; 
      for (j = 0; j < numV(g); j++) { 
         if (isAdjacent(g,i,j)) {
            printf("%d-%d : %d ", i, j, g->adj[i][j]); 
            nshown++; 
         } 
      } 
      if (nshown > 0){
         printf("\n"); 
      }
   } 
}

void static printMatrix(Graph g) {

   int i = 0;
   int j = 0;
   for(i = 0; i < numV(g); i++) {
      for(j = 0; j < numV(g); j++) {
         if(g->adj[i][j] != NO_EDGE) {
            printf(" %2d,", g->adj[i][j]);
         } else {
            printf("   ,");
         }
      }
      printf("\n");
   }
}

void printError(char *message, int abortFlag) {

   fprintf(stderr, RED"ERROR: %s"NRM"\n", message);
   if(abortFlag == DO_ABORT) {
      abort();
   }
}

void mallocCheck(void *new) {
   if(new == NULL) {
      printError(MALLOC_ERR, DO_ABORT);
   }
}



Graph readGraph(int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1]) {

   int crystalNum = MAX_CRYSTALS_NUM;

   int i = 0;
   int j = 0;

   Graph g = newGraph(crystalNum);

   for(i = 0; i < crystalNum; i++) {
      j = 0;
      while(edges[i][j] != -1) {
         insertE(g, mkEdge(i, edges[i][j], 1));
         j++;
      }
   }

   
   return g;
}

int *calcDist(Graph g, int origin) {

   int i = 0;

   Vertex *dist = malloc(sizeof(Vertex) * MAX_CRYSTALS_NUM);
   Vertex *st = malloc(sizeof(Vertex) * MAX_CRYSTALS_NUM);

   for(i = 0; i < MAX_CRYSTALS_NUM; i++) {
      dist[i] = INT_MAX;
      st[i] = -1;
   }
   
   dijkstra(g, origin, st, dist);

   free(st);

   return dist;
}

