#include"List.h"
#include<cstring>
#include<cstdio>

void List::init(char buf[], int n_op){//list中不存放\0
    int _size = strlen(buf);
    //空闲链表与数据链表起止点初始化
    Rank _data_begin = 0;
    Rank _data_end   = _size - 1;
    _free_begin = _size * 2 + 4;
    _free_end = _size * 2 + n_op * 2 + 3;
    //数据链表初始化
    for(int i = 0; i < _size; i++){
        elem[i] = buf[i];//初始化正链表
        Righ_link[i] = i + 1;
        Left_link[i] = i - 1;
        elem[i + _size] = buf[_size - i - 1];//初始化反链表
        Righ_link[i + _size] = i + _size + 1;
        Left_link[i + _size] = i + _size - 1;
    }
    //添加哨兵结点
    header = _size * 2;
    Left_link[header] = -1;
    Righ_link[header] = _data_begin;
    Left_link[_data_begin] = header;

    trailer = _size * 2 + 1;
    Righ_link[trailer] = -1;
    Left_link[trailer] = _data_end;
    Righ_link[_data_end] = trailer;

    header2 = _size * 2 + 2;
    Left_link[header2] = -1;
    Righ_link[header2] = _data_begin + _size;
    Left_link[_data_begin + _size] = header2;

    trailer2 = _size * 2 + 3;
    Righ_link[trailer2] = -1;
    Left_link[trailer2] = _data_end + _size;
    Righ_link[_data_end + _size] = trailer2;
    //空闲链表初始化
    //由于空闲链表只需要单向访问，故不必初始化Left_link
    for(int i = _free_begin; i < _free_end; i++){
        Righ_link[i] = i + 1;
    }
    Righ_link[_free_end] = -1;
    //光标位置初始化
    L_cursor = _data_begin;
    R_cursor = trailer;
    L_cursor2 = Left_link[trailer2];
    R_cursor2 = header2;
}

