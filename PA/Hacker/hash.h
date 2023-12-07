#pragma once
#define TABLE_SIZE 9999971
class HashTable;

class String{
    unsigned char content[9];
    int length = 0;
    public:
        String(){}
        String(char a[]);
        String(unsigned char a[], int len);
        void push(char);
        char pop();
        int size();
        unsigned char * str();
        void print();
        bool operator==(const String &);
        bool operator!=(const String &);
    friend HashTable;
};

struct Entry{
    unsigned int key;
    String value;
};

class HashTable{
    //表长采用了模4余3的素数
    Entry bucket[TABLE_SIZE];
    unsigned int hash(unsigned int);
    public:
        String & operator[](unsigned int);
};