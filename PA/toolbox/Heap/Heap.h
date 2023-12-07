#pragma once

class Heap{
    int * top;
    int percolateDown(int * A, int n, int i);
    int percolateUp(int * A, int n);
    inline int Parent(int i);
    inline int LChild(int i);
    inline int RChild(int i);
    public:
        void heapify(int * A, int length);
        void Insert(int t);
};