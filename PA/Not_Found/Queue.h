#pragma once
class Stack{
    public:
    int a[30];
    int size = 0;
    void push(int);
    void pop();
};
class Queue{
    public:
    Stack F,R;
    int size = 0;
    void enqueue(int);
    void dequeue();
    int map();
};