#include "Node.h"
void Tree::insert(char str[], int n){}
int Tree::search(char str[], int index, int k){}
Node * Tree::find(char str[]){}


void Tree::insert(item elem[], int n){
    Node * node = root;//初始放在根节点
    Node * next;
    for(int i = 0; i < 64; i++){        
        if(elem[n].str[i] == '0') next = node->lc;
        else next = node->rc;
        
        if(next == nullptr){//如果下个结点尚未被插入
            if(next == node->lc) {
                node->lc = cl.new_node();
                next = node->lc;
            }
            else{
                node->rc = cl.new_node();
                next = node->rc;
            }//创建新结点
            
            next->index = n;
            next->prefix = i;
            next->parent = node;
            node = next;
            return;
        }
        else if(next->prefix > i){//如果下个结点是压缩结点
            for(; i < next->prefix; i++){
                if(elem[n].str[i] != elem[next->index].str[i]){
                    Node * new_one = cl.new_node();
                    if(next == node->lc){
                        node->lc = new_one;
                    }
                    else{
                        node->rc = new_one;
                    }
                    new_one->parent = node;
                    if(elem[n].str[i] == '0'){
                        new_one->index = n;
                        new_one->prefix = i-1;
                        new_one->lc = cl.new_node();
                        new_one->lc->index = n;
                        new_one->lc->prefix = i;
                        new_one->rc = next;
                    }
                    else{
                        new_one->index = n;
                        new_one->prefix = i-1;
                        new_one->rc = cl.new_node();
                        new_one->rc->index = n;
                        new_one->rc->prefix = i;
                        new_one->lc = next;
                    }
                    next->parent = new_one;
                }
            }
            return;
        }
        
        node = next;
    
    }
}
/**
     * 按照路径向下找路
     * 发现需要新增结点时提起注意：
     *      如果当前结点已经是叶节点，找到不同位，执行分叉操作（找到底了还找不到就直接覆盖）
     *          当场分开，还是向下长枝再分？
     *              当场分开：记录一个共同区段，记录分开的位点
     *              后续插入时需要试探位置
    */