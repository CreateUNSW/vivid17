// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Agent function implementations for COMP1927 17x1 AE2.

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

#define NRM "\x1B[0m"
#define BLD "\x1B[1m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"

#define NO_EDGE INT_MAX
#define DO_ABORT 1
#define NO_ABORT 0
#define MALLOC_ERR "Out of memory. Exiting program."

#define NO_DESTINATION -1
#define NO_PLAN -1

//This struct stores information about an individual agent(detective or thief)
//You might want to add to this struct to store more information
struct agentRep{
   Vertex startLocation;
   Vertex currentLocation;
   int currentCycle;
   int maxCycles;
   int initialStamina; //max stamina
   int stamina;  //current stamina
   int strategy;
   Graph map;
   char * name;
   // Stores how many times each vertex has been visited
   Vertex *visited;
   // Stores the next moves that will be taken (size initialised to
   // max needed during DFS - visiting every edge then backtracking
   // = (numV(g) - 1) * 2, double a minimum spanning tree
   Vertex *plan;
   // Increments every time a move is done from the plan array,
   // NOTE: will be NO_PLAN = -1 if currently has no plan
   int planProgress;
   // Stores number of moves total in plan
   // NOTE: will be NO_PLAN = -1 if currently has no plan
   int planLength;
   // NOTE: will be NO_DESTINATION = -1 if currently has no destination
   //       and for detective, doubles as storing thief's current
   //       location, updates whenever informant city is reached,
   //       as well as an override flag for the assigned strategy
   Vertex destination;
   // Flag for whether is thief
   int thiefFlag;
};

void static checkValidAgentAndCity(Agent agent, Vertex city);
void static printData(Agent agent, Vertex city);

//This creates one individual thief or detective
//You may need to add more to this
Agent initAgent(Vertex start, int maxCycles,int stamina, 
                int strategy, Graph g, char * name) {
   
   if(start >= numV(g)) {
      printf("Error starting vertex %d not valid\n",start);
      abort();
   }
   int i = 0;
   
   Agent agent = malloc(sizeof(struct agentRep));
   mallocCheck(agent);
   agent->startLocation = start;
   agent->currentLocation = start;
   agent->currentCycle = 0;
   agent->maxCycles = maxCycles;
   agent->initialStamina = stamina;
   agent->stamina = stamina;
   agent->strategy = strategy;
   agent->map = g;
   agent->name = strdup(name);

   agent->visited = malloc(sizeof(Vertex) * numV(agent->map));
   mallocCheck(agent->visited);
   for(i = 0; i < numV(agent->map); i++) {
      agent->visited[i] = 0;
   }
   // Updates the starting location to have 1 visit
   agent->visited[start]++;

   // Stores the next moves that will be taken (size initialised to
   // max needed during DFS - visiting every edge then backtracking
   // = (numV(g) - 1) * 2, double a minimum spanning tree
   agent->plan = malloc(sizeof(Vertex) * (numV(g) - 1) * 2);
   mallocCheck(agent->plan);
   for(i = 0; i < (numV(g) - 1) * 2; i++) {
      agent->plan[i] = -1;
   }

   // If the agent has a DFS assigned strategy
   if(agent->strategy == DFS) {
      // Initially generates a DFS plan, setting plan progress to 0
      agent->planProgress = 0;
      agent->planLength = dfSearch(agent->map, agent->currentLocation, 
                                   agent->plan);
      agent->destination = NO_DESTINATION;
   } else {
      agent->planProgress = NO_PLAN;
      agent->planLength = NO_PLAN;
      agent->destination = NO_DESTINATION;
   }
   agent->thiefFlag = 0;

   return agent;
}

void initThief(Agent thief, Vertex destination) {

   checkValidAgentAndCity(thief, destination);
   // Assumes that the thief has already been initiated as an agent
   thief->destination = destination;
   thief->thiefFlag = 1;
}


// Takes an array with all the possible edges and puts the ones the agent
// has enough stamina for into the filteredMoves array
// returns the number of filteredMoves
int filterEdges(Agent a,int numEdges,Edge *possibleMoves,Edge * filteredMoves) {
   int numFiltered = 0;
   int i;
   for(i=0;i<numEdges;i++){
      if(possibleMoves[i].weight <= a->stamina){
         filteredMoves[numFiltered++] = possibleMoves[i];     
      }
   }
   return numFiltered;
}

