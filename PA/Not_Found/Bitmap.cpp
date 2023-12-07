#include "Bitmap.h"

/**
 * 将Bitmap的某位置为1并更新各位置占据情况
 * 要求该位置原来必须为0, 这一点已经在之前的操作中保证, 因此不再做额外判断
 * @param a 位置
*/
void Bitmap::set(int a){
    empty --;
    c[a >> 3] |= (0x80 >> (a & 0x07));
}

/**
 * 判断该Bitmap是否已经被填满
 * @return 若填满, 则返回true; 否则返回false
*/
bool Bitmap::full(){
    if(empty == 0){
        return true;
    }
    return false;
}

/**
 * 返回输入位置的值
 * @param k 输入位置
 * @return 该位置为1则返回true, 否则返回false
*/
bool Bitmap::test(int k) {
    return c[ k >> 3 ] & ( 0x80 >> (k & 0x07) ); 
}

/**
 * 寻找第一个空位置
 * @return 返回序号最小空位置的位置数据
*/
int Bitmap::find(){
    for(int i = 0; i < N; i++){
        if(c[i] != 0xff){
            for(int j = 0; j < 8; j++){
                if(((0x80 >> j) & c[i]) == 0){
                    return 8 * i + j;
                }
            }
        }
    }
    return -1;
}

/**
 * 初始化Bitmap, 分配空间
 * @param n Bitmap容量上限
*/
void Bitmap::init(int n){
    N = (n+7)/8;
    empty = n;
    c = new unsigned char[N]();
}