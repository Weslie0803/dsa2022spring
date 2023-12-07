class AVL;
#pragma once
#include "BBST.h"

class AVL : public BBST{
    inline int BalenceFactor(Rank x);
    inline bool AVLBalanced(Rank x);
    void insert(int key)override;
    void remove(int ket)override;
};