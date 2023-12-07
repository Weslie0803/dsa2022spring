#include "Node.h"

/**
 * 构造函数：初始化
*/
NodeList::NodeList(){
    elem[0].link = 1;
    for(int i = 1; i < MAX_NODE_NUM; i ++){
        elem[i].link = elem[i-1].link + 1;
    }
    elem[MAX_NODE_NUM - 1].link = -1;
}

/**
 * 新建结点
 * @return 新节点在NodeList中的位置
*/
Rank NodeList::new_node(){
    Rank t = free_begin;
    free_begin = elem[free_begin].link;
    return t;
}

/**
 * 回收结点
 * @param t 待回收结点的指针
*/
void NodeList::del_node(Rank t){
    if(0 <= t && t < MAX_NODE_NUM){
        elem[free_end].link = t;
        free_end = t;
        ListNode no;
        elem[t] = no;//回收后重置结点内容
    }
}

/**
 * @param t 在NodeList中位置
 * @return 结点的指针
*/
ListNode * NodeList::pointer(Rank t){
    return elem + t;
}