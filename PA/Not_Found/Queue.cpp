#include"Queue.h"

void Stack::push(int e){
    this->a[size] = e;
    size++;
}

void Stack::pop(){
    size --;
}

void Queue::enqueue(int e){
    R.push(e);
    this->size ++;
}

void Queue::dequeue(){
    if(F.size > 0){
        F.pop();
    }
}
