# ⑨的完美文本编辑器 解题报告
by 郑劭轩 材91 2019011852

## 算法构思

结合提示，本题对文本进行了大量的动态操作，因此适合用列表结构存储字符。因此本题算法的关键是正确实现列表结构，再为不同类型的操作提供接口。

列表结构可以令插入与删除的复杂度降至$O(1)$级别，光标的移动也可以容易地在$O(1)$时间内实现，但一般情况下列表的反转需要$O(n)$的时间。为此，结合提示，我在维护正向列表的同时维护一个方向恰好相反的镜像列表，通过修改连接结点的方式即可在$O(1)$时间内实现反转操作。

## 算法实现

### 列表基本结构
考虑到若用链表实现列表，频繁的动态空间分配会大幅拖慢程序的效率，因此我参考讲义以及实例代码，用游标方法实现了列表(cursor_list)。讲义与示例代码中的cursor_list为单向链表，不能满足本题的要求，因此我加入了存储上一个结点位置的数组，实现了双向访问。

### 镜像链表
为给反转操作提速，我同时维护了一个镜像链表。镜像链表内容与正向链表一致，方向与正向链表恰好相反。为保证镜像性，在操作正向链表时需要同时对镜像链表进行相同的操作。

### 功能接口的实现
#### 初始化

指向前后结点的数组必须经过初始化才可以实现定位，在初始化过程中可以预先将初始序列复制到列表里，同时生成镜像链表等。

##### elem[]数组的空间分配及初始序列
设初始序列的长度为size，elem[]数组前size位存放初始序列，接下来的size位存放镜像初始序列。之后4个位置分别存放正向、镜像链表的前、后哨兵结点。剩余的2N位空间分配给空闲链表，以应对后续的N次操作。因此elem长度至少需要为$2\text{size}+2N+4$。

初始序列可以直接复制到elem开头处，后面接着生成镜像序列。

##### link数组的初始化
link数组包括Left_link和Righ_link，管理结点的先后顺序。
所有结点的先后顺序初始状态下按照物理内存的顺序设定。

首先设定初始序列、镜像序列及其哨兵结点的link数组，先按照内存位置的顺序设定link数组的值，再在头尾连接上哨兵结点。

空闲链表仅需单向访问，因此只初始化Righ_link以节约时间。

##### 位置存储
初始化需要将哨兵结点的位置、空闲链表的起止点等信息存储下来。

#### 光标移动

##### 判断边界
由于正向链表和镜像链表成镜像关系，因此只需要检测正向链表的边界情况即可。由于正向链表的光标指向光标右侧的结点，光标到达左边界的标志为`Left_link[cursor] == header`，到达右边界的标志为`Righ_link[cursor] == trailer`。

##### 监测光标相对位置
由于光标相对位置的变化仅在移动光标的过程中发生，因此需要在移动光标时监测光标的相对位置情况，以在反转时判断是否满足条件。在执行移动操作前判断左右光标是否重合，若重合，即可根据光标的移动方向判断移动后两光标的相对位置，并将结果存下来。尽管该方法不能判断移动后两光标重合的情况，但光标重合可以在执行反转操作时快速判断，同样能获得准确结果。

#### 插入
插入发生在光标的左侧，正向链表的光标指向光标右侧的结点，因此插入后光标的位置不会发生变化，镜像链表同理。插入前需要预先在空闲链表起点处生成结点，再插入到链表结构中，维护链表中结点的先后顺序，空闲链表的起点位置也将会向后移动。


#### 删除

删除前需要判断光标是否位于右边界上，若`Righ_link[cursor] = trailer`则无法进行删除
删除时也只需要维护被删除结点两侧结点的先后顺序，同时维护空闲链表，将被删除的结点位置添加到空闲链表的尾部以释放空间。
由于正向链表光标指向光标右侧的结点，因此被删除的是光标指向的结点，光标位置将会移动到被删除结点右侧的结点上。


#### 反转
##### 判断是否可以反转
初始状态下，光标不可能是错位的，因此错位情况只有可能在移动光标后发生。发生错位前或恢复非错位状态前必然有两光标重合，因此在移动光标时加入的判断可以准确判断出光标错位的情形，即错位时有`unreversible = true`，非错位时有`unreversible = false`。

不可反转的情形只有错位和重叠两种情形，且重叠可以容易地通过比较光标位置是否相同得出，因此可以判断出是否可以执行反转操作。

##### 利用镜像链表实现反转
由于正向链表和镜像链表位于同一个一维数组上，因此可以直接通过更改link数组的方式，在$O(1)$时间内实现两个反转区间连接关系的改变，即：正向链表连接到镜像链表的反转区间，镜像链表连接到正向链表的反转区间。

由于两个链表互为镜像关系，正向链表反转区间被反转的同时，镜像链表中的对应区间也被反转，两个链表仍然能保持镜像关系不变，保证了算法的正确性。

#### 输出
从`Righ_link[header]`开始，循位置访问到`trailer`即可


## 复杂度分析

### 时间复杂度

本题中，列表的大部分接口时间复杂度都很明显为$O(1)$量级，以下仅分析初始化及输出的复杂度。
#### 初始化的时间复杂度
显然初始化的时间复杂度为$O(n)$级别，但程序运行中只执行一次初始化。
#### 输出的时间复杂度
输出的时间复杂度也为$O(n)$级别，且有可能多次执行输出。但好消息是，题目规定了输出文件的大小不超过20MB。按每个字符1字节计算，20MB相当于$2\times 10^7$个字符，因此最多只有$2\times 10^7$次单个字符输出操作。封底估算下，按每秒执行$10^9$次指令计，输出最多只耗费20 ms，属于可以接受的范围内。

#### 常数分析及时间复杂度封底估算
尽管大部分接口的时间复杂度为$O(1)$量级，但常数可能很高。通过直接计数的方法可以得知常数最大的$O(1)$接口为`del(char)`，常数约为25，若考虑输入处理，常数可能达到30左右。另外，初始化的常数约为16。

利用封底估算，按每秒执行$10^9$次指令计，初始文本长度$n \le 3200000$，指令数为$N \le 4000000$，总操作数
$$
16n+30\times4000000\le1.71\times 10^8
$$
折合时间171 ms，在限制范围内。

### 空间复杂度

最主要的空间开支在List的elem数组以及link数组，长度上限均为$2n+4+2N\le14400004$
elem数组为char类型，link数组为int类型，共计花费空间最多为$(1\text B+4\text B+4\text B)\times14400004 \approx 123.6\text{MB} < 256 \text {MB}$，满足限制。
## 遇到的问题及解决

### 列表实现方法的选择
动态分配空间过于耗时，因此我使用了游标实现的方法。
### reverse加速
原本采用的是逐个移动位置的方法来实现reverse操作，但耗时巨大。在阅读了习题课文件后理解了使用镜像链表辅助反转的方法，实现了$O(1)$时间的reverse。
### 删除及反转操作中光标位置的维护
由于我的实现中，正向链表的光标指向光标右侧的结点，因此在删除及反转操作的实现中有时会忘记维护光标的位置，导致光标位置错误。在仔细的检查后，我发现了这一错误，并在完成删除及反转操作后将光标置于正确的位置。
事实上，若将光标作为一个列表中的真正的结点，在插入、删除和反转操作中就可以避免光标位置的变化，代价是移动光标的常数增加。重构代码工作量较大，由于时间原因，我没有改用这种实现方式。

## 参考资料

讲义：列表的游标实现，P254~258
示例代码：cursor_list.h，但仅作为参考用于帮助理解cursor_list，没有照搬