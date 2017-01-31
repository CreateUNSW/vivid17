// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Priority-Queue function headers for COMP1927 17x1 AE2.

#ifndef PQ_H
#define PQ_H

#include "Graph.h"

typedef struct _pq *PQ;

Queue newQueue(void);
void destroyQueue(Queue q);
void joinQueue(Queue q, Edge e);
Edge leaveQueue(Queue q);
int queueSize(Queue q);

#endif