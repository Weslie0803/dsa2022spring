#include "Node.h"


/**
 * 将结点插入到树中
 * @param str 代表元器件的字符串
 * @param n 元器件的编号
*/
void Tree::insert(char str[], int n){
    Node * node = cl.pointer(root);
    Rank node_rank = root;
    for(int i = 0; i < 64; i++){
        if(str[i] == '0'){
            if(node->lc == -1) node->lc = cl.new_node();//若左子结点未定义，则新建。下同
            cl.pointer(node->lc)->parent = node_rank;//录入子节点的父节点信息
            node_rank = node->lc;
        }
        else{
            if(node->rc == -1) node->rc = cl.new_node();
            cl.pointer(node->rc)->parent = node_rank;
            node_rank = node->rc;
        }
        node = cl.pointer(node_rank);
    }
    node->lc = n;
}

/**
 * 在树中找到元器件的最大异或元器件
 * @param str 代表元器件的字符串
 * @param index 元器件的编号
 * @param k 间隔
 * @return 最大异或元器件的编号
*/
int Tree::search(char str[], int index, int k){
    Node * node = cl.pointer(root);
    Rank node_rank = root;
    for(int i = 0; i < 64; i++){
        if(str[i] == '0'){
            if(node->rc == -1) node_rank = node->lc;//无法反向走时就正向走，否则反向走。下同
            else node_rank = node->rc;
        }
        else{
            if(node->lc == -1) node_rank = node->rc;
            else node_rank = node->lc;
        }
        node = cl.pointer(node_rank);
    }

    if(node->lc == index){//若编号与自身相同
        //此时自身编号一定为0，且搜索范围内的元器件和自身一样
        //因此范围内除自己外最靠前的编号一定为1
        return 1;
    }
    return node->lc;
}

/**
 * 根据路径找到结点位置
 * @return 路径对应结点的在NodeList中的位置
*/
Rank Tree::find(char str[]){
    Rank node_rank = root;
    Node * node = cl.pointer(node_rank);
    for(int i = 0; i < 64; i++){
        if(str[i] == '0'){
            node_rank = node->lc;
        }
        else{
            node_rank = node->rc;
        }
        node = cl.pointer(node_rank);
    }
    return node_rank;
}

/**
 * 删除路径、序号对应的结点
 * 若路径对应的结点序号不匹配，则不进行操作
*/
void Tree::del(char str[], int index){
    Rank node_rank = find(str);
    Node * t = cl.pointer(node_rank);
    if(t->lc != index) return;//结点已经被覆盖时，不操作直接返回
    Rank parent_rank = t->parent;
    cl.del_node(node_rank);//删除叶节点
    while(1){//维护父节点信息，剪除单链
        t = cl.pointer(parent_rank);
        if(node_rank == t->lc){
            t->lc = -1;
        }
        else{
            t->rc = -1;
        }
        if(t->lc == t->rc){//判断该结点是否成为了叶节点（此时二者应均为-1）
            node_rank = parent_rank;
            parent_rank = t->parent;
            cl.del_node(node_rank);//回收
        }
        else break;
    }
}
