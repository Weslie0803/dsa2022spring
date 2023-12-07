#include "Heap.h"

inline int Heap::Parent(int i){
    return (i - 1 )>> 1;
}
inline int Heap::LChild(int i){
    return (i << 1) + 1;
}
inline int Heap::RChild(int i){
    return (i << 1) + 2;
}

inline void swap(int & i, int & j){
    int t = i;
    i = j;
    j = t;
}

int Heap::percolateDown(int * A, int n, int i){
    
}