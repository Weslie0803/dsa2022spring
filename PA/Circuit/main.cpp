#include <cstdio>
#include"Node.h"

Tree tree;
int n, k;
char element[500000][65];
item * elem = (item *)element;//用item结构指针，方便读取数据
int result[500000];

int main(){
    //输入
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++){
        scanf("%s", element[i]);
    }
    
    //建树: 预先读取最后的k+2个
    int frontier, current_elem;
    for(frontier = n - 1; frontier > n - k - 3 && frontier > -1; frontier --){
        tree.insert(elem[frontier].str, frontier);
    }

    //从后往前遍历
    for(current_elem = n - 1; current_elem > -1; current_elem --){
        result[current_elem] = tree.search(elem[current_elem].str, current_elem, k);
        if(-1 < frontier){
            //插入结点
            tree.insert(elem[frontier].str, frontier);
            frontier --;
        }
        //删除末尾结点
        int end = current_elem + k + 1;
        if( end < n ){
            tree.del(elem[end].str, end);
        }
    }

    //输出结果
    for(int i = 0; i < n; i++){
        printf("%d\n", result[i]);
    }

    return 0;
}