void List::cursor_leftward(char w){
    bool was_overlap = L_cursor == R_cursor;    //检测移动前光标是否重合
    if(w == 'L'){
        if(Left_link[L_cursor] == header){      //若左光标左边为哨兵结点
            printf("F\n");                      //无法移动
            return;
        }
        else{//可以移动
            L_cursor = Left_link[L_cursor];     //左光标左移
            L_cursor2 = Righ_link[L_cursor2];   //镜像左光标右移
            printf("T\n");
            if(was_overlap){                //若移动前为重合状态
                unreversible = false;       //判断左光标在右光标左侧，并非不可反转
            }
        }
    }
    else if(w == 'R'){
        if(Left_link[R_cursor] == header){      //若右光标左边为哨兵结点
            printf("F\n");                      //无法移动
            return;
        }
        else{//可以移动
            R_cursor = Left_link[R_cursor];     //右光标左移
            R_cursor2 = Righ_link[R_cursor2];   //镜像右光标右移
            printf("T\n");
            if(was_overlap){                //若移动前为重合状态
                unreversible = true;        //判断右光标在左光标左侧，不可反转
            }
        }
    }
}
void List::cursor_rightward(char w){
    bool was_overlap = L_cursor == R_cursor;    //检查移动前光标是否重合
    if(w == 'R'){
        if(R_cursor == trailer){                //若右光标指向哨兵结点
            printf("F\n");                      //不可移动
            return;
        }
        else{//可以移动
            R_cursor = Righ_link[R_cursor];     //右光标右移
            R_cursor2 = Left_link[R_cursor2];   //镜像右光标左移
            printf("T\n");
            if(was_overlap){                    //若移动前光标重合
                unreversible = false;           //判断右光标在左光标右侧，并非不可反转
            }
        }
    }
    else if(w == 'L'){
        if(L_cursor == trailer){                //若左光标指向哨兵结点
            printf("F\n");                      //不可移动
            return;
        }
        else{//可以移动
            L_cursor = Righ_link[L_cursor];     //左光标右移
            L_cursor2 = Left_link[L_cursor2];   //镜像左光标左移
            printf("T\n");
            if(was_overlap){            //若移动前两光标重合
                unreversible = true;    //判断左光标在右光标右侧，不可反转
            }
        }
    }
}
void List::insert(char c, char w){
    Rank cursor, cursor2, new_node, new_node2;
    if(w == 'L') {  //在左光标插入结点
        cursor = L_cursor;
        cursor2 = L_cursor2;
    }
    else {//右光标
        cursor = R_cursor;
        cursor2 = R_cursor2;
    }
    //在空闲链表起始处插入新结点
    new_node = _free_begin;
    //维护空闲链表
    _free_begin = Righ_link[_free_begin];
    elem[new_node] = c;
    //插入镜像新结点
    new_node2 = _free_begin;
    _free_begin = Righ_link[_free_begin];
    elem[new_node2] = c;

    //新结点的前后结点信息
    Left_link[new_node] = Left_link[cursor];
    Righ_link[new_node] = cursor;
        //镜像新结点的前后结点信息
    Righ_link[new_node2] = Righ_link[cursor2];
    Left_link[new_node2] = cursor2;
    
    //维护新结点的前后关系
    Rank l = Left_link[cursor];
    Left_link[cursor] = new_node;
    Righ_link[l] = new_node;

    Rank r = Righ_link[cursor2];
    Righ_link[cursor2] = new_node2;
    Left_link[r] = new_node2;

    printf("T\n");
}
void List::del(char w){
    Rank * cursor, * cursor2;
    if(w == 'L') {//左光标
        cursor = &L_cursor;
        cursor2 = &L_cursor2;
    }
    else {//右光标
        cursor = &R_cursor;
        cursor2 = &R_cursor2;
    }
    //光标右侧为空情形
    if(*cursor == trailer){
        printf("F\n");//删除失败
        return;
    }
    //cursor左右元素脱钩
    Rank l = Left_link[*cursor],
        r = Righ_link[*cursor];
    Righ_link[l] = r;
    Left_link[r] = l;

    Rank r2 = Righ_link[*cursor2],
        l2 = Left_link[*cursor2];
    Left_link[r2] = l2;
    Righ_link[l2] = r2;

    //维护空闲链表
    Righ_link[_free_end] = *cursor;
    _free_end = *cursor;
    Righ_link[_free_end] = *cursor2;
    _free_end = *cursor2;
    Righ_link[_free_end] = -1;
    //cursor指向新位置
    if(L_cursor == R_cursor){
        L_cursor = r;
        R_cursor = r;
        L_cursor2 = l2;
        R_cursor2 = l2;
    }
    else {
        *cursor = r;
        *cursor2 = l2;
    }
    printf("T\n");
}
void List::reverse(){
    if(unreversible || L_cursor == R_cursor){//判断不可反转（左右光标错位或重合）
        printf("F\n");
        return;
    }
    
    //正链表段与镜像链表段交换
    //接口位置备份
    Rank l = L_cursor,
         r = R_cursor,
         l2 = L_cursor2,
         r2 = R_cursor2,
         ll = Left_link[l],
         lr = Left_link[r],
         rl2 = Righ_link[l2],
         rr2 = Righ_link[r2];
    Righ_link[ll] = rr2;
    Left_link[rr2] = ll;

    Righ_link[r2] = l;
    Left_link[l] = r2;

    Righ_link[lr] = rl2;
    Left_link[rl2] = lr;

    Righ_link[l2] = r;
    Left_link[r] = l2;

    //左光标位置维护
    L_cursor = rr2;
    L_cursor2 = lr;
    
    printf("T\n");

}
void List::show(){
    Rank it = Righ_link[header];
    while(it != trailer){
        printf("%c", elem[it]);
        it = Righ_link[it];
    }
    printf("\n");
}
