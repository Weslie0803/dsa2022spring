#include "AVL.h"
#include "BBST.h"

inline int AVL::BalenceFactor(Rank x){
    return stature(nl.pointer(x)->lc) - stature(nl.pointer(x)->rc);
}

inline bool AVL::AVLBalanced(Rank x){
    int f = BalenceFactor(x);
    return (-2 < f) && (f < 2);
}

void AVL::insert(int key){
    Rank & x = search(key);
    if(x != -1) return;
    x = nl.new_node();
    Rank xx = x;
    nl.pointer(xx)->key = key;
    nl.pointer(xx)->parent = _hot;//size++;
    for(Rank g = _hot; g != -1; g = nl.pointer(g)->parent){
        if(!AVLBalanced(g)){
            FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else{
            updateHeight(g);
        }
    }
}

void AVL::remove(int key){
    Rank & x = search(key); if(x == -1) return;
    removeAt(x, _hot); //_size--;
    for(Rank g = _hot; g != -1; g = nl.pointer(g)->parent){
        if(!AVLBalanced(g)){
            g = FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
        }
        updateHeight(g);
    }
    return;
}