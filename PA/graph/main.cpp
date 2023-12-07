#include<cstdio>

int n,m,px,py,
    x[200000],
    y[200000];

void sort(int a[], int len);
void mergesort(int a[], int len);
bool compare(int _x, int _y, int _px, int _py); //\frac{x}{_x} + \frac{y}{_y} >= 1  ==>  x * _y + y * _x >= _x_y
int search(int _px, int _py);

int main(){
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        scanf("%d",&x[i]);
    }
    for(int i = 0; i < n; i++){
        scanf("%d",&y[i]);
    }
    sort(x,n);
    sort(y,n);
    scanf("%d",&m);
    for(int i = 0; i < m; i++){
        scanf("%d%d",&px,&py);
        printf("%d\n",search(px,py));
    }
    return 0;
}

void sort(int a[], int len){
    if(len <= 1) return;
    int lo = 0, hi = len - 2, tmp;
    while(lo <= hi){
        while(a[lo] <= a[len - 1] && lo <= hi){
            lo ++;
        }
        while(a[hi] >= a[len - 1] && lo <= hi){
            hi --;
        }
        if(lo <= hi){
            tmp = a[lo];
            a[lo] = a[hi];
            a[hi] = tmp;
        }
    }
    tmp = a[len - 1];
    a[len - 1] = a[lo];
    a[lo] = tmp;
    sort(&a[0],lo);
    sort(&a[lo + 1],len - lo - 1);
}

bool compare(int i, int _px, int _py){
    long long   px = _px,
                py = _py,
                _x = x[i],
                _y = y[i];
    return !(_px * _y + _py * _x < _x * _y);
}

void mergesort(int a[], int len){
    if(len <= 1) return;
    int mi = len >> 1;
    mergesort(&a[0], mi);
    mergesort(&a[mi],len - mi);
    int b[len],
        it1 = 0,
        it2 = mi;
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

int search(int px, int py){//find max i that comp(i,x,y) true
    int lo = 0,
        hi = n,
        mi = (lo+hi) >> 1;
    while(lo < hi-1){
        mi = (lo + hi) >> 1;
        if(compare(mi,px,py)){
            lo = mi;
        }
        else{
            hi = mi;
        }
    }
    if(compare(lo,px,py)){
        return lo+1;
    }
    return lo;
}