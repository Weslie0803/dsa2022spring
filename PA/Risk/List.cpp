#include<list>

std::list<int> lst;


class List{
    private:
        int * elem;
        int * link;
        int Capacity;
    public:
        List(int MaxContent){
            Capacity = MaxContent;
            elem = new int[MaxContent];
            link = new int[MaxContent];
        }
        ~List(){
            delete[] elem;
            delete[] link;
        }
        int size();
        int first();
        int last();
        int remove();

        
};



template <class T>
class Queue{    //队列的cursorlist实现
    private:
        T elem[1000001];    //存放元素的数组
        Rank Next_link[1000001];    //下一个元素的位置
        Rank Prev_link[1000001];    //前一个元素的位置
        int _size = 0;
        Rank _data = -1,    //数据列表的起点
             _free = 0,     //空闲列表的起点
             _end = -1;     //数据列表的终点
    public:
        void init(int MaxContent){  //初始化为一个完整的空闲列表
            for(int i = 0; i < MaxContent; i++){
                Next_link[i] = i+1;
                Prev_link[i] = i-1;
            }
            Next_link[MaxContent - 1] = -1;
        }
        int size(){return _size;}
        bool empty(){return !_size;}
        void enqueue(T e){
            Rank k = _free;//找到空闲链表起点，准备存放元素
            if(empty()){
                _end = k;
            }
            _free = Next_link[k];   //空闲链表指向下一个位置
            elem[k] = e;            //存放元素
            Next_link[k] = _data;   //下一个元素位置改为当前数据链表起点
            Prev_link[_data] = k;   //当前数据链表起点的上一个点改为当前元素
            Prev_link[k] = -1;      //当前元素的前一个元素位置置为-1，表示没有上一个元素
            _data = k;              //现在插入的点就成为数据链表起点
            _size ++;               //统计大小的增加
            return;
        }
        T dequeue(){
            _size --;
            Rank k = _end;
            if(_data  == _end){
                _data = -1;
            }
            _end = Prev_link[k];
            Next_link[_end] = -1;
            return elem[k];
        }
        T pop(){
            _size--;
            Rank k = _data;
            _data = Next_link[k];
            Prev_link[_data] = -1;
            return elem[k];
        }
        T & roar(){
            return elem[_end];
        }
        T front(){
            return elem[_data];
        }
        void print(){
            Rank k = _data;
            while(k != -1){
                printf("%d ",elem[k]);
                k = Next_link[k];
            }
        }
};

