#include "kth.h"
typedef int Rank;
inline Rank Parent(Rank i){return (i - 1) >> 1;}
inline Rank LChild(Rank i){return (i << 1) + 1;}
inline Rank RChild(Rank i){return (i << 1) + 2;} 

int B[500000];//归并辅助空间
int _a[500000];
int _b[500000];
int _c[500000];//a b c的下标排序数组
void _sort(int [], int len, int label);

struct pair{//记录下标排序数组的下标
    int x, y, z;
    pair(){};
    pair(int _x, int _y, int _z){x = _x; y = _y; z = _z;};
};
void swap(pair & i, pair & j){ pair t = i;   i = j;    j = t;}
bool _compare(pair i, pair j){//在堆中使用的比较函数
    return compare(_a[i.x], _b[i.y], _c[i.z], _a[j.x], _b[j.y], _c[j.z]);
}

//对_a排序时使用
bool compare1(int i, int j){
    return compare(i, 1, 1, j, 1, 1);
}
//对_b排序时使用
bool compare2(int i, int j){
    return compare(1, i, 1, 1, j, 1);
}
//对_c排序时使用
bool compare3(int i, int j){
    return compare(1, 1, i, 1, 1, j);
}

class Heap{//小顶堆，参照讲义实现
    pair p[4000001];
    int size = 0;
    public:
    pair delMin();//摘除堆顶最小元素
    void insert(pair);//插入元素
    Rank ProperParent(pair * A, Rank n, Rank i);//在下滤中使用，返回自身与子节点中最小者
    Rank percolateDown(pair * A, Rank n, Rank i);
    Rank percolateUp(pair * A, Rank i);
};

Rank Heap::percolateUp(pair * A, Rank i){
    while(0 < i){
        Rank j = Parent(i);
        if(_compare(p[j], p[i])){
            break;
        }
        swap(p[i], p[j]);
        i = j;
    }
    return i;
}

void Heap::insert(pair t){
    p[size] = t;
    size ++;

    percolateUp(p, size - 1);
}

Rank Heap::ProperParent(pair * A, Rank n, Rank i){
    Rank LC = LChild(i);
    Rank RC = RChild(i);
    Rank candidate;
    if(RC < n){
        if(_compare(A[LC], A[RC])){
            candidate = LC;
        }
        else{
            candidate = RC;
        }
        if(_compare(A[i], A[candidate])){
            return i;
        }
        else return candidate;
    }
    else if(LC < n){
        if(_compare(A[i], A[LC])){
            return i;
        }
        else return LC;
    }
    else{
        return i;
    }
}

Rank Heap::percolateDown(pair * A, Rank n, Rank i){
    Rank j;
    while(true){
        j = ProperParent(A, n, i);
        if(i != j){
            swap(A[i], A[j]);
            i = j;
        }
        else break;
    }
    return i;
}

pair Heap::delMin(){
    pair Min = p[0];
    p[0] = p[size - 1];
    size --;
    percolateDown(p, size, 0);
    return Min;
}

Heap PQ;

/**
 * @param n 数组长度
 * @param k 要求的序数
*/
void get_kth(int n, int k, int *x, int *y, int *z){
    //下标数组初始化
    for(int i = 0; i < n; i++){
        _a[i] = i+1;
        _b[i] = i+1;
        _c[i] = i+1;
    }
    //排序
    _sort(_a, n, 1);
    _sort(_b, n, 2);
    _sort(_c, n, 3);
    pair p0 = {0,0,0};
    PQ.insert(p0);//插入初始结点
    pair out;
    for(int i = 0; i < k; i++){
        out = PQ.delMin();
        //对所有结点(x,y,z)都插入(x+1,y,z)
        if(out.x+1 < n)
        PQ.insert(pair(out.x + 1, out.y, out.z));
        if(out.x == 0){
            //在x = 0时插入(x,y+1,z)
            if(out.y + 1 < n)
            PQ.insert(pair(out.x, out.y + 1, out.z));
            if(out.y == 0){
                //在y = 0时插入(x,y,z+1)
                if(out.z + 1 < n)
                PQ.insert(pair(out.x, out.y, out.z + 1));
            }
        }
    }
    *x = _a[out.x];
    *y = _b[out.y];
    *z = _c[out.z];
}

//归并排序
void _sort(int A[], int length, int label){
    bool (*comp)(int i, int j);//函数指针
    switch (label)//根据label选择比较函数
    {
    case 1:
        comp = compare1;
        break;
    case 2:
        comp = compare2;
        break;
    case 3:
        comp = compare3;
        break;
    default:
        break;
    }

    if(length <= 1) return;
    int mi = length >> 1,
        it1 = 0,
        it2 = mi;
    _sort(&A[0], mi, label);
    _sort(&A[mi],length - mi, label);
    for(int i = 0; i < length; i++){
        if(it1 < mi && it2 < length){
            if(comp(A[it1], A[it2])){
                B[i] = A[it1];
                it1 ++;
            }
            else{
                B[i] = A[it2];
                it2++;
            }
        }
        else if(it1 >= mi){
            B[i] = A[it2];
            it2++;
        }
        else{
            B[i] = A[it1];
            it1++;
        }
    }
    for(int i = 0; i < length; i++){
        A[i] = B[i];
    }
    return;
}