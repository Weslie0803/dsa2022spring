#include<cstdio>
#include"AVL.h"

int n;
char command;
int x;

BBST * bbst = new AVL;//AVL或Splay或BBST
int main(){
    //输入
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf(" %c %d", &command, &x);
        // printf("%c %d\n", command, x);
        switch (command)
        {
        case 'A':
            bbst->insert(x);
            break;
        
        case 'B':
            bbst->remove(x);
            break;
        
        case 'C':
            printf("%d\n", bbst->find(x));
            break;
        default:
            break;
        }
    }
    return 0;
}