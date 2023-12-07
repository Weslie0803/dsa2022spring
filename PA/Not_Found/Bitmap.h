#pragma once

class Bitmap{
    int N;
    int empty;
    unsigned char * c;
    public:
        void init(int n);
        void set(int);
        bool test(int);
        bool full();
        int find();
        ~Bitmap(){
            delete[] c;
        }
};