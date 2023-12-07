#include <cstdio>
#include "tree.h"

int N, M, com;
Tree tree;

int main(){
    scanf("%d%d", &N, &M);
    tree.init(N);//读取数据，建立初始树结构
    
    for(int i = 0; i < M; i++){
        scanf("%d", &com);
        switch (com)
        {
        case 0:
            tree.move();
            break;
        
        case 1:
            tree.h_query();
            break;

        case 2:
            tree.s_query();
            break;

        default:
            break;
        }
    }

    return 0;
}