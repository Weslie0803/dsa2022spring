/***********************************************************************
 * 自行实现的cursor list类，同时封装结点类，统一cursor list与chain list形式
 * 实质应当为自行管理内存空间的chain list
************************************************************************/
#pragma once

template <typename T>
class Node
{
    public:
    T elem;
    Node<T> * prev;
    Node<T> * next;
    void connect(Node<T> * next_node){
        this->next = next_node;
        next_node->prev = this;
    }
};

template <typename T>
class List{
    private:
        Node<T> * _node;
        int _size;
        int _capacity;
        Node<T> * header, * trailer;
        Node<T> * free_begin, * free_end;

    public:
        List(){};
        List(int length): _capacity(length){
            _node = new Node<T>[_capacity];
        }
        List(int length, T init[], int ini_len): _capacity(length){
            _node = new Node<T>[_capacity];
            
            /*以输入数组为源初始化列表*/
            for(int i = 0; i < len; i++){
                _node[i].elem = init[i];
                _node[i].connect(&_node[i+1]);
            }

            /*添加哨兵结点*/
            header->connect(_node);
            _node[ini_len - 1].connect(trailer);
            
            header->prev = nullptr;
            trailer->next = nullptr;

            /*初始化空闲链表*/
            for(int i = ini_len; i < length; i++){
                _node[i].next = &_node[i+1];
            }
            free_begin = &_node[ini_len];
            free_end = &_node[length - 1];
            free_end->next = nullptr;
            free_begin->prev = nullptr;
        }

        /**********************************************
         * 在列表中线性查找元素e
         * @param e 待寻找的元素
         * @return 若命中，返回结点的指针；若未命中，返回空指针
        ***********************************************/
        Node<T> * search(T & e){
            Node<T> * it = this->header->next;
            while (it != this->trailer)
            {
                if(it->elem == e){
                    return it;
                }
            }
            return nullptr;
        }

        /*********************************
         * 将元素e插入列表
         * @param le 插入结点左侧结点的指针
         * @param e 待插入的元素
         * @return 插入元素结点的指针
        **********************************/
        Node<T> * insert(Node<T> * le, T & e){
            Node<T> * ri = le->next,
                    * tmp = free_begin;
            free_begin = free_begin->next;
            tmp->elem = e;
            le->connect(tmp);
            tmp->connect(ri);
            
            return tmp;
        }
        /*********************************
         * 将元素e插入列表
         * @param e 待插入的元素
         * @param ri 插入结点右侧结点的指针
         * @return 插入元素结点的指针
        **********************************/
        Node<T> * insert(T & e, Node<T> * ri){
            Node<T> * le = ri->prev,
                    * tmp = free_begin;
            free_begin = free_begin->next;
            tmp->elem = e;
            le->connect(tmp);
            tmp->connect(ri);
            
            return tmp;
        }

        /*******************************
         * 从列表中删除输入的结点
         * @param node 待删除的结点指针
         * @return 被删除结点的内容
        ********************************/
        T && del(Node<T> * node){
            Node<T> * pre = node->prev;
            Node<T> * nxt = node->next;
            free_end->next = node;
            free_end = node;
            pre->connect(nxt);
            return node->elem;
        }
};
