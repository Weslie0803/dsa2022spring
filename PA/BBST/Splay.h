class Splay;
#pragma once
#include"BBST.h"
class Splay : public BBST{
    public:
    void splay(Rank v);
    Rank & search(int key) override;
    void insert(int key) override;
    void remove(int key) override;
};