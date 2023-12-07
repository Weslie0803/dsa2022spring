#include<cstdio>
#include"Queap.h"


int nday,_T,
    k[1000000],
    b[1000000],//归并排序辅助空间
    x[1000000],
    m[1000000],
    p[100000],
    q[100000];

Queap _q;

void mergesort(int a[], int len);
int search(int);
int main(){
    //处理输入
    scanf("%d",&nday);
    for(int i = 0; i < nday; i++){
        scanf("%d",&x[i]);
    }
    for(int i = 0; i < nday; i++){
        scanf("%d",&m[i]);
    }
    scanf("%d",&_T);
    for(int i = 0; i < _T; i++){
        scanf("%d%d",&p[i],&q[i]);
    }

    for(int i = 0; i < nday; i++){
        if(_q.size() == 0){//若Queap为空则直接将k置为0
            k[i] = 0;
        }
        else{
            while (_q.size() > m[i])//若当前Queap的长度大于需要考虑的天数
            {
                _q.dequeue();//早先进队的元素出队，直到Queap长度<=需要考虑的天数
            }
            k[i] = _q.getMax();//获取Queap中元素的最大值
        }
        _q.enqueue(x[i]);//当天的确诊数据入队
    }

    //为方便后续的查找，预先对k作排序
    mergesort(k, nday);
    //用查找的方法快速确定风险天数
    for(int i = 0; i < _T; i++){
        int low = search(p[i]),
            mid = search(q[i]) - low;
        printf("%d %d\n",low, mid);
    }

    return 0;
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

int search(int p){//find max i that k[i] < p true
    int lo = 0,
        hi = nday,
        mi = (lo+hi) >> 1;
    while(lo < hi-1){
        mi = (lo + hi) >> 1;
        if(k[mi] < p){
            lo = mi;
        }
        else{
            hi = mi;
        }
    }
    if(k[lo] < p){
        return lo+1;
    }
    return lo;
}