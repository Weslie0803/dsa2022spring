#include"hash.h"
#include<cstring>
#include<cstdio>

/* 基于字符串构造String */
String::String(unsigned char c[], int len = 8){
    for(int i = 0 ; i < len; i++){
        if(c[i] != 0){
            content[i] = c[i];
            length ++;
        }
        else{
            break;
        }
    }
}

/**
 * String可以实现栈的结构
 * 为适应集合A的功能，当长度到达8后，每次push时抹去首位，保持长度不变
*/
void String::push(char c){
    if(length < 8){
        content[length] = c;
        length ++;
    }
    else{
        memcpy(content, content+1, 7);
        content[7] = c;
    }
}
/*排出末尾字符，若栈空则报错*/
char String::pop(){
    if(length > 0){
        length --;
        return content[length];
    }
    printf("Empty!\n");
    return 0;
}
//返回字符串
unsigned char * String::str(){
    return content;
}
//返回长度
int String::size(){
    return length;
}
//输出内容
void String::print(){
    for(int i = 0; i < length; i++){
        printf("%c", content[i]);
    }
    printf("\n");
}

/**
 * 重载运算符实现散列表访问
 * @param key 密文
 * @return 明文位置的引用
*/
String & HashTable::operator[](unsigned int key){
    int index = hash(key);
    int count = 0;
    //双向平方试探
    //由于没有删除操作，不会引起试探链断裂，因此不必实现懒惰删除
    while(bucket[index].key != key && bucket[index].value.length != 0){
        count ++;
        if(count % 2 != 0){
            index = hash(key) * 2 - index + count;
        }
        else{
            index = hash(key) * 2 - index;
        }
        index = hash(index);
    }
    //键值记录为密文（记录密文与该位置的匹配），为下一步可能的赋值做准备
    bucket[index].key = key;
    return bucket[index].value;
}

/*散列函数：取余法*/
unsigned int HashTable::hash(unsigned int key){
    int index = (key + TABLE_SIZE) % TABLE_SIZE;
    return index;
}

bool String::operator==(const String & s){
    if(length != s.length) return false;
    for(int i = 0; i < length; i++){
        if(content[i] != s.content[i]) return false;
    }
    return true;
}

bool String::operator!=(const String & s){
    return !(*this==(s));
}