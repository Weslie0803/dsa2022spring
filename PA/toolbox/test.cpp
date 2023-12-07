#define LIST_CAPACITY 20
#include"BinNode.h"
#include<iostream>
using namespace std;

Memory_List<BinNode<int>> _mem;
template <typename T>
Memory_List<BinNode<T>> * BinNode<T>::mem = &_mem;

int main(){
    BinNode<int> q;
    BinNode<int> * p = &(_mem.new_node(q)->content);
    q.InsertAsLC(1);
    printf("%d",q._lc->_data);
    return 0;
}