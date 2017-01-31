// Randy Tjang, z5116840
// COMP1927 Thursday 9AM, Stanis
// 20/01/2017
// Priority-Queue function implementations for COMP1927 17x1 AE2.

#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"
#include "Graph.h"

struct _pq {
	// Stores how many of the heap spots have been used
	int filled;
	// Stores the current heap max size
	int capacity;
	// A heap array of edges
	Edge *e;
};



// --------------------------------------------------
// DELETE EVERYTHING BELOW THIS, AND REWRITE IT ABOVE
// --------------------------------------------------


//Create a new empty priority queue
PriQ initPriQ(int size) { 
    PriQ q = malloc(sizeof(struct pqRep)); 
    assert(q != NULL); 
    // indexes start from 1 
    q->items = malloc(sizeof(Item) * (size+1));
    assert(q->items != NULL); 
    q->nItems = 0; 
    q->size = size; 
    return q; 
}

int isEmpty(PriQ pq){
    return (pq->nItems == 0);
}

// A local helper function to swap the item from index1 and index2 in the array
void swap(Item a[],int index1,int index2){
   Item tmp;
   tmp = a[index1];
   a[index1] = a[index2];
   a[index2] = tmp;
}

// Local function - not part of the interface
// Bottom up heapify
// force value at a[k] into correct position 
void fixUp(Item a[], int k) { 
    while (k > 1 && greater(a[k/2],a[k])) { 
        swap(a, k, k/2); 
        k = k/2; // integer division 
    } 
} 

// Top down heapify
// force value at a[k] into correct position 
void fixDown(Item a[], int k, int N) {
   while (2*k <= N) { 
   int j = 2*k; //choose larger of two children 
   if (j < N && greater(a[j], a[j+1])) j++; 
   if (!greater(a[k], a[j])) break; 
   swap(a, k, j); 
   k = j; 
} 
} 



// add a new item into the queue 
void insert(PriQ q, Item it) { 
    assert(q != NULL && q->nItems < q->size); 
    q->nItems++; 
    q->items[q->nItems] = it; 
    fixUp(q->items, q->nItems); 
} 

// delete the largest item 
Item delMin(PriQ q) { 
    assert(q != NULL && q->nItems > 0); 
    swap(q->items, 1, q->nItems); 
    q->nItems--; 
    fixDown(q->items, 1, q->nItems); 
    return q->items[q->nItems+1]; 
} 

//decreases the weight of the priority for a given value
void decreaseWeight(PriQ pq, int value, Key newWeight){
    int i;
    for(i=1;i<=pq->nItems;i++){
      if(pq->items[i]->value == value){ 
            pq->items[i]->keyVal = newWeight;
            break;
      }
    }
    if(i <= pq->nItems)
       fixUp(pq->items,i);
}