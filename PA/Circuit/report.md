# 解题报告：Circuit
by 郑劭轩 材91 2019011852

## 算法构思
本题要求在$\pm k+1$范围内找到与本二进制串异或值最大的二进制串。

考虑蛮力算法，可以在这一范围内遍历所有的数，直至找到异或值最大的串。尽管在将二进制串转化为对应的整数后可以在$O(1)$时间内快速计算出任意两个串的异或值，但遍历将会使得每个数都要与范围内的所有数计算异或值，总计算次数预计将达到$O(nk)$量级。由于k与n的规模相当，这一计算次数是十分巨大的，还有很大的优化空间。

结合提示，二进制串对应着一个结点在二叉树中的路径，因此可以将二进制串用一个二叉树中的叶结点表示。利用异或运算的性质，要在二叉树中寻找与给定二进制串异或值最大的结点，只需要尽量选取与给定二进制串相反的路径即可。这一过程需要的计算次数与路径长度相当，为常数级别。

该算法需要动态地对二叉树进行插入/删除的维护操作。预先将最后的k+2个二进制串插入到空二叉树中，然后从后向前查找每个元器件的最大异或串。根据当前元器件的编号位置对二叉树进行插入/删除，保证二叉树中的叶节点在搜索范围内。

算法流程(伪代码)：
```
读取输入数据
建立树：预先读取后k+2个（不超过n个）元器件数据，插入到空树中
自后向前遍历：
    在树中搜索对应二进制串的最大异或二进制串，将结果存下来
    若前方还有可以添加的元器件数据，插入到树中
    若搜索范围末尾的数据即将离开搜索范围，从树中删除末尾数据对应的结点
输出结果
```


## 算法实现

### 结点类与结点存储空间管理
为方便管理结点空间，在实现了结点类`Node`后，我继承`Node`类实现了`ListNode`子类，并实现了`NodeList`空间管理类。所有结点均存放在`NodeList`的`ListNode`数组中，并以数组下标作为标识。

#### `Node`结点类
为节省空间，`Node`类中只有三个成员变量：
- `Node::lc`左子结点
- `Node::rc`右子节点
- `Node::parent`父节点
对叶节点而言，由于叶节点没有子节点，且算法需要在叶节点处存储元器件编号，因此`Node::lc`也用来存放叶节点的编号数据。

#### `ListNode`子类
相比`Node`类新增了成员变量`ListNode::link`用于记录下一个结点在`NodeList`中的位置。

#### `NodeList`结点管理类
维护一个`ListNode`数组，并向外提供内存管理的接口，包括：
- `NodeList::new_node()`：返回一个空结点的下标
- `NodeList::del_node(Rank r)`：回收下标对应的结点
- `NodeList::pointer(Rank r)`：返回下标对应结点的指针

### 二叉树
二叉树类`Tree`中存放一个`NodeList`对象及根节点的数组下标，并向外提供结点插入/删除、寻找最大异或结点的接口。
#### 结点插入`Tree::insert`
根据二进制串给定的路径从根节点向下走，若发现对应子节点未被创建则调用`NodeList::new_node()`创建新结点，并接入到二叉树中。
到达根节点后，将元器件编号存放在叶节点的`Node::lc`成员变量中。

#### 结点删除`Tree::del`
根据给定的路径找到叶节点（这一过程封装在`Tree::find()`中）。若叶节点存放的编号与计划删除的不符，说明该元器件对应的结点已被覆盖，不必再删除。否则，从叶节点向上逐个用`NodeList::del_node()`回收结点，直到与其它叶节点的路径交叉为止。

#### 最大异或结点查找`Tree::search`
尽量沿给定结点路径相反的方向走，若相反方向没有子节点则还是跟着路径走，直至走到叶节点。返回叶节点存储的编号值。由于先前的遍历插入是从后向前进行的，若出现重复结点，编号靠前者将会自动覆盖编号靠后者，因此可以保证返回的编号值是相同结点中编号靠前的。

