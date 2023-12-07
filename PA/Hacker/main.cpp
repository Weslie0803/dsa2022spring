#include<cstdio>
#include<cstring>
#include"crc32.h"
#include"hash.h"

int n, s_len; 
unsigned int Hash[1000000];
char salt[5];
HashTable dict;
String A;

const unsigned char No[3] = "No",
                    Init[19] = "0123456789tsinghua";
String Duplicate((unsigned char*)"Duplicate", 9);

/**
 * 自动加盐的crc32
 * @param buf 输入字符串
 * @param len 待转换字符串的长度
*/
inline z_crc_t salted_crc32(unsigned char *buf, z_size_t len){
    return crc32(crc32(0, buf, len),(unsigned char*)salt, s_len);
}

/**
 * 初始化遍历函数
*/
void traverse(String a, int index){
    
    a.push(Init[index]);
    unsigned int pw = salted_crc32(a.str(),a.size());
    String & value = dict[pw];
    if(value.size() > 0) value = Duplicate;
    else value = a;

    if(a.size() >= 5) return;
    
    for(int i = 0; i < 18; i++){
        traverse(a, i);
    }
    a.pop();
}
/**
 * 初始化遍历函数入口
*/
void traverse(){
    String tmp;
    for(int i = 0; i < 18; i++){
        traverse(tmp, i);
    }
}

int main(){
    //处理输入
    scanf("%d", &n);
    scanf("%s", salt);
    s_len = strlen(salt);
    for(int i = 0; i < n; i++){
        scanf("%x", &Hash[i]);
    }

    traverse();//初始化遍历所有1~5长度的字符串

    for(int i = 0; i < n; i++){
        String & tmp = dict[Hash[i]];   //引用哈希表中密文对应的位置
        if(tmp.size() == 0){            //若该位置为空（说明表中不存在对应的明文）
            printf("%s\n",No);
        }
        else{       //若不为空
            tmp.print();    //输出对应的明文（若有多个对应的明文，该位置的明文将被置为Duplicate）
            if(tmp.size() != 9){     //明文长度为9的唯一情况就是Duplicate，Duplicate时不更新集合A
                A.push(tmp.str()[0]); //用首字母更新集合A
                //将集合A中内容添加到散列表中
                for(int j = 0; j < A.size(); j++){//集合A中的第i个字符串从A.str()+j位置开始，长度为A.size()-j
                    if(A.size() - j <= 5) break;//不超过5的串必然已经在初始化散列表内，剪枝
                    unsigned int pw = salted_crc32(A.str()+j, A.size()-j);
                    String & strA = dict[pw];
                    if(strA.size() == 0){//新加入
                        strA = String(A.str() + j, A.size() - j);
                    }
                    else if(strA.size() == 9) continue;//已知有同一密文对应多个明文
                    else if(strA != String(A.str() + j, A.size() - j)){//同一密文对应多个明文
                        strA = Duplicate;
                    }
                    else break;//最后一种情形是发现该串已经在散列表内，那么此时A中的其它串必然也已经在散列表内，剪枝
                }
            }
        }
    }
}