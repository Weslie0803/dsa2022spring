#pragma once
#include <cstdio>
#define MAX_NODE_NUM 10000000
typedef int Rank;

struct Node{
    Rank lc = -1,
        rc = -1,
        parent = -1;
    int key;
    int height;
};

struct ListNode : public Node{
    Rank link;
};

struct NodeList{
    NodeList();
    ListNode elem[MAX_NODE_NUM];
    Rank free_begin = 0, free_end = MAX_NODE_NUM-1;
    Rank new_node();
    void del_node(Rank t);
    ListNode * pointer(Rank t);
};