// Get a legal move. This should be a move that the agent has enough 
// stamina to make and is a valid edge from the graph. 
// You need to implement all other strategies.
Edge getNextMove(Agent agent,Graph g) {

   int i = 0;
   Edge nextMove;
   int numEdges = 0;
   int numFilteredEdges = 0;
   int moveWeight = 0;

   Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
   Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));
   
   // Stationary strategy useful for debugging
   if(agent->strategy == STATIONARY) {
      nextMove = mkEdge(agent->currentLocation, 
                        agent->currentLocation, 0);  
   } 

   // =========================================================
   // CHUCK IN ELSE IF, FOR WHEN AGENT IS AT INFORMANT CITY AND
   // hence its destination != NO_DESTINATION

   // Least turns path strategy IF and ONLY IF the agent has a
   // destination
   else if(agent->destination != NO_DESTINATION) {
      
      // NOTE: can assume that agent->destination, agent->plan,
      //       agent->planProgress and agent->planLength are all
      //       up-to-date, as updateDetectiveInfo maintains this when 
      //       it's called at each step in main

      // Checks whether the thief has reached the destination
      if(agent->currentLocation == agent->destination) {
         // Returns the detective back to its old strategy by switching
         // its least-turns-path flag off, and calling getNextMove
         agent->destination = NO_DESTINATION;
         nextMove = getNextMove(agent, g);
      }
      // If the least-turns-path plan still needs to be executed
      else {



         // DUMMY MOVE TO GET IT TO COMPILE
         nextMove = mkEdge(agent->currentLocation, 
                           agent->currentLocation, 0);

      }
   }

   // Random strategy
   else if(agent->strategy == RANDOM) {      
      // Get all edges to adjacent vertices
      numEdges = incidentEdges(g, agent->currentLocation, possibleMoves);

      // Filter out edges that the agent does not have enough stamina for
      numFilteredEdges = filterEdges(agent, numEdges, possibleMoves, 
                                     filteredMoves);
      if(numFilteredEdges != 0) {
         // nextMove is randomly chosen from the filteredEdges
         nextMove = filteredMoves[rand()%numFilteredEdges];
      } else {
         // the agent must stay in the same location
         nextMove = mkEdge(agent->currentLocation, 
                           agent->currentLocation, 0);
      }
   } 

   // Cheapest-Least-Visited strategy
   else if(agent->strategy == C_L_VISITED) {
      // Get all edges to adjacent vertices
      numEdges = incidentEdges(g, agent->currentLocation, possibleMoves);

      // Filter out edges that the agent does not have enough stamina for
      numFilteredEdges = filterEdges(agent, numEdges, possibleMoves, 
                                     filteredMoves);
      
      if(numFilteredEdges != 0) {
         // Picks the cheapest-least-visited move by first assuming
         // that the first entry of the array is it, then goes through
         // it until i == numFilteredEdges, and updates the nextMove at
         // each iteration
         nextMove = filteredMoves[0];
         for(i = 1; i < numFilteredEdges; i++) {
            // If it finds a less visited move, updates nextMove to it
            if(agent->visited[filteredMoves[i].w] < 
               agent->visited[nextMove.w]) {
               nextMove = filteredMoves[i];
            }               
            // If they are equal, checks the cost of the move
            else if(agent->visited[filteredMoves[i].w] ==
                    agent->visited[nextMove.w]) {
               // If the cost is lower, updates nextMove to it
               if(filteredMoves[i].weight < nextMove.weight) {
                  nextMove = filteredMoves[i];
               }
               // If it finds one with an equal weight, checks the index
               else if(filteredMoves[i].weight == nextMove.weight) {
                  // If the index is lower, updates nextMove to it
                  if(filteredMoves[i].w < nextMove.w) {
                     nextMove = filteredMoves[i];
                  }
               }
            }
         }
      } else {
         // the agent must stay in the same location
         nextMove = mkEdge(agent->currentLocation, 
                           agent->currentLocation, 0);
      }
   } 

   // Depth-First-Search Strategy
   else if(agent->strategy == DFS) {

      // If the current plan has been executed to completion
      if(agent->planProgress == agent->planLength) {
         // Makes a new plan from current location
         agent->planLength = dfSearch(agent->map, agent->currentLocation, 
                                      agent->plan);
         // And resets progress back to 0
         agent->planProgress = 0;
      }

      moveWeight = weightE(agent->map, agent->currentLocation,
                           agent->plan[agent->planProgress]);

      // Checks if the agent can make the move
      if(agent->stamina >= moveWeight) {
         // Follows the plan now assuming that there are moves in the
         // plan to follow
         nextMove = mkEdge(agent->currentLocation, 
                           agent->plan[agent->planProgress],
                           moveWeight);
      } else {
         // Remains in place
         nextMove = mkEdge(agent->currentLocation, 
                           agent->currentLocation, 0);
      }
   } else {
      printf("Agent strategy not implemented yet\n");
      abort();
   }

   free(filteredMoves);
   free(possibleMoves);

   return nextMove;
}

