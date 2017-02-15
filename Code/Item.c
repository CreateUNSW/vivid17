#include <stdlib.h>

#include "Item.h"

Item newItem(Key k,int v){
    Item i = malloc(sizeof(struct record));
    assert(i != NULL);
    i->keyVal = k;
    i->value = v;
    return i;
}