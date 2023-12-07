#include "S2Queue.h"

int Queue::size(){
    return _size;
}

void Queue::enqueue(char c){
    if(R.size() >= 8){
        while(R.size() != 0){
            F.push(R.pop());
        }
    }
    R.push(c);
}

void Queue::dequeue(){
    if(F.size() <= 0){
        while(R.size()!=0){
            F.push(R.pop());
        }
    }
    F.pop();
}