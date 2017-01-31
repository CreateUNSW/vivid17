// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Black-box tests for Graph.c functions, for COMP1927 17x1 AE2.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Graph.h"

#define MAXLINE 20

#define NRM "\x1B[0m"
#define BLD "\x1B[7m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"

// ===================================
// -----------------------------------
// Test functions & section prototypes
// -----------------------------------
// ===================================

// -----------------------
// Test section prototypes
// -----------------------

Graph readGraph(char *graphStr);

void newGraphSection(void);
void insertESection(void);

// ----------------------------------
// Black-box test function prototypes
// ----------------------------------

void insertBigTest(void);
void abusiveInsert(Graph g, int abuseLevel);
void testInsert(Graph g, Edge *edges, int v, int w, int solRow,
                Edge insertSol[10][5], int insertAdjSol[22][10]);

// --------------------------
// Helper function prototypes
// --------------------------

int numDigits(int n);
void destroyGraphWarning(void);


// ====================================================================
// --------------------------------------------------------------------
// Main function, comment out sections as needed (funcs self-contained)
// --------------------------------------------------------------------
// ====================================================================

int main(int argc, char *argv[]) {

   // CURRENT COMMAND BEING USED TO TEST
   // ./assn2 citiesInformants.data agentsS3.data 5 0
   // ~cs1927/bin/assn2Model citiesMedium.data agentsS3.data 5 0

   // FOR ENDLESS GAME:
   // ./assn2 citiesEndless.data agentsEndless.data 100 0
   // ~cs1927/bin/assn2Model citiesEndless.data agentsEndless.data 100 0


   newGraphSection();

   insertESection();

   char *informantsString = "10\n"
                            "0 5 29 1 41 6 60 7 50 8 40 -1"
                            "1 2 51 5 29 i adelaide\n"
                            "2 n melbourne\n"
                            "3 5 30 4 36 n perth\n"
                            "4 3 36 9 20 n darwin\n"
                            "5 1 29 0 29 3 30 6 10 n hobart\n"
                            "6 n auckland\n"
                            "7 n madrid\n"
                            "8 i new york\n"
                            "9 n brisbane\n";
   Graph g = readGraph(informantsString);
   int i = 0;
   Vertex *plan = malloc(sizeof(Vertex) * (numV(g) - 1) * 2);
   for(i = 0; i < (numV(g) - 1) * 2; i++) {
      plan[i] = -1;
   }
   
   leastTurnsPath(g, 0, 9, plan, 20, 20);

   printf("\n");
   for(i = 0; i < (numV(g) - 1) * 2; i++) {
      printf("%d, ", plan[i]);
   }

   printf("\n");


   destroyGraphWarning();
   destroyGraph(g);

   return EXIT_SUCCESS;
}

// ========================================
// ----------------------------------------
// Test functions & section implementations
// ----------------------------------------
// ========================================

// ----------------------------
// Test section implementations
// ----------------------------

Graph readGraph(char *graphStr) {

   int id = 0;
   int dest = 0;
   int weight = 1;
   int bytesRead = 0;

   //First line of file has the number of vertices
   int numV;
   sscanf(graphStr, "%d", &numV);
   // + 1 is for the new line character that follows
   bytesRead += (numDigits(numV) + 1) * sizeof(char);

   Graph g = newGraph(numV);

   // scan through file and insert edges into graph
   int counter=0;
   while (counter < numV) {
      sscanf(graphStr + bytesRead,"%d",&id);
      bytesRead += (numDigits(id) + 1) * sizeof(char);
      counter++;

      while(sscanf(graphStr + bytesRead, "%d", &dest) == 1 && dest != -1) {
         bytesRead += (numDigits(dest) + 1) * sizeof(char);
         insertE(g, mkEdge(id, dest, weight));
      }
   }
   return g;
}

void newGraphSection(void) {

   printf(BLD" Testing newGraph() "NRM"\n");

   Graph g = NULL;
   int i = 0;
   int j = 0;
   int k = 0;
   Vertex *adj = calloc(100, sizeof(Vertex));
   Edge *edges = calloc(100, sizeof(Edge));

   for(i = 0; i < 100; i++) {
      if(i % 20 == 0 || i == 99) {
         printf(" Making %2d node graph : ", i);
      }
      g = newGraph(i);
      assert(g != NULL);

      for(j = 0; j < i; j++) {
         assert(adjacentVertices(g, j, adj) == 0);
         assert(incidentEdges(g, j, edges) == 0);
         for(k = 0; k < 100; k++) {
            assert(adj[k] == 0);
            assert(edges[k].v == 0);
            assert(edges[k].w == 0);
            assert(edges[k].weight == 0);
         }
      }

      destroyGraph(g);
      g = NULL;
      if(i % 20 == 0 || i == 99) {
         printf(GRN"Passed."NRM"\n");
      }
   }

   printf("\n");
   free(adj);
   free(edges);
}

