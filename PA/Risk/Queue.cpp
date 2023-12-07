typedef int Rank;
class Queue{
    private:
        int * elem;
        Rank * Next_link;
        Rank * Prev_link;
        int Capacity;
        int _size = 0;
        Rank _data = -1, _free = 0, _end = -1;
    public:
        Queue(int MaxContent){
            Capacity = MaxContent;
            elem = new int[MaxContent];
            Next_link = new int[MaxContent];
            Prev_link = new int[MaxContent];
            for(int i = 0; i < MaxContent; i++){
                Next_link[i] = i+1;
                Prev_link[i] = i-1;
            }
            Next_link[MaxContent - 1] = -1;
        }
        ~Queue(){
            delete[] elem;
            delete[] Next_link;
        }
        int size(){return _size;}
        bool empty(){return !_size;}
        void enqueue(int e){
            Rank k = _free;//找到空闲链表起点，准备存放元素
            if(empty){
                _end = k;
            }
            _free = Next_link[k];//空闲链表指向下一个位置
            elem[k] = e;//存放元素
            Next_link[k] = _data;//下一个元素位置改为当前数据链表起点
            Prev_link[_data] = k;//当前数据链表起点的上一个点改为当前元素
            Prev_link[k] = -1;
            _data = k;//现在插入的点就成为数据链表起点（头）
            _size ++;//统计大小增加
            return;
        }
        int dequeue(){
            Rank k = _end;
            if(_data  == _end){
                _data = -1;
            }
            _end = Prev_link[k];
            Next_link[_end] = -1;
            return elem[k];
        }
};