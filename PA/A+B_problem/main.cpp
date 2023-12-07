#include<iostream>
#include<cstring>
#include"LongInt.h"

int main(){
    std::ios::sync_with_stdio(false);
    int N = 0;
    std::cin >> N;
    LongInt arr[2];
    char str1[5001],str2[5001];
    for(int i = 0; i < N; i++){
        std::cin >> str1 >> str2;
        arr[0] = LongInt(str1, strlen(str1));
        arr[1] = LongInt(str2, strlen(str2));
        LongInt tmp = arr[0] * arr[1];
        std::cout << tmp << std::endl;
    }
    return 0;
}