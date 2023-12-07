//双栈当队
#pragma once
#include"hash.h"

class Queue{
    private:
        String F;
        String R;
        int _size = 0;
    public:
        int size();
        void enqueue(char);
        void dequeue();
};