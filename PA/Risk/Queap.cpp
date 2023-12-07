#include"Queap.h"

int Queap::getMax(){
    return pm.roar().value;
}

void Queap::enqueue(int e){
    q.enqueue(e);
    Node _e = {e,1};//预先构造新结点
    while(pm.front().value <= e && !pm.empty()){//若头部结点值太小且队列非空
        _e.count += pm.front().count;//新结点的长度累加
        pm.pop();//头部结点pop
    }
    pm.enqueue(_e);
}

int Queap::dequeue(){
    int num = pm.roar().value;
    q.dequeue();
    pm.roar().count --;
    if(pm.roar().count == 0){//尾部结点长度为0则出队
        pm.dequeue();
    }
    return num;
}