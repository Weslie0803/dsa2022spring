#include"Bitmap.h"
#include<iostream>



void Eratosthenes( int n) {
    Bitmap B;
    B.init( n );
    B.set( 0 ); B.set( 1 );
    for ( int i = 2; i < n; i++ )
        if ( ! B.test( i ) )
            for ( int j = 2*i; j < n; j += i )
                B.set( j );
                
    int count = 0;
    for(int i = 0; i < n; i++){
        if( ! B.test(i)){
            std::cout << i << '\t';
            count ++;
            if(count % 10 == 0){
                std::cout << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

int main(){
    Eratosthenes(10000000);
    return 0;
}