#include "BBST.h"

Rank & BBST::search(int key){
    if(root == -1 || key == nl.pointer(root)->key){//空树或根节点命中
        _hot = -1;
        return root;
    }
    _hot = root;
    while(1){
        Rank *next;
        if(key < nl.pointer(_hot)->key){
            next = &(nl.pointer(_hot)->lc);
        }
        else next = &(nl.pointer(_hot)->rc);
        if(*next == -1 || key == nl.pointer(*next)->key) //叶节点或命中
            return *next;
        _hot = *next;
    }
}

int BBST::find(int key){
    Rank t = search(key);
    if(t != -1){//命中
        return key;
    }
    if(_hot == -1) return -1;
    if(nl.pointer(_hot)->key <= key) return nl.pointer(_hot)->key;
    t = nl.pointer(_hot)->parent;
    while(t != -1 && _hot == nl.pointer(t)->lc){
        _hot = t;
        t = nl.pointer(_hot)->parent;
    }
    if(t == -1) return -1;
    return nl.pointer(t)->key;
}

Rank BBST::rotateAt(Rank v){
    if(v == -1){
        printf("Rotate error\n");
        return -1;
    }
    Rank p = nl.pointer(v)->parent;
    Rank g = nl.pointer(p)->parent;
    if(p == nl.pointer(g)->lc){
        if(v == nl.pointer(p)->lc){
            nl.pointer(p)->parent = nl.pointer(g)->parent;
            return connect34(v, p, g, nl.pointer(v)->lc, nl.pointer(v)->rc, nl.pointer(p)->rc, nl.pointer(g)->rc);
        }
        else{
            nl.pointer(v)->parent = nl.pointer(g)->parent;
            return connect34(p, v, g, nl.pointer(p)->lc, nl.pointer(v)->lc, nl.pointer(v)->rc, nl.pointer(g)->rc);
        }
    }
    else{
        if(v == nl.pointer(p)->rc){
            nl.pointer(p)->parent = nl.pointer(g)->parent;
            return connect34(g, p, v, nl.pointer(g)->lc, nl.pointer(p)->lc, nl.pointer(v)->lc, nl.pointer(v)->rc);
        }
        else{
            nl.pointer(v)->parent = nl.pointer(g)->parent;
            return connect34(g, v, p, nl.pointer(g)->lc, nl.pointer(v)->lc, nl.pointer(v)->rc, nl.pointer(p)->rc);
        }
    }
}

int BBST::stature(Rank p){
    if(p == -1) return -1;
    return nl.pointer(p)->height;
}

void BBST::updateHeight(Rank a){
    nl.pointer(a)->height = 1 + max(stature(nl.pointer(a)->lc), stature(nl.pointer(a)->rc));
}

Rank BBST::connect34(Rank a, Rank b, Rank c,
                    Rank T0, Rank T1, Rank T2, Rank T3){
    nl.pointer(a)->lc = T0; if(T0 != -1) nl.pointer(T0)->parent = a;
    nl.pointer(a)->rc = T1; if(T1 != -1) nl.pointer(T1)->parent = a;
    updateHeight(a);
    nl.pointer(c)->lc = T2; if(T2 != -1) nl.pointer(T2)->parent = c;
    nl.pointer(c)->lc = T3; if(T3 != -1) nl.pointer(T3)->parent = c;
    updateHeight(c);
    nl.pointer(b)->lc = a; nl.pointer(a)->parent = b;
    nl.pointer(b)->rc = c; nl.pointer(c)->parent = b;
    updateHeight(b);
    return b;
}

Rank BBST::tallerChild(Rank x){
    if(stature(nl.pointer(x)->lc) > stature(nl.pointer(x)->rc)){
        return nl.pointer(x)->lc;
    }
    else if(stature(nl.pointer(x)->lc) < stature(nl.pointer(x)->rc)){
        return nl.pointer(x)->rc;
    }
    else{
        if(x == nl.pointer(nl.pointer(x)->parent)->lc){
            return nl.pointer(x)->lc;
        }
        else return nl.pointer(x)->rc;
    }
}

Rank & BBST::FromParentTo(Rank x){
    Rank p = nl.pointer(x)->parent;
    if(p == -1){
        return root;
    }
    if(nl.pointer(p)->lc == x){
        return nl.pointer(p)->lc;
    }
    return nl.pointer(p)->rc;
}

Rank BBST::removeAt(Rank & x, Rank & hot){
    Rank w = x;
    Rank succ = -1;
    if(nl.pointer(x)->lc == -1)
        succ = x = nl.pointer(x)->rc;
    else if(nl.pointer(x)->rc == -1)
        succ = x = nl.pointer(x)->lc;
    else{
        //寻找后继
        Rank s = w;
        if(nl.pointer(w)->rc != -1){
            s = nl.pointer(w)->rc;
            while(nl.pointer(s)->lc != -1) s = nl.pointer(s)->lc;
        }
        else{
            Rank p = nl.pointer(s)->parent;
            while (nl.pointer(p)->rc == s){
                s = p;
                p = nl.pointer(s)->parent;
            }
            s = p;
        }
        w = s;

        int tmp; 
        tmp = nl.pointer(x)->key;
        nl.pointer(x)->key = nl.pointer(w)->key;
        nl.pointer(w)->key = tmp;

        Rank u = nl.pointer(w)->parent;
        succ  = nl.pointer(w)->rc;
        if(u == x){
            nl.pointer(u)->rc = succ;
        }
        else{
            nl.pointer(u)->lc = succ;
        }
    }
    hot = nl.pointer(w)->parent;
    if(succ != -1) nl.pointer(succ)->parent = hot;
    nl.del_node(w);
    return succ;
}

void BBST::updateHeightAbove(Rank x){
    while(x != -1){
        updateHeight(x);
        x = nl.pointer(x)->parent;
    }
}

void BBST::insert(int key){
    Rank & x = search(key);
    if(x != -1) return;
    x = nl.new_node();
    nl.pointer(x)->key = key;
    nl.pointer(x)->parent = _hot;
    updateHeightAbove(x);
    return;
}

void BBST::remove(int key){
    Rank & x = search(key);
    if(x == -1) return;
    removeAt(x, _hot);
    updateHeightAbove(_hot);
    return;
}