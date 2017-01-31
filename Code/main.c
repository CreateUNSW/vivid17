// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Game client for COMP1927 17x1 AE2.

/**
  main.c

  The client game. This reads in data from a file to create a graph that
  represents a map of cities. 
  It reads in data to create 5 agents: a thief and 4 detectives. 
  It then runs a simulation where the thief and detectives move
  through the cities. 
  Currently only a random movement strategy has been implemented.
  Stamina requirements and finishing a game need to implemented, as well as printing
  out agent information and storing city names
 **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Graph.h"
#include "Agent.h"

#define NRM "\x1B[0m"
#define BLD "\x1B[1m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"

#define MAXLINE 20

#define NUM_DETECTIVES 4
#define THIEF 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4

//Game states
#define CONTINUE 0
#define WIN -1
#define LOSE -2
#define OVER -3

Graph readGraph(char * filename);
void initialiseAgents(char *filename, Agent agents[], int maxCycles, Graph g);
void display(int cycle,Agent agents[],Graph g);
int checkGameState(Agent agents[],Graph g,int cycle,int maxCycles);
int step(int cycle,Agent agents[],Graph g,int maxCycles);
int run(int cycle, int maxCycles, Agent agents[],Graph g);
void stats(int cycle, Agent agents[]);
void freeResources(Agent agents[],Graph g);

// Reads in data from the file with the given filename and creates a newGraph
// The file must be of the format
// numVertices
// v1 v2 weight v1 v2 weight informant cityname
// v1 v2 weight v1 v2 weight informant cityname
Graph readGraph(char * filename) {
   FILE *fp;
   fp = fopen (filename, "r"); // open data file
   assert (fp != NULL);

   int city = 0;
   int dest = 0;
   int weight = 0;

   //First line of file has the number of vertices
   int numV;
   fscanf(fp, "%d", &numV);

   Graph g = newGraph(numV);   

   // scan through file and insert edges into graph
   int counter=0; 
   char informant; 
   char name[MAXLINE];  
   while (counter < numV) {
      fscanf(fp,"%d",&city);
      counter++;

      while(fscanf(fp, "%d %d", &dest,&weight) == 2){     
         insertE(g, mkEdge(city, dest, weight));
      }
      //TASK - YOU MUST STORE THIS INFO IN THE GRAPH
      fscanf(fp,"%c %[^\n]", &informant, name);
      insertCity(g, city, informant, name);
   }
   fclose(fp);
   return g;
}

// partially initialises the thief and 4 detectives from a data file
// You may need to modify this function, to initialise all 
// important agent information
void initialiseAgents(char *filename, Agent agents[], int maxCycles, Graph g){
   FILE *fp;
   fp = fopen (filename, "r"); // open data file
   assert (fp != NULL);
   int stamina;
   Vertex start;
   Vertex thiefStart;
   Vertex end;
   char name[5];
   int i;
   int strategy;

   fscanf(fp, "%d %d %d %[^\n]", &stamina,&start,&end,name);
   agents[THIEF] = initAgent(start,maxCycles,stamina,RANDOM,g,name);
   initThief(agents[THIEF], end);
   // Preps to do initial store of thief curr data into detectives
   thiefStart = start;

   for(i = 1; i <= NUM_DETECTIVES; i++){      
      fscanf(fp, "%d %d %d %[^\n]", &stamina,&start,&strategy,name);
      agents[i] = initAgent(start,maxCycles,stamina,strategy,g,name);
      // Stores thief location if starts on an informant city
      updateDetectiveInfo(agents[i], thiefStart);
   }  
   fclose(fp);
}

//Display information about the current state of the game
void display(int cycle,Agent agents[],Graph g){
   int i;
   printf("Hour %d\n",cycle);
   // function to print the current location of each agent
   printf ("  T  D1  D2  D3  D4\n");
   for (i = 0; i <= NUM_DETECTIVES; i++) {    
      printf ("%3d", getCurrentLocation(agents[i]));
      if(hasInformant(g, getCurrentLocation(agents[i])) == 1) {
         printf("*");
      } else {
         printf(" ");         
      }
   }
   printf ("\n\n");
}


//check whether the game is over
int checkGameState(Agent agents[],Graph g,int cycle,int maxCycles) {

   Agent thief = agents[THIEF];
   Agent det1 = agents[1];
   Agent det2 = agents[2];
   Agent det3 = agents[3];
   Agent det4 = agents[4];

   Vertex currLocT = getCurrentLocation(thief);
   Vertex endLoc = getEndLocation(thief);

   Vertex currLoc1 = getCurrentLocation(det1);
   Vertex currLoc2 = getCurrentLocation(det2);
   Vertex currLoc3 = getCurrentLocation(det3);
   Vertex currLoc4 = getCurrentLocation(det4);

   // Game won when detectives catch thief (note if multiple detectives)
   // caught thief, will default to lowest index one
   if(currLocT == currLoc1) {
      printf("%s caught the thief in %s (%d)\n"
             "YOU WIN - THIEF CAUGHT!\n", 
              getName(det1), getCityName(g, currLoc1), currLoc1);
      return OVER;
   } else if(currLocT == currLoc2) {
      printf("%s caught the thief in %s (%d)\n"
             "YOU WIN - THIEF CAUGHT!\n", 
              getName(det2), getCityName(g, currLoc2), currLoc2);
      return OVER;
   } else if(currLocT == currLoc3) {
      printf("%s caught the thief in %s (%d)\n"
             "YOU WIN - THIEF CAUGHT!\n", 
              getName(det3), getCityName(g, currLoc3), currLoc3);
      return OVER;
   } else if(currLocT == currLoc4) {
      printf("%s caught the thief in %s (%d)\n"
             "YOU WIN - THIEF CAUGHT!\n", 
              getName(det4), getCityName(g, currLoc4), currLoc4);
      return OVER;
   } 

   // Game lost when thief gets to endLoc
   else if(currLocT == endLoc) {
      printf("%s got away to %s (%d)\n"
             "GAME OVER: YOU LOSE - THIEF GOT TO GETAWAY\n", 
              getName(thief), getCityName(g, endLoc), endLoc);
      return OVER;
   }

   // Game lost when time is up
   else if(cycle >= maxCycles) {
      printf("GAME OVER: YOU LOSE - TIME IS UP\n");
      return OVER;
   }

   // Game keeps going
   else {
      return CONTINUE;
   }
}

//step through one cycle of the game
int step(int cycle,Agent agents[],Graph g,int maxCycles){

   int i = 0;
   Vertex thiefLocation = 0;

   cycle++;
   for(i=0;i<=NUM_DETECTIVES;i++){
      Edge nextMove = getNextMove(agents[i],g);  
      makeNextMove(agents[i],nextMove);

      // Stores thief location
      if(i == THIEF) {
         thiefLocation = nextMove.w;
      }
      // Updates the detective's destination to thief's current location
      //  and generates a least-turns-path plan to get to it
      // NOTE: updateDetectiveInfo only does this if agent is a
      //       detective, and detective's current city has an informant
      updateDetectiveInfo(agents[i], thiefLocation);
   }
   display(cycle,agents,g);
   int gameState = checkGameState(agents,g,cycle,maxCycles);
   if(gameState == CONTINUE){
      return cycle;
   } else {
      return gameState;
   }
}


//runs the game until the maximum number of cycles have completed
int run(int cycle, int maxCycles, Agent agents[],Graph g){
   while(cycle < maxCycles && cycle >= 0){
      cycle = step(cycle,agents,g,maxCycles);
   }
   return cycle;
}


void stats(int cycle, Agent agents[]){
   int i;
   printf("Hour %d\n",cycle);
   for(i=0;i<=NUM_DETECTIVES;i++){
      printAgent(agents[i]);
   } 
   printf("\n");
}

void freeResources(Agent agents[], Graph g){
   int i;
   for(i=0;i<=NUM_DETECTIVES;i++){
      destroyAgent(agents[i]);
   }
   destroyGraph(g);
}


int main(int argc, char * argv[]){
   Agent agents[NUM_DETECTIVES+1];

   if(argc < 4){
      printf("Incorrect usage: please enter filename1 filename2 maxCycles\n");
      exit(0);
   }

   int maxCycles = atoi(argv[3]);
   int cycle = 0;
   int seed = time(NULL);

   if(argc == 5) 
      seed = atoi(argv[4]);


   srand(seed);

   Graph g = readGraph(argv[1]);
#ifdef DEBUG
   show(g);
#endif

   initialiseAgents(argv[2],agents,maxCycles,g);
#ifdef DEBUG
   stats(cycle,agents);
#endif



   char command[MAXLINE];
   printf("\nPOLICE ACADEMY 1927");
   printf("\n\nRed alert! A thief is on the run.\n");
   printf("Agents, to your cars. You have %d hours.\n\n",maxCycles);
   display(cycle,agents,g);

   if(checkGameState(agents,g,cycle,maxCycles) != CONTINUE){
      freeResources(agents,g);
      return 0;
   }
   printf("Enter command: ");
   scanf("%s",command);


   while (strcmp(command,"quit") != 0) {
      if(strcmp(command,"display") == 0) {
         display(cycle,agents,g);
      } else if(strcmp(command,"run") == 0) {
         cycle = run(cycle,maxCycles,agents,g);
      } else if(strcmp(command,"step") == 0) {
         cycle = step(cycle,agents,g,maxCycles);
      } else if(strcmp(command,"stats") == 0) {
         stats(cycle,agents);
      } else if(strcmp(command,"map") == 0) {
         show(g);
         printf("\n");
      }

/*
      int i = 0;
      int j = 0;
      int numEdges = 0;
      Edge *edges = malloc(sizeof(Edge) * numV(g));
      for(i = 0; i < numV(g); i++) {
         numEdges = incidentEdges(g, i, edges);
         for(j = 0; j < numEdges; j++) {
            printf("%d, %d, %d\n", edges[j].v, edges[j].w, edges[j].weight);
         }
      }
*/

      if(cycle < 0) break;
      printf("Enter command: ");
      scanf("%s",command);
   }
   freeResources(agents,g);
   return 0;
}

