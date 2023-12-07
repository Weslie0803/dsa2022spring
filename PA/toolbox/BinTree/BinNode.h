/********************************
 * 不必动态分配空间的二叉树
 * 实质是自行实现了内存空间的分配
 * 类比cursorList的实现
********************************/
#pragma once

#include "Memory_manage.h"

/*树结点模板类*/
template<typename T> class BinNode{
    public:
    static Memory_List<BinNode<T>> * mem; 
    BinNode<T> * _parent, *_lc, *_rc;
    T _data; int _height;

    BinNode(){};
    BinNode(T &e){_data = e;};
    void Memory_Setting(Memory_List<BinNode<T>> * list){
        mem = list;
    }

    void InsertAsLC(BinNode<T> * lc){
        this->_lc = lc;
        lc->_parent = this;
    }
    BinNode<T> * InsertAsLC(T &e){
        BinNode<T> * temp = &(mem->new_node(e)->content);
        this->_lc = temp;
        return temp;
    }
    BinNode<T> * InsertAsLC(T &&e){
        BinNode<T> * temp = &(mem->new_node(e)->content);
        this->_lc = temp;
        return temp;
    }
    void InsertAsRC(BinNode<T> * rc){
        this->_rc = rc;
        rc->_parent = this;
    }
    int size(){
        int _size = 1;
        if(_lc != nullptr){
            _size += _lc->size();
        }
        if(_rc != nullptr){
            _size += _rc->size();
        }
        return _size;
    }
};
