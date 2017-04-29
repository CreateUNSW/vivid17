// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Queue function headers for COMP1927 17x1 AE2.

#ifndef QUEUE_H
#define QUEUE_H

#include "Graph.h"

typedef struct _node *Node;
typedef struct _queue *Queue;

Queue newQueue(void);
void destroyQueue(Queue q);
void joinQueue(Queue q, Edge e);
Edge leaveQueue(Queue q);
int queueSize(Queue q);

#endif