#pragma once
#include<cstdio>
typedef int Rank;
struct Node
{
    int value;
    int count;
};
template<class Type>
class Queue{
    private:
        Type elem[1000001];  //存放元素，定义高指数为头，低指数为尾，头进尾出
        Rank _begin = 0, _end = 0;
        int _size = 0;
    public:
        int size(){
            return _size;
        }
        bool empty(){
            return !_size;
        }
        void enqueue(Type e){
            elem[_end] = e; //从头部进队
            _end ++;
            _size ++;
        }
        Type dequeue(){
            Type tmp = elem[_begin];    //从尾部出队
            _begin ++;
            _size --;
            return tmp;
        }
        Type pop(){//从头部出队
            Type tmp = elem[_end - 1];
            _end --;
            _size --;
            return tmp;
        }
        Type & roar(){
            return elem[_begin];
        }
        Type front(){
            return elem[_end - 1];
        }
};

class Queap{
    private:
        Queue<int>  q;
        Queue<Node>  pm;
    public:
        int getMax();
        void enqueue(int);
        int dequeue();
        int size(){return q.size();}
};