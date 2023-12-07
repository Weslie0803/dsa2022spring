#pragma once

/**
 * 左子结点寻址
 * @param x 当前结点序号
 * @return 左子结点序号
*/
inline int lc(int x){
    return x * 2 + 1;
}

/**
 * 右子结点寻址
 * @param x 当前结点序号
 * @return 右子结点序号
*/
inline int rc(int x){
    return x * 2 + 2;
}

//线段树结点类
class SegNode{
    public:
    long long v = 0;
    int l = 0,r = 0;//左开右闭区间
    long long lazy = 0;//懒惰标记
};

//线段树类
class SegmentTree{
    private:
        SegNode * seg;
        int _n_Inteval, //离散区间数目（叶节点数目） 
            _capacity;  //总结点数目
        void pass_lazy(int _node);
    public:
        SegmentTree(){};
        ~SegmentTree(){ delete[] seg;}
        void initialize(int b[], int len);
        void InsertSegment(int node, int l, int r);
        long long Query(int node, int l, int r);
};