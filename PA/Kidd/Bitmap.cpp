#include "Bitmap.h"

void Bitmap::set(int a){
    empty --;
    c[a >> 3] |= (0x80 >> (a & 0x07));
}

bool Bitmap::full(){
    if(empty == 0){
        return true;
    }
    return false;
}

bool Bitmap::test(int k) {
    return c[ k >> 3 ] & ( 0x80 >> (k & 0x07) ); 
}

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

void Bitmap::init(int n){
    N = (n+7)/8;
    empty = n;
    c = new unsigned char[N];
}