//Actually perform the move, by changing the agent's state
//This function needs to be updated to adjust the agent's stamina
void makeNextMove(Agent agent, Edge move) {
   
   Vertex prevLocation = agent->currentLocation;

   agent->currentCycle++;
   agent->currentLocation = move.w;

   // Updates stamina
   agent->stamina -= move.weight;

   // Updates visited array
   agent->visited[agent->currentLocation]++;

   // If the agent stayed at the same location
   if(prevLocation == agent->currentLocation) {
      // Updates agent stamina back to full
      agent->stamina = agent->initialStamina;
   } 
   // If the agent did do a move, and has a plan
   else if(agent->planLength != NO_PLAN) {
      // Updates the plan progress, to move onto the next planned move
      agent->planProgress++;
   }
}

// Updates the detective's destination to thief's current location and
// generates a least-turns-path plan to get to it
// NOTE: updateDetectiveInfo only does this if agent is a
//       detective, and detective's current city has an informant
void updateDetectiveInfo(Agent agent, Vertex thiefLocation) {

   checkValidAgentAndCity(agent, thiefLocation);
   // Ensures that agent is detective, and city has informant
   if(agent->thiefFlag == 0 && 
      hasInformant(agent->map, agent->currentLocation)) {
      // Updates destination to thief's location
      agent->destination = thiefLocation;
      // Updates the plan progress to 0, and the plan to the new plan
      agent->planProgress = 0;
      agent->planLength = leastTurnsPath(agent->map, agent->currentLocation,
                                         agent->destination, agent->plan);
   }
}

Vertex getCurrentLocation(Agent agent) {
   return agent->currentLocation;
}

Vertex getStartLocation(Agent agent) {
   return agent->startLocation;
}

Vertex getEndLocation(Agent agent) {
   return agent->destination;
}

char * getName(Agent agent) {
   return agent->name;
}

int getPlanProgress(Agent agent) {
   return agent->planProgress;
}

int getPlanLength(Agent agent) {
   return agent->planLength;
}

Vertex *getPlan(Agent agent) {
   return agent->plan;
}

//Needs to be updated to print out vertex name information
//and * for cities with informants
void printAgent(Agent agent) {

   printf("%s %d ", agent->name, agent->stamina);
   printData(agent, agent->currentLocation);

   // Shows secondary city data (for thief, shows goal, for detective,
   // shows thief's location if city has informant)
   if(agent->thiefFlag == 1) {
      // Shows thief destination city
      if(agent->destination != NO_DESTINATION) {
         printData(agent, agent->destination);
      }
   } else {
      // Shows thief destination for detective on informant city
      if(hasInformant(agent->map, agent->currentLocation) == 1) {
         printData(agent, agent->destination);
      }
   }
   printf("\n");
}

//You may need to update this to free any extra memory you use
void destroyAgent(Agent agent) {
   //YOU MAY NEED TO MODIFY THIS
   free(agent->name);
   free(agent->visited);
   free(agent->plan);
   free(agent);
}

void static checkValidAgentAndCity(Agent agent, Vertex city) {

   if(agent == NULL) {
      printError("Agent passed in must be valid", DO_ABORT);
   } else if(city < 0 || city >= numV(agent->map)) {
      printError("City passed in must be valid", DO_ABORT);
   }
}

void static printData(Agent agent, Vertex city) {
   if(city == NO_DESTINATION) {
      return;
   }

   printf("%s (%d", getCityName(agent->map, city),
                                city);
   if(hasInformant(agent->map, city) == 1) {
      printf("*");
   }
   printf(") ");

}
