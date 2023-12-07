#include "Segment.h"

/**
 * 线段树初始化
 * @param b 存放区间信息的数组
 * @param len 区间数目（叶节点数目）
*/
void SegmentTree::initialize(int b[], int len){
    _n_Inteval = len;
    _capacity = len * 2 - 1;//计算表明总结点数为叶节点数的2倍减1
    seg = new SegNode[_capacity];
    //确定叶节点位置
    int depth = 0;
    for(int i = 1; ; i++){
        if(((_n_Inteval-1) >> i) == 0){
            depth = i;//depth取_n_Inteval-1的位数。最低的叶节点将位于树的第depth层（根节点为第0层）
            break;
        }
    }
    //填充最底层叶节点
    for(int i = 0; i < _capacity - (1<<depth) + 1; i++){
        seg[(1<<depth) - 1 + i].l = b[i];
        seg[(1<<depth) - 1 + i].r = b[i+1];
    }
    //填充次底层叶节点
    for(int i = _capacity - (1<<depth) + 1; i < _n_Inteval; i++){
        seg[(1<<depth) - 1 - _n_Inteval + i].l = b[i];
        seg[(1<<depth) - 1 - _n_Inteval + i].r = b[i+1];
    }
    //根据叶节点向上填充其它节点
    for(int i = _n_Inteval - 2; i >= 0; i--){
        seg[i].l = seg[lc(i)].l;
        seg[i].r = seg[rc(i)].r;
    }
}
/**
 * 将懒惰标记向下传递(如果当前结点有懒惰标记的话)
 * 没有标记就不做操作
 * @param _node 当前结点
*/
void SegmentTree::pass_lazy(int _node){
    if(seg[_node].lazy > 0){
        seg[lc(_node)].v += (seg[lc(_node)].r - seg[lc(_node)].l) * seg[_node].lazy;
        seg[lc(_node)].lazy += seg[_node].lazy;
        
        seg[rc(_node)].v += (seg[rc(_node)].r - seg[rc(_node)].l) * seg[_node].lazy;
        seg[rc(_node)].lazy += seg[_node].lazy;
        
        seg[_node].lazy = 0; 
    }
}

/**
 * @param node 结点的序号
 * @param l 待插入区间的左端点
 * @param r 待插入区间的右端点
*/
void SegmentTree::InsertSegment(int node, int l, int r){
    //若当前结点表示的区间被待插入区间包含
    //当前区间数值更新，并更新懒惰标记，直接返回
    if(l <= seg[node].l && r >= seg[node].r){
        seg[node].v += (seg[node].r - seg[node].l);
        seg[node].lazy += 1;
        return;
    }
    //若待插入区间与左子结点表示的区间有交集
    //（需要访问子区间）传递懒惰标记
    //转入左子区间操作
    //更新当前结点的数值
    if(l < seg[lc(node)].r && r > seg[lc(node)].l){
        pass_lazy(node);
        InsertSegment(lc(node), l, r);
        seg[node].v = seg[lc(node)].v + seg[rc(node)].v;
    }
    //若待插入区间与右子结点表示的区间有交集
    //与左子结点类似
    if(l < seg[rc(node)].r && r > seg[rc(node)].l){
        pass_lazy(node);
        InsertSegment(rc(node), l, r);
        seg[node].v = seg[lc(node)].v + seg[rc(node)].v;
    }
}

/**
 * @param node 结点的序号
 * @param l 待查询区间的左端点
 * @param r 待查询区间的右端点
*/
long long SegmentTree::Query(int node, int l, int r){
    long long result = 0;
    //若待查询区间包含当前区间
    //直接取用当前区间值并返回
    if(l <= seg[node].l && r >= seg[node].r){
        result += seg[node].v;
        return result;
    }
    //若待查询区间和左子结点区间有交集
    //（需要访问子区间）传递懒惰标记
    //返回左子结点区间查询情况并累加
    if(l < seg[lc(node)].r && r > seg[lc(node)].l){
        pass_lazy(node);
        result += Query(lc(node), l, r);
    }
    //右子结点区间: 与左子结点区间类似
    if(l < seg[rc(node)].r && r > seg[rc(node)].l){
        pass_lazy(node);
        result += Query(rc(node), l, r);
    }
    return result;
}