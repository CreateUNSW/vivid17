// A priority Queue ADT interface

#ifndef PQ_H
#define PQ_H

#include "Item.h"

typedef struct pqRep * PriQ;

// Core operations 
PriQ initPriQ(int size); 
void insert(PriQ q, Item it); 
Item delMin(PriQ q); 

// Useful operations 
int isEmpty(PriQ q); 
void change(PriQ q, Key k, Item it);
void delete(PriQ q, Key k); 
PriQ join(PriQ q1, PriQ q2); 

void decreaseWeight(PriQ q, int v, Key k);

#endif