// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Graph function prototypes for COMP1927 17x1 AE2.

// An graph ADT interface for weighted undirected graphs

#ifndef GRAPH_H
#define GRAPH_H

#define MAX_CRYSTALS_NUM 19
#define MAX_EDGE_PER_CRYSTAL MAX_CRYSTALS_NUM

// vertices denoted by integers 0..N-1 
typedef int Vertex; 

// edges are pairs of vertices (end-points) 
typedef struct { 
   Vertex v; 
   Vertex w; 
   int weight;
} Edge; 

struct cityRep {
   // Is set to ON or OFF depending on whether or not city (ie node)
   // has an informant
   int informant;
   // String storing the city's name
   char *name;
};

Edge mkEdge(Vertex, Vertex, int); 

// Graph representation is hidden
typedef struct graphRep *Graph;
typedef struct cityRep City;


// --------------
// City functions
// --------------
void insertCity(Graph g, Vertex v, char informant, char *name);
int hasInformant(Graph g, Vertex v);
char *getCityName(Graph g, Vertex v);

// ---------------
// Graph functions
// ---------------

// operations on graphs 
Graph newGraph(int nV); // #vertices 

// insert an edge into the graph
// the edge must not be inserted if
//     the vertices are not valid
//     it would create a self loop
//     there already exists an edge between the vertices
void insertE(Graph g, Edge e); 

//returns 1 if there is ad adge from v to w
int isAdjacent(Graph g,Vertex v, Vertex w);

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]);

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]);

// returns the number of edges and fills the array of edges.
// nE is the max size of the es array
int edges(Edge es[], int nE, Graph g);

int numV(Graph g);
int numE(Graph g);
int weightE(Graph g, Vertex v, Vertex w);

int dfSearch(Graph g, Vertex start, Vertex *plan);
int leastTurnsPath(Graph g, Vertex start, Vertex dest, Vertex *plan,
                   int currStamina, int maxStamina);

void dijkstra(Graph g,Vertex s,int st[],int dist[]);
int *calcDist(Graph g, int origin);

//YOU DO NOT NEED ASSERT BASED TESTS FOR THESE FUNCTIONS
void destroyGraph(Graph g); 
void show(Graph g); 

void printError(char *message, int abortFlag);
void mallocCheck(void *new);

//YOU MAY ADD MORE FUNCTIONS IN HERE FOR YOUR OWN IMPLEMENTATION
//DO NOT SUBMIT UNIT TESTS FOR THESE FUNCTIONS - OF COURSE
//YOU SHOULD TEST THEM ANYWAY BUT COMMENT OUT OR REMOVE TESTS FOR 
//SUBMISSION OTHERWISE

Graph readGraph(int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1]);

#endif
