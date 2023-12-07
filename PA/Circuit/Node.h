#pragma once
#define MAX_NODE_NUM 25000000
typedef int Rank;


struct item{
    char str[64];//二进制串的内容
    char enter;//换行符，直接忽略
};

struct Node{
    Rank lc = -1,//左子结点，顺便给叶结点用来记录index  
        rc = -1, //右子节点
        parent = -1;//父节点
};

struct ListNode : public Node{
    Rank link;//NodeList中指引下一个结点的位置
};

struct NodeList{
    NodeList();
    ListNode elem[MAX_NODE_NUM];
    Rank free_begin = 0, free_end = MAX_NODE_NUM-1;
    Rank new_node();
    void del_node(Rank t);
    ListNode * pointer(Rank t);
};

struct Tree{
    NodeList cl;
    Rank root = cl.new_node();
    void insert(char [], int );
    int search(char [], int index, int k);//找到最大异或值
    Rank find(char []);//找到对应叶节点
    void del(char [], int );
};

