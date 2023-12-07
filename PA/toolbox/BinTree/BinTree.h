/********************************
 * 不必动态分配空间的二叉树
 * 实质是自行实现了内存空间的分配
 * 类比cursorList的实现
********************************/

#include"BinNode.h"

/*树模板类*/
template<typename T> class BinTree{
    BinNode<T> * root;
};