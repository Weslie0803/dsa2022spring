#include<cstdio>
#include<cstring>
#include "tree.h"
char str[500001];//读取字符串

//频率预处理数组
int freq[26];

Tree tree;

int main(){
    scanf("%s", str);
    int length = strlen(str);
    //记录频率
    for(int i = 0;i < length; i++){
        freq[(int)(str[i] - 'a')] ++;
    }
    //将出现过的字符输入到tree中
    for(int i = 0; i < 26; i++){
        if(freq[i] != 0){
            tree.push(i, freq[i]);
        }
    }

    //建树
    tree.build();
    
    //记录编码
    tree.record(tree.size * 2 - 2);

    //统计总长
    int Hufflen = 0;
    for(int i = 0; i < length; i++){
        for(int j = 0; j < tree.size; j++){
            if(str[i] == tree.nodes[j].hc.ch){
                Hufflen += tree.nodes[j].Hufflen;
                break;
            }
        }
    }

    //输出
    printf("%d\n", Hufflen);
    for(int i = 0; i < tree.size; i++){
        printf("%c ", tree.nodes[i].hc.ch);
        printb(tree.nodes[i].Huffval, tree.nodes[i].Hufflen);
    }

    return 0;

}