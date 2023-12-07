/**********************************************************
 * 实现自动内存管理类，避免调用new/delete拖慢效率
 * 借鉴cursor list的空闲链表结构，以列表的形式管理内存空间
***********************************************************/

#pragma once
#include<cstdio>
#ifndef LIST_CAPACITY
#define LIST_CAPACITY 10
#endif

template <class T>
class Memory_Node{
    public:
        Memory_Node * _next = nullptr;
        T content;
        Memory_Node(){};
        Memory_Node(T &e):content(e){};
        Memory_Node(T &&e):content(e){};
        Memory_Node * next(){
            if(_next != nullptr)
            return this->_next;
            else return this + 1;
        }
};

template <class T>
class Memory_List{
    Memory_Node<T> _node[LIST_CAPACITY];
    Memory_Node<T> * free_begin = _node;
    Memory_Node<T> * free_end = &_node[LIST_CAPACITY - 1];
    int _size = 0;
    public:
        Memory_Node<T> * new_node(T & e){
            if(_size >= LIST_CAPACITY){
                printf("Overflow! No enough space.\n");
                return nullptr;
            }
            Memory_Node<T> * temp = free_begin;
            free_begin = free_begin->next();
            temp->content = e;
            _size ++;
            return temp;
        }
        Memory_Node<T> * new_node(T && e){
            if(_size >= LIST_CAPACITY){
                printf("Overflow! No enough space.\n");
                return nullptr;
            }
            Memory_Node<T> * temp = free_begin;
            free_begin = free_begin->next();
            temp->content = e;
            _size ++;
            return temp;
        }

        void delete_node(Memory_Node<T> * n){
            free_end->_next = n;
            free_end = n;
            _size --;
        }
};