#include"my_hashing.h"

int asc_hashing::operator()(char * str, int N ){
    unsigned int h = 0;
    for(int n = strlen(str), i = 0; i < n; i++){
        h = (h << 5) | (h >> 27); 
        h += (int)str[i];
    }
    return (int)h % N;
}

int utf_hashing::operator()(char * str, int N){
    //建立utf字符与uint的映射
    int p = 0x80;
    int buffer = 0;
    unsigned int h = 0;
    for(int n = strlen(str), i = 0; i < n; i++){
        if(str[i] & p == 0){
            buffer = (int)str[i];
        }
        else if(str[i] & 0xe0 == 0xc0){//110开头
            buffer = (int)(str[i] & 0x1f);
            buffer = (buffer << 6) | (int)(str[i+1] & 0x3f);
            i ++;
        }
        else if(str[i] & 0xe0 == 0xe0){//111开头
            buffer = (int)(str[i] & 0x0f);
            buffer = (buffer << 6) | (int)(str[i+1] & 0x3f);
            buffer = (buffer << 6) | (int)(str[i+2] & 0x3f);
            i += 2;
        }
        h = (h << 5) | (h >> 27); 
        h += buffer;
    }
    return ((int)h + N) % N;
}

void dquad_probe::init(){
    count = 0;
    return;
}

int dquad_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    if(count == 0) first_hash = last_choice;
    count ++;
    if(count % 2 == 0){
        return (2 * first_hash - last_choice + count + table_size) % table_size;
    }
    else{
        return (2 * first_hash - last_choice + table_size) % table_size;
    }
}

void overflow_area::init(){
    return;
}
int overflow_area::operator()(hash_entry* Table, int table_size, int last_choice){
    if(last_choice < table_size){
        return table_size;
    }
    else return last_choice + 1;
}