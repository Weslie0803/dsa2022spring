#pragma once
#include<ostream>
class LongInt{
    int a[2560];//123321 is [3321,12]
    int length = 0;
    bool sign = true;
    void self_check();
    void de_zero();
    void push_back(int c){
        this->a[length] = c;
        length ++;
    }
    int pop_back(){
        length --;
        return this->a[length];
    }
    public:
        LongInt(){};
        //LongInt(std::string);
        LongInt(char str[], int len);
        LongInt(int num){   //O(log n)
            while(num != 0){
                this->push_back(num % 10000);
                num /= 10000;
            }
        }
        LongInt operator+(const LongInt &)const;
        LongInt operator-(const LongInt &)const;
        LongInt operator*(const LongInt &)const;
        bool operator>(const LongInt &)const;
        friend std::ostream & operator<<(std::ostream & out, const LongInt & _LI);
};