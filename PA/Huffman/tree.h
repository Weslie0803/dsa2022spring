#pragma once

//超字符结构体
struct HuffChar{
    char ch;
    int weight;
};

//树结点
struct Node{
    HuffChar hc;
    int lc = -1, rc = -1;
    bool UNDISCOVERED = true;
    int Hufflen = 0;
    int Huffval = 0;
};

struct Tree{
    Node nodes[52];
    int size = 0;
    Node & root = nodes[50];
    Tree(){}

    //添加字符
    void push(int i, int weight){
        nodes[size].hc.ch = char('a' + i);
        nodes[size].hc.weight = weight;
        size ++;
    }

    //建立树结构
    void build(){
        for(int i = size; i < 2 * size - 1; i++){
            int m1 = -1, m2 = -1;//记录权值最小的超字符位置
            //寻找m1
            for(int j = 0; j < i; j++){//每次扩大查找范围
                if(nodes[j].UNDISCOVERED){
                    m1 = j;
                    break;
                }
            }
            for(int j = 0; j < i; j++){
                if(nodes[j].UNDISCOVERED && nodes[j].hc.weight < nodes[m1].hc.weight){
                    m1 = j;
                }
            }
            nodes[m1].UNDISCOVERED = false;//将m1结点标记为已探索
            //寻找m2（与m1类似）
            for(int j = 0; j < i; j++){
                if(nodes[j].UNDISCOVERED){
                    m2 = j;
                    break;
                }
            }
            for(int j = 0; j < i; j++){
                if(nodes[j].UNDISCOVERED && nodes[j].hc.weight < nodes[m2].hc.weight){
                    m2 = j;
                }
            }
            nodes[m2].UNDISCOVERED = false;//将m2结点标记为已探索
            //添加父节点
            nodes[i].lc = m1;
            nodes[i].rc = m2;
            nodes[i].hc.weight = nodes[m1].hc.weight + nodes[m2].hc.weight;
        }
    }

    //记录字符对应的编码
    void record(int n, int len = 0, int hv = 0, int lr = 0){
        if(n < 0) return;
        nodes[n].Hufflen = len;
        nodes[n].Huffval = hv;
        nodes[n].Huffval <<= 1;
        nodes[n].Huffval += lr;
        record(nodes[n].lc, len + 1, nodes[n].Huffval, 0);//更新左子树
        record(nodes[n].rc, len + 1, nodes[n].Huffval, 1);//更新右子树
    }
};

void printb(int r, int l){
    int probe = 1<<(l-1);   //辅助变量，用于读取对应位的值。初始设置在最高位l位上
    for(int i = 0; i < l; i++){
        if((r & probe) == probe){   //probe对应位为1
            printf("1");
        }
        else{                       //probe对应位为0
            printf("0");
        }
        probe >>= 1;        //右移一位，读取下一位
    }
    printf("\n");
}