void insertESection(void) {

   printf(BLD" Testing insertE() "NRM"\n"
             "===================\n");

   printf(" Testing with empty graph\n"
          " ------------------------\n");
   printf(" Inserting from 0 - 1k: ");
   Graph g = newGraph(0);
   assert(numV(g) == 0);
   assert(numE(g) == 0);
   abusiveInsert(g, 1000);
   assert(numV(g) == 0);
   assert(numE(g) == 0);
   printf(GRN"Passed."NRM"\n");
   printf("\n");
   destroyGraph(g);


   insertBigTest();
}

// ----------------------
// Generic Test functions
// ----------------------

void insertBigTest(void) {

   int i = 0;
   int j = 0;
   Graph g = newGraph(10);
   assert(numV(g) == 10);
   assert(numE(g) == 0);
   Edge *ed = malloc(sizeof(Edge) * numV(g));
   Edge emptyEdge = {-1, -1, -1};
   int insertAdjSol[22][10] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {5, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                               {5, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                               {5, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                               {5, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                               {5, 3, 1, 1, 0, 0, 0, 0, 0, 0},
                               {5, 3, 1, 2, 0, 0, 0, 0, 0, 0},
                               {5, 3, 1, 2, 1, 0, 0, 0, 0, 0},
                               {5, 3, 1, 2, 2, 0, 0, 0, 0, 0},
                               {5, 3, 1, 2, 2, 3, 0, 0, 0, 0},
                               {5, 3, 1, 2, 2, 3, 0, 0, 0, 0},
                               {5, 3, 1, 2, 2, 3, 0, 0, 0, 0},
                               {5, 3, 1, 2, 2, 4, 0, 0, 0, 0},
                               {5, 3, 1, 2, 2, 4, 2, 0, 0, 0},
                               {5, 3, 1, 2, 2, 4, 2, 0, 0, 0},
                               {5, 3, 1, 2, 2, 4, 2, 1, 0, 0},
                               {5, 3, 1, 2, 2, 4, 2, 1, 1, 0},
                               {5, 3, 1, 2, 2, 4, 2, 1, 1, 1}};

   Edge insertSol[10][5] = 
   {{mkEdge(0,1,41), mkEdge(0,5,29), mkEdge(0,6,60), mkEdge(0,7,50), mkEdge(0,8,40)},
    {mkEdge(1,0,41), mkEdge(1,2,51), mkEdge(1,5,29), emptyEdge     , emptyEdge     },
    {mkEdge(2,1,51), emptyEdge     , emptyEdge     , emptyEdge     , emptyEdge     },
    {mkEdge(3,4,36), mkEdge(3,5,30), emptyEdge     , emptyEdge     , emptyEdge     },
    {mkEdge(4,3,36), mkEdge(4,9,20), emptyEdge     , emptyEdge     , emptyEdge     },
    {mkEdge(5,0,29), mkEdge(5,1,29), mkEdge(5,3,30), mkEdge(5,6,10), emptyEdge     },
    {mkEdge(6,0,60), mkEdge(6,5,10), emptyEdge     , emptyEdge     , emptyEdge     },
    {mkEdge(7,0,50), emptyEdge     , emptyEdge     , emptyEdge     , emptyEdge     },
    {mkEdge(8,0,40), emptyEdge     , emptyEdge     , emptyEdge     , emptyEdge     },
    {mkEdge(9,4,20), emptyEdge     , emptyEdge     , emptyEdge     , emptyEdge     }};
   
   printf(" Testing self-edge inserts\n"
          " -------------------------\n");
   for(i = 0; i < 10; i++) {
      printf(" Inserting from %d - %d : ", i, i);
      insertE(g, mkEdge(i, i, 0));
      assert(incidentEdges(g, 0, ed) == 0);
      printf(GRN"Passed."NRM"\n");
   }


   printf("\n Testing normal inserts (+dupl)\n"
            " ------------------------------\n");
   printf(" Inserting edge 0-1 41: ");
   insertE(g, mkEdge(0, 1, 41));
   testInsert(g, ed, 0, 1, 0, insertSol, insertAdjSol);
   printf(" Inserting edge 0-5 29: ");
   insertE(g, mkEdge(0, 5, 29));
   testInsert(g, ed, 0, 2, 1, insertSol, insertAdjSol);
   printf(" Inserting edge 0-6 60: ");
   insertE(g, mkEdge(0, 6, 60));
   testInsert(g, ed, 0, 3, 2, insertSol, insertAdjSol);
   printf(" Inserting edge 0-7 50: ");
   insertE(g, mkEdge(0, 7, 50));
   testInsert(g, ed, 0, 4, 3, insertSol, insertAdjSol);
   printf(" Inserting edge 0-8 40: ");
   insertE(g, mkEdge(0, 8, 40));
   testInsert(g, ed, 0, 5, 4, insertSol, insertAdjSol);
   printf(" Inserting edge 1-0 41: ");
   insertE(g, mkEdge(1, 0, 41));
   testInsert(g, ed, 1, 1, 5, insertSol, insertAdjSol);
   printf(" Inserting edge 1-2 51: ");
   insertE(g, mkEdge(1, 2, 51));
   testInsert(g, ed, 1, 2, 6, insertSol, insertAdjSol);
   printf(" Inserting edge 1-5 29: ");
   insertE(g, mkEdge(1, 5, 29));
   testInsert(g, ed, 1, 3, 7, insertSol, insertAdjSol);
   printf(" Inserting edge 2-1 51: ");
   insertE(g, mkEdge(2, 1, 51));
   testInsert(g, ed, 2, 1, 8, insertSol, insertAdjSol);
   printf(" Inserting edge 3-4 36: ");
   insertE(g, mkEdge(3, 4, 36));
   testInsert(g, ed, 3, 1, 9, insertSol, insertAdjSol);
   printf(" Inserting edge 3-5 30: ");
   insertE(g, mkEdge(3, 5, 30));
   testInsert(g, ed, 3, 2, 10, insertSol, insertAdjSol);
   printf(" Inserting edge 4-3 36: ");
   insertE(g, mkEdge(4, 3, 36));
   testInsert(g, ed, 4, 1, 11, insertSol, insertAdjSol);
   printf(" Inserting edge 4-9 20: ");
   insertE(g, mkEdge(4, 9, 20));
   testInsert(g, ed, 4, 2, 12, insertSol, insertAdjSol);
   printf(" Inserting edge 5-0 29: ");
   insertE(g, mkEdge(5, 0, 29));
   testInsert(g, ed, 5, 1, 13, insertSol, insertAdjSol);
   printf(" Inserting edge 5-1 29: ");
   insertE(g, mkEdge(5, 1, 29));
   testInsert(g, ed, 5, 2, 14, insertSol, insertAdjSol);
   printf(" Inserting edge 5-3 30: ");
   insertE(g, mkEdge(5, 3, 30));
   testInsert(g, ed, 5, 3, 15, insertSol, insertAdjSol);
   printf(" Inserting edge 5-6 10: ");
   insertE(g, mkEdge(5, 6, 10));
   testInsert(g, ed, 5, 4, 16, insertSol, insertAdjSol);
   printf(" Inserting edge 6-0 60: ");
   insertE(g, mkEdge(6, 0, 60));
   testInsert(g, ed, 6, 1, 17, insertSol, insertAdjSol);
   printf(" Inserting edge 6-5 10: ");
   insertE(g, mkEdge(6, 5, 10));
   testInsert(g, ed, 6, 2, 18, insertSol, insertAdjSol);
   printf(" Inserting edge 7-0 50: ");
   insertE(g, mkEdge(7, 0, 50));
   testInsert(g, ed, 7, 1, 19, insertSol, insertAdjSol);
   printf(" Inserting edge 8-0 40: ");
   insertE(g, mkEdge(8, 0, 40));
   testInsert(g, ed, 8, 1, 20, insertSol, insertAdjSol);
   printf(" Inserting edge 9-4 20: ");
   insertE(g, mkEdge(9, 4, 20));
   testInsert(g, ed, 9, 1, 21, insertSol, insertAdjSol);

   printf("\n Testing all duplicate inserts\n"
            " -----------------------------\n");
   printf(" Reinserting all edges: ");
   abusiveInsert(g, 0);
   testInsert(g, ed, 9, 1, 21, insertSol, insertAdjSol);

   printf("\n Testing invalid vertices\n"
            " ------------------------\n");
   printf(" Inserting from 0-1000: ");
   for(i = numV(g); i < 1000; i++) {
      for(j = numV(g); j < 1000; j++) {
         insertE(g, mkEdge(i, j, 0));
      }
   }
   testInsert(g, ed, 9, 1, 21, insertSol, insertAdjSol);

   printf("\n");


   free(ed);
   destroyGraph(g);
}

void abusiveInsert(Graph g, int abuseLevel) {

   int i = 0;
   int j = 0;

   insertE(g, mkEdge(0, 1, 41));
   insertE(g, mkEdge(1, 0, 41));
   insertE(g, mkEdge(0, 5, 29));
   insertE(g, mkEdge(5, 0, 29));
   insertE(g, mkEdge(0, 6, 60));
   insertE(g, mkEdge(6, 0, 60));
   insertE(g, mkEdge(0, 7, 50));
   insertE(g, mkEdge(7, 0, 50));
   insertE(g, mkEdge(0, 8, 40));
   insertE(g, mkEdge(8, 0, 40));
   insertE(g, mkEdge(1, 0, 41));
   insertE(g, mkEdge(0, 1, 41));
   insertE(g, mkEdge(1, 2, 51));
   insertE(g, mkEdge(2, 1, 51));
   insertE(g, mkEdge(1, 5, 29));
   insertE(g, mkEdge(5, 1, 29));
   insertE(g, mkEdge(2, 1, 51));
   insertE(g, mkEdge(1, 2, 51));
   insertE(g, mkEdge(3, 4, 36));
   insertE(g, mkEdge(4, 3, 36));
   insertE(g, mkEdge(3, 5, 30));
   insertE(g, mkEdge(5, 3, 30));
   insertE(g, mkEdge(4, 3, 36));
   insertE(g, mkEdge(3, 4, 36));
   insertE(g, mkEdge(4, 9, 20));
   insertE(g, mkEdge(9, 4, 20));
   insertE(g, mkEdge(5, 0, 29));
   insertE(g, mkEdge(0, 5, 29));
   insertE(g, mkEdge(5, 1, 29));
   insertE(g, mkEdge(1, 5, 29));
   insertE(g, mkEdge(5, 3, 30));
   insertE(g, mkEdge(3, 5, 30));
   insertE(g, mkEdge(5, 6, 10));
   insertE(g, mkEdge(6, 5, 10));
   insertE(g, mkEdge(6, 0, 60));
   insertE(g, mkEdge(0, 6, 60));
   insertE(g, mkEdge(6, 5, 10));
   insertE(g, mkEdge(5, 6, 10));
   insertE(g, mkEdge(7, 0, 50));
   insertE(g, mkEdge(0, 7, 50));
   insertE(g, mkEdge(8, 0, 40));
   insertE(g, mkEdge(0, 8, 40));
   insertE(g, mkEdge(9, 4, 20));
   insertE(g, mkEdge(4, 9, 20));

   for(i = numV(g); i < abuseLevel; i++) {
      for(j = numV(g); j < abuseLevel; j++) {
         insertE(g, mkEdge(i, j, 0));
      }
   }
}

void testInsert(Graph g, Edge *edges, int v, int w, int solRow,
                Edge insertSol[10][5], int insertAdjSol[22][10]) {

   int i = 0;
   int j = 0;
   int inclE = 0;

   for(i = 0; i < (v + 1); i++) {
      // Checks incident edges on each vertex
      inclE = incidentEdges(g, i, edges);
      assert(inclE == insertAdjSol[solRow][i]);
      for(j = 0; j < inclE; j++) {
         if(insertSol[i][j].v != -1) {
            // Checks edges incident against solution array
            assert(edges[j].v == insertSol[i][j].v);
            assert(edges[j].w == insertSol[i][j].w);
            assert(edges[j].weight == insertSol[i][j].weight);
         }
      }
   }

   printf(GRN"Passed."NRM"\n");
}

// ===============================
// -------------------------------
// Helper and formatting functions
// -------------------------------
// ===============================

// Finds the number of digits in an int
int numDigits(int n) {

   int digits = 0;

   // Adds "-" as a digit if n < 0, and "0" as digit if n == 0
   if(n <= 0) {
      digits = 1;
   }

   // Loops until 10 cannot fit in "n" anymore
   while(n != 0) {
      // Divides "n" by 10 to get rid of a decimal place, and
      // increments digits count
      n /= 10;
      digits++;
   }

   return digits;
}

void destroyGraphWarning(void) {

   printf(BLD" NOTE: "NRM
                    " There is a posibility that destroyGraph(g) will\n" 
             "        inadvertently try freeing city names as they were\n"
             "        never malloc'd into the graph, depending upon the\n"
             "        implementation of your graph functions.\n"
             "\n"
             "        A guard can be put in place within destroyGraph,\n"
             "        but the name rep's must be initialised to NULL\n"
             "        at some point at graph creation.\n"
             "\n"
             "        If your program segfaults now, this is likely\n"
             "        what happened. All other functions have "
                      GRN"passed."NRM"\n");
}