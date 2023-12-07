#include<cstdio>
#include"List.h"

char buffer[3200001],//存放初始字符串
    oper, w, c;
int N;
List list;


int main(){
    //处理输入
    scanf("%s", buffer);
    scanf("%d", &N);
    list.init(buffer,N);    //队列初始化
    for(int i = 0; i < N; i++){
        scanf(" %c", &oper);    //读取指令类型
        switch (oper)   //判断指令类型，并执行对应操作
        {
        case '<':
            scanf(" %c", &w);
            list.cursor_leftward(w);
            break;
        case '>':
            scanf(" %c", &w);
            list.cursor_rightward(w);
            break;
        case 'I':
            scanf(" %c %c", &w, &c);
            list.insert(c,w);
            break;
        case 'D':
            scanf(" %c", &w);
            list.del(w);
            break;
        case 'R':
            list.reverse();
            break;
        case 'S':
            list.show();
            break;
        default:
            break;
        }
    }
    return 0;
}