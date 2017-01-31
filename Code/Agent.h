// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Agent function prototypes for COMP1927 17x1 AE2.

//An ADT interface to represent an agent

//Constants to represent search strategies used by the agents

#ifndef AGENT_H
#define AGENT_H

#define STATIONARY -1 //useful for debugging
#define RANDOM 0
#define C_L_VISITED 1 //Cheapest Least Visisted
#define DFS 2


typedef struct agentRep * Agent;

//Initialise an agent
Agent initAgent(Vertex start, int maxCycles,int stamina, 
                              int strategy,Graph g, char * name);
void initThief(Agent thief, Vertex destination);

//Calculate the next move
Edge getNextMove(Agent agent,Graph graph);
//Execute a given move
void makeNextMove(Agent agent,Edge move);
// Updates the detective's destination to thief's current location
// NOTE: updateDetectiveInfo only does this if agent is a
//       detective, and detective's current city has an informant
void updateDetectiveInfo(Agent agent, Vertex thiefLocation);

//Get information from the agent
Vertex getCurrentLocation(Agent agent);
Vertex getStartLocation(Agent agent);
Vertex getEndLocation(Agent agent);
char * getName(Agent agent);
int getPlanProgress(Agent agent);
int getPlanLength(Agent agent);
Vertex *getPlan(Agent agent);


void printAgent(Agent agent);

void destroyAgent(Agent agent);

#endif