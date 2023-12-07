#include<cstdio>
#include"Bitmap.h"

Bitmap bm;

void printb(int, int);

int main(){
    //bitmap数组初始化
    bm.init(1<<24);
    //读入
    char c;
    int width = 0,  //窗口宽度 
        lb = 0;//lb为当前最短非子串长度的bitmap的下标值，当前最短非子串长度为lb+1，bm[lb]记录了lb+1长度子串的出现情况
    int buffer = 0;
    while((c = getchar()) != '\n'){//以字符形式读取
        if(width < 24)
            width ++;   //预先更新窗口宽度
        else buffer %= (1 << 23);//宽度达到24时不再增加宽度，删除最早读入的位
        buffer <<= 1;
        buffer += int(c - '0'); //更新窗口内容，读入到buffer中

        //遍历buffer的子串，更新bitmap数据
        //从长子串到短子串遍历
        for(int i = width - 1; i >= lb; i--){//对长度为i+1的子串：buffer % (2 << i)
            if(bm.test(buffer % (2 << i))){
                break;//若某子串已经出现过，则该子串的子串也必然已经出现过，故不需要再遍历下去
            }
            bm.set(buffer % (2 << i));//（若还没出现过）将当前子串记录到bitmap中
        }
    }
    int result = bm.find();//在bm+1长度子串的bitmap中寻找字典序最小的串
    if(result == -1) {printf("error!\n");return 1;}
    printb(result, lb + 1);
    return 0;
}


/*************************************
 * 输出对应的01串，并以换行符结尾
 * @param r 输入的int型值
 * @param l 01串的长度
**************************************/
void printb(int r, int l){
    int probe = 1<<(l-1);   //辅助变量，用于读取对应位的值。初始设置在最高位l位上
    for(int i = 0; i < l; i++){
        if((r & probe) == probe){   //probe对应位为1
            printf("1");
        }
        else{                       //probe对应位为0
            printf("0");
        }
        probe >>= 1;        //右移一位，读取下一位
    }
    printf("\n");
}