此处还需要考虑到题目中“元件不能和自己组合”的约束：
- 以上算法可以保证编号对应的二进制串与给定二进制串异或值最大，而容易得知，两个相同二进制串的异或值为0。
- 因此可以得出此时搜索范围内的所有元器件的二进制串相同的结论。-
- 根据上一段关于重复结点的讨论，此时函数将会返回搜索范围中序号最靠前的结点编号。
- 若返回的结点编号与当前结点编号相同，即当前结点编号为搜索范围中最靠前的结点编号，则当前结点编号一定为0。因此，范围内除当前结点外，最靠前结点的编号为1。此时可直接返回1。

## 复杂度分析
### 空间复杂度
#### 结点的存储空间
结点将会组成一棵高度为64的树，树的叶节点数最多时为2k+3（不超过n）。
考虑最坏情形：存在大量单链导致结点数巨大，如以下所述情形：
- 先构成有n个叶节点的完全二叉树。该部分总结点数不超过2n。
- 每个叶节点延伸出单链，使延伸后所有新的叶节点深度均为64。
    - 先前完全二叉树的高度为$\log n$
    - 因此单链的长度不超过$64-\log n + 1 = 65-\log n$
    - 单链部分总结点数不超过$65n-n\log n$

因此总结点数$N$最多不超过$67n-n\log n$

由于题目给出$n\le500000$，因此有$N\le67n-n\log n\le24034216$。

每个结点占据16字节的空间，总空间占用不超过$16\rm B\times24034216\approx367\text{MB}$

#### 存储输入输出数据
输入数据用500000*65的二维字符数组存储，复杂度为$O(n)$级别，常数为65，总空间占用不超过31MB
输出数据用长度为500000的一维`int`数组存储，空间复杂度为$O(n)$级别，总空间占用不超过4MB

此外没有大的空间开支。由于$\log n$相比n较小，因此总体空间复杂度为$O(n)$级别，但常数较大，总占用空间约为400MB，在题目限制的512MB以内。

### 时间复杂度
#### 初始化NodeList
初始化NodeList需要花费固定的时间遍历MAX_NODE_NUM长度的数组，计算次数与MAX_NODE_NUM相当。

#### 插入、删除、查找接口的复杂度
每次插入均需要向下行走64步，复杂度为常数

每次删除时，找到叶节点需要64步，完成删除至多需要64步，复杂度也为常数

同样，查找最大异或值结点时也需要向下执行64步，也为常数复杂度。

每个元器件在算法执行过程中至多被插入、删除、查找1次，因此花在插入、删除、查找上的时间开销为$O(n)$级别。

#### 输入与输出
显然均为$O(n)$级别。

#### 封底估算
根据空间复杂度方面的计算，MAX_NODE_NUM取25000000可以保证算法在题目所给数据规模下正常运行。按每秒执行$10^9$次运算计，需要
$$
25000000\times 3 \div 10^9 = 75 \rm{ms}
$$
(3考虑了for循环中比较与自增的运算)

主算法方面，时间复杂度为$O(n)$级别。按每秒执行$10^9$次运算计，需要0.5 ms即可，在很大的常数下（不超过约3800）能够满足题目要求的时间限制(2s)。

## 遇到的问题及解决
### 遍历方向
原本计划按照正常从前向后的顺序遍历元器件，但在实现过程中发现这会使得在有重复二进制串时保留靠前编号变得困难。结合提示以及对算法的分析，我发现若将遍历顺序改为从后向前，每次插入后，靠前的编号会自动覆盖重复结点上原本记录的编号，而不必再维护历史信息，使得树的维护变得方便。

### 空间压缩
原本的结点使用指针访问子节点和父节点，且单独划出了空间用于存储编号信息。但在实现过程中，我发现，在64位系统中，指针的大小为8字节，是int类型的2倍，这在结点数巨大的情况下对内存是巨大的浪费，而且会使得内存使用超出限制。此外，由于只有叶节点需要存储编号信息，这一空间在内部结点中均被浪费了。因此在改进的过程中，我修改了NodeList的接口，用数组下标定位结点在存储中的位置；同时利用叶节点没有子节点的特性，将编号信息存储在叶节点存储左子节点的位置上，很大程度上节省了空间。

此外，提示给出可以通过压缩结点的方式减少空间的使用。结合以上部分的分析，当前的算法已经可以实现题目的要求，受限于时间，此处就不再实现压缩结点的算法。

## 参考资料
讲义：P254 列表的游标实现（结点管理方面对此有部分参考）
讲义：P450 完全二叉树（叶节点与内部结点的数量关系）