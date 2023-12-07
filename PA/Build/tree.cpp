#include "tree.h"
#include <cstdio>

void Tree::HeightUpdateAbove(int n){
    //迭代ver
    while(n > 0){
        int son = nodes[nodes[n].son].prefix,   //长子结点的前缀值
            bro = nodes[nodes[n].brother].prefix;   //兄弟结点的前缀值
        int max = ((son + 1) > bro) ? (son + 1) : bro;  //二者的最大值

        if(nodes[n].prefix != max){//若当前结点需要更新
            nodes[n].prefix = max;//更新
            n = nodes[n].prev;//更新前一结点
        }
        else return;//若不需要更新，直接返回
    }
}

void Tree::SizeUpdateAbove(int n, int varies){
    //迭代ver
    while(n > 0){
        nodes[n].size += varies;
        n = nodes[n].father;
    }
}

int t;
Node * stack[1000000];
void Tree::HeightAndSize(int n){
    stack[t] = &(nodes[n]);
    t++;

    while(t != 0){
        if(stack[t-1]->index != nodes[n].prev){
            while (int x = stack[t-1]->index)
            {
                if(nodes[x].son != 0){
                    if(nodes[x].brother != 0){
                        stack[t] = &(nodes[nodes[x].brother]);
                        t++;
                    }
                    stack[t] = &(nodes[nodes[x].son]);
                    t ++;
                }else{
                    stack[t] = &(nodes[nodes[x].brother]);
                    t++;
                }
            }
            t--;
        }
        n = stack[t-1]->index;
        t --;

        nodes[n].prefix = nodes[nodes[n].son].prefix + 1 > nodes[nodes[n].brother].prefix ? nodes[nodes[n].son].prefix + 1 : nodes[nodes[n].brother].prefix;
        nodes[n].s_prefix = nodes[nodes[n].son].s_prefix + nodes[nodes[n].brother].s_prefix;
    }

}


void Tree::init(int N){
    int com, tmp, buf;
    for(int i = 1; i <= N; i++){//对N个结点遍历
        nodes[i].index = i;
        scanf("%d", &com);      //读取子节点个数
        for(int j = 0; j < com; j++){
            scanf("%d", &tmp);      //读取子节点到tmp
            if(tmp == 1) continue;
            if(j == 0) {            //若为长子
                nodes[i].son = tmp;
                nodes[tmp].prev = i;//长子与父亲连接
            }
            else{//若非长子
                nodes[buf].brother = tmp;
                nodes[tmp].prev = buf;//兄弟连接
            }
            nodes[tmp].father = i;//记录父亲
            buf = tmp;
        }
    }

    HeightAndSize(1);
    for(int i = 1; i <= N; i++){
        nodes[i].size = nodes[nodes[i].son].s_prefix;//向上更新规模
    }

}
//根据路径确定结点
int Tree::n_locate(){
    int length, path, current = 1, subnode;
    scanf("%d", &length);//读取路径长度
    for(int i = 0; i < length; i++){
        scanf("%d", &path);
        subnode = nodes[current].son;//当前结点的长子
        for(int j = 0; j < path; j ++){
            if(subnode == 0) return current;//若发现遍历到0结点，说明访问失败，直接返回当前结点
            subnode = nodes[subnode].brother;//向下遍历兄弟
        }
        if(subnode == 0) return current;//若发现遍历到0结点，说明访问失败，直接返回当前结点
        current = subnode;//否则，访问成功，当前结点更新为子节点
    }
    return current;//读取完成后，返回当前结点
}

void Tree::move(){
    int s = n_locate(), //源子树
        p = n_locate(), //父节点
        rank;

    //源子树断开
    int prev = nodes[s].prev,
        bro = nodes[s].brother;
    nodes[bro].prev = prev;
    if(nodes[prev].son == s){//若s为长子
        nodes[prev].son = bro;//兄终弟及
    }
    else{
        nodes[prev].brother = bro;
    }

    nodes[0] = empty;
    nodes[1].father = 0;
    nodes[1].prev   = 0;

    //更新源子树前序结点的高度后缀
    HeightUpdateAbove(prev);
    //更新规模
    SizeUpdateAbove(nodes[s].father, -nodes[s].size);

    //连接到新父节点
    scanf("%d", &rank);
    int son = nodes[p].son;
    if(rank == 0){//插入为父结点的长子
        nodes[p].son = s;
        nodes[s].brother = son;
        nodes[s].prev = p;
        nodes[son].prev = s;
    }
    else{//一般子节点
        for(int i = 1; i < rank; i++){
            son = nodes[son].brother;//找到最小哥哥结点
        }
        int bro = nodes[son].brother;
        nodes[bro].prev = s;
        nodes[s].prev = son;
        nodes[son].brother = s;
        nodes[s].brother = bro;
    }
    nodes[s].father = p;//标注父节点

    nodes[0] = empty;
    nodes[1].father = 0;
    nodes[1].prev   = 0;

    HeightUpdateAbove(s);//更新源子树后缀高度
    HeightUpdateAbove(nodes[s].prev);//更新源子树前序结点后缀高度
    SizeUpdateAbove(p, nodes[s].size);//维护规模
}

void Tree::h_query(){
    int n = n_locate();
    printf("%d\n", nodes[nodes[n].son].prefix);//长子结点的最大后缀即为本节点的高度
}

void Tree::s_query(){
    int n = n_locate();
    printf("%d\n", nodes[n].size);
}