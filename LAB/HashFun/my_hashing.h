#include"hashtable.h"

class asc_hashing : public hashing_strategy{
    public:
    int operator()(char * str, int N ) override; 
};

class utf_hashing : public hashing_strategy{
    public:
    int operator()(char * str, int N) override;
};

class dquad_probe : public collision_strategy{
    public:
    static int count, first_hash;
    void init() override;
    int operator()(hash_entry* Table, int table_size, int last_choice) override;
};

class overflow_area : public collision_strategy{
    public:
    const static int NEW_TABLE_SIZE = 249971;
    void init() override;
    int operator()(hash_entry* Table, int table_size, int last_choice) override;
};