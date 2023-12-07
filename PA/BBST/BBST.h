class BBST;
#pragma once
#include "Node.h"
#include <cstdio>

class BBST{
    public:
    NodeList nl;
    Rank root = -1;
    Rank _hot;//命中点的父节点
    virtual void insert(int key);
    virtual void remove(int key);
    virtual Rank & search(int key);
    virtual int find(int key);
    Rank rotateAt(Rank v);
    Rank connect34(Rank, Rank, Rank, 
                    Rank, Rank, Rank, Rank);
    int stature(Rank p);
    void updateHeight(Rank x);
    Rank tallerChild(Rank x);
    Rank & FromParentTo(Rank x);
    int removeAt(Rank & x, Rank & hot);
    void updateHeightAbove(Rank x);

};

inline int max(int a, int b){
    return a > b ? a : b;
}