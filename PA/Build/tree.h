#pragma once

struct Node{
    int index;
    int prev = 0;
    int father = 0;
    int son = 0;
    int brother = 0;
    int size = 1;
    int prefix = 0;
    int s_prefix = 1;
};

const Node empty = {
    .index = 0,
    .prev = 0,
    .father = 0,
    .son = 0,
    .brother = 0,
    .size = 1,
    .prefix = 0,
    .s_prefix = 1
};

class Tree{
    Node nodes[1000001];
    int n_locate();
    void HeightUpdateAbove(int n);
    void SizeUpdateAbove(int n, int varies);
    void HeightAndSize(int n);
    public:
        void init(int N);
        void move();
        void h_query();
        void s_query();
};