#pragma once
typedef int Rank;
class List{
    private:
        char elem[14400004];    //存放结点字符内容
        Rank Righ_link[14400004];   //右侧结点的位置
        Rank Left_link[14400004];   //左侧结点的位置
        
        bool unreversible = false;  //判断是否可进行reverse的辅助记录量
        Rank _free_begin, _free_end,    //空闲链表的起止点
             header, trailer,           //正向链表的哨兵结点
             header2, trailer2,         //镜像链表的哨兵结点
             L_cursor2, R_cursor2,      //正向链表的光标位置：指向光标左侧的元素
             L_cursor, R_cursor;        //镜像链表的光标位置：指向光标右侧的元素
    public:
        void init(char buf[], int n_op);    //初始化

        void cursor_leftward(char);         //光标左移
        void cursor_rightward(char);        //光标右移
        void insert(char c, char w);        //光标左侧插入结点
        void del(char);                     //删除光标右侧结点
        void reverse();                     //翻转左右光标间的内容
        void show();                    //输出列表内容（正向链表）
};
