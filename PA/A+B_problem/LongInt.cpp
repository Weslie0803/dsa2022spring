#include "LongInt.h"
/*
LongInt::LongInt(std::string str){
    int length = str.size();
    while(length > 4){
        int tmp = std::stoi(str.substr(length-4,4));
        this->push_back(tmp);
        length -= 4;
    }
    this->push_back(std::stoi(str.substr(0,length)));
}
*/
LongInt::LongInt(char str[], int len){
    this->length = (len - 1) / 4 + 1;
    int tmp = 0, j = 0;
    for(int i = 0; i < len; i++){
        switch(i%4){
            case 0: tmp += (str[len - 1 - i] - '0'); break;
            case 1: tmp += (str[len - 1 - i] - '0') * 10; break;
            case 2: tmp += (str[len - 1 - i] - '0') * 100; break;
            default: 
                tmp += (str[len - 1 - i] - '0') * 1000;
                this->a[j] = tmp;
                j ++; tmp = 0;
                break;
        }
    }
    if(tmp != 0 || j == 0){
        this->a[j] = tmp;
    }
    this->de_zero();
}

LongInt LongInt::operator+(const LongInt & _LI)const{    //O(n)
    LongInt sum;
    if(this->sign == false && _LI.sign == false){
        sum.sign = false;
    }
    else if(this->sign == true && _LI.sign == false){
        LongInt tmp = _LI;
        tmp.sign = true;
        sum = *this - tmp;
        return sum;
    }
    else if(this->sign == false && _LI.sign == true){
        sum = *this;
        sum.sign = true;
        return _LI - sum;
    }
    if(this->length > _LI.length){
        sum = *this;
        for(int i = 0; i < _LI.length; i++){
            sum.a[i] += _LI.a[i];
        }
    }
    else {
        sum = _LI;
        for(int i = 0; i < this->length; i++){
            sum.a[i] += this->a[i];
        }
    }
    sum.self_check();
    return sum;
}

LongInt LongInt::operator-(const LongInt & _LI)const{
    LongInt result;
    if(_LI > *this){
        result = _LI - *this;
        result.sign = false;
    }
    else{
        result = *this;
        for(int i = 0; i < _LI.length; i++){
            result.a[i] -= _LI.a[i];
        }
        result.self_check();
        result.de_zero();
    }
    return result;
}

LongInt LongInt::operator*(const LongInt & _LI)const{
    if(_LI.length > this->length) return _LI * *this;
    LongInt tmp = *this;
    if(this->sign == _LI.sign) tmp.sign = true;
        else tmp.sign = false;
    
    if(_LI.length <= 1){
        for(int i = 0; i < this->length; i++){
            tmp.a[i] *= _LI.a[0];
        }
        tmp.self_check();
        return tmp;
    }
    //divide
    LongInt A,B,C,D,AC,BD,ABDC;
    int seg = _LI.length >> 1;
    for(int i = 0; i < seg; i++){
        B.a[i] = this->a[i];
        D.a[i] = _LI.a[i];
    }
    for(int i = seg; i < this->length; i++){
        A.a[i - seg] = this->a[i];
    }
    for(int i = seg; i < _LI.length; i++){
        C.a[i - seg] = _LI.a[i];
    }
    A.length = this->length - seg;
    C.length = _LI.length - seg;
    B.length = D.length = seg;
    D.de_zero();
    B.de_zero();
    //calculate
    AC = A * C;
    BD = B * D;
    ABDC = (A - B) * (D - C);
    LongInt BCAD = AC + BD + ABDC;
    //merge
    tmp.length = AC.length + seg * 2;
    for(int i = 0; i < tmp.length; i++){
        if(i < BD.length){
            tmp.a[i] = BD.a[i];
        }
        else if(i < seg * 2){
            tmp.a[i] = 0;
        }
        else{
            tmp.a[i] = AC.a[i - seg * 2];
        }
    }
    for(int i = 0; i < BCAD.length; i++){
        tmp.a[seg + i] += BCAD.a[i];
    }
    tmp.self_check();
    return tmp;
}

bool LongInt::operator>(const LongInt & _LI)const{
    if(this->sign == true && _LI.sign == false){
        return true;
    }
    else if(this->sign == false && _LI.sign == true){
        return false;
    }
    else if(this->sign == true && _LI.sign == true){
        if(this->length > _LI.length){
            return true;
        }
        else if(this->length < _LI.length){
            return false;
        }
        else{
            int length = this->length;
            for(int i = length - 1; i >= 0; i--){
                if(this->a[i] > _LI.a[i]){
                    return true;
                }
                if(this->a[i] < _LI.a[i]){
                    return false;
                }
            }
            return false;
        }
    }
    else{// double minus situation
        if(this->length > _LI.length){
            return false;
        }
        else if(this->length < _LI.length){
            return true;
        }
        else{
            int length = this->length;
            for(int i = length - 1; i >= 0; i--){
                if(this->a[i] > _LI.a[i]){
                    return false;
                }
                if(this->a[i] < _LI.a[i]){
                    return true;
                }
            }
            return false;
        }
    }
}

void LongInt::self_check(){//O(n)
    int length = this->length;
    int tmp = 0;

        this->a[i] += tmp;
        if(this->a[i] >= 10000){
            tmp = this->a[i]/10000;
            this->a[i] %= 10000; 
        }
        else if(this->a[i] < 0){
            tmp = -1;
            this->a[i] += 10000;
        }
        else{
            tmp = 0;
        }
    }
    while(tmp != 0){
        this->push_back(tmp%10000);
        tmp /= 10000;
    }
}

void LongInt::de_zero(){
    while(this->a[this->length - 1] == 0){
        if(this->length > 1){
            this->pop_back();
        }
        else break;
    }
}

std::ostream & operator<<(std::ostream & out, const LongInt & _LI){
    int length = _LI.length;
    if(_LI.sign == false) out << '-';
    for(int i = length - 1; i >= 0; i--){
        if(_LI.a[i] < 1000 && i != (length - 1)){
            if(_LI.a[i] >= 100)
                out << "0";
            else if(_LI.a[i] >= 10)
                out << "00";
            else out << "000";
        }
        out << _LI.a[i];
    }
    return out;
}