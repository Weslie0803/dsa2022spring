#include<cstdio>
#include"Segment.h"

SegmentTree tree;   //线段树数据结构

int n,m,
    _i[200000], _j[200000],//存放输入数据
    left[200000], right[200000];//拷贝存放输入数据，用于生成区间
int b[400000];//归并排序的辅助空间，同时用于存储区间信息（生成叶结点）
char com[200000];//存放输入数据的操作名称（H or Q）

//归并排序
void mergesort(int a[], int len);

/**
 * 生成区间信息用于建立线段树结构
 * @return 生成区间的数目，即叶节点个数
*/
int Build();

int main(){
    //输入
    scanf("%d%d",&n,&m);
    for(int i = 0; i < m; i++){
        scanf(" %c %d%d", &com[i], &_i[i], &_j[i]);
        left[i] = _i[i] - 1;//区间采用左开右闭的格式
        right[i] = _j[i];
    }
    //建立线段树
    tree.initialize(b, Build());

    for(int i = 0; i < m; i++){
        if(com[i] == 'H'){
            tree.InsertSegment(0,_i[i] - 1,_j[i]);
        }
        else{
            printf("%lld\n",tree.Query(0, _i[i] - 1, _j[i]));
        }
    }
    return 0;
}

int Build(){
    mergesort(left,m);
    mergesort(right,m);//对复制的输入数据分别进行排序
    //对left和right做二路归并，顺便完成去重
    //二路归并+去重的结果存放在数组b中
    int it1 = 0, it2 = 0, len;
    for(int i = 0; ; i++){
        //去重
        if(i > 0){
            while(b[i - 1] == left[it1]  && it1 < m)
                it1 ++;
            while(b[i - 1] == right[it2] && it2 < m)
                it2 ++;
        }
        if(it1 < m && it2 < m){
            if(left[it1] <= right[it2]){
                b[i] = left[it1];
                it1 ++;
            }
            else{
                b[i] = right[it2];
                it2 ++;
            }
        }
        else if(it1 >= m){
            b[i] = right[it2];
            it2 ++;
        }
        else{
            b[i] = left[it1];
            it1 ++;
        }
        //判断是否完成
        if(it1 >= m && it2 >= m){
            len = i;//离散化区间的数量，即叶节点的数量
            return len;
        }
    }
}

void mergesort(int a[], int len){//mergesort 实现归并排序
    if(len <= 1) return;
    int mi = len >> 1,
        it1 = 0,
        it2 = mi;
    mergesort(&a[0], mi);
    mergesort(&a[mi],len - mi);
    for(int i = 0; i < len; i++){
        if(it1 < mi && it2 < len){
            if(a[it1] <= a[it2]){
                b[i] = a[it1];
                it1 ++;
            }
            else{
                b[i] = a[it2];
                it2++;
            }
        }
        else if(it1 >= mi){
            b[i] = a[it2];
            it2++;
        }
        else{
            b[i] = a[it1];
            it1++;
        }
    }
    for(int i = 0; i < len; i++){
        a[i] = b[i];
    }
    return;
}
