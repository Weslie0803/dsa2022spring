# filename解题报告
by 郑劭轩 材91 2019011852
## 设计动态规划算法
结合提示，我们很自然想到应用动态规划的算法来解题。

对将长度为n的字符串`str1`修改为长度为m的字符串`str2`的规模为(n,m)的问题(记作`str1 -> str2`)，应用减治思想，我们希望能够将其化为规模为(n-1,m-1)的子问题, 即: 将长度为(n-1)的字符串`substr1`修改为长度为(m-1)的字符串`substr2`的问题(记作`substr1 -> substr2`)。

### 符号约定
- `str1 -> str2`: 将长度为n的字符串`str1`修改为长度为m的字符串
- `substr1 -> substr2`: 将长度为(n-1)的字符串`substr1`修改为长度为(m-1)的字符串`substr2`
- $C(n,m)$: `str1 -> str2`的最小修改代价
- $C(n-1,m-1)$: `substr1 -> substr2`的最小修改代价

### 状态转移方程的推导
考察`str1`与`str2`的尾部元素（为方便讨论，以下分别记作`t1`与`t2`）:
- 若`t1` = `t2`, 则显然可知`str1 -> str2`的最小修改代价与`substr1 -> substr2`相同, 即$C(n,m) = C(n-1,m-1)$:
    - 显然存在修改方法: 在`str1`中使用`substr1 -> substr2`的最小修改代价方法, 即可实现`str1 -> str2`. 因此$C(n,m) \le C(n-1,m-1)$
    - 当`str1 -> str2`的修改方法不涉及有关尾部元素的操作(即删除尾部元素`t1`)时, `str1 -> str2`的方法显然可以直接应用在`substr1 -> substr2`上, 因此有$C(n,m) \ge C(n-1,m-1)$, 综上$C(n,m) = C(n-1,m-1)$
    - 当涉及删除尾部元素操作时, 删去`str1`尾部的`t1`, `str1 -> str2`问题变为`substr1 -> str2`问题. 
        - 若此时`substr1`与`str2`的尾部元素不同, 则势必需要在`substr1`的尾部加上`t1`. 此时问题又变为`str1 -> str2`, 但多了2步额外的开支, 因此这种方法一定不是最小修改代价方法.
        - 若此时`substr1`与`str2`尾部元素相同, 这意味着`substr1`尾部元素同样为`t1`, `str1`的末端是连续的2个`t1`. 因此删除尾部`t1`的操作与删除倒数第二个`t1`的操作等效, 可以用后者代替前者, 从而等效实现`str1 -> str2`而不必涉及有关尾部元素的操作.
        
        综上: 涉及删除尾部操作的修改方法一定与某一种不涉及删除尾部操作的修改方法具有同样的修改代价. 
    - 因此只需要考虑不涉及删除尾部操作的修改方法, 从而有$C(n,m) = C(n-1.m-1)$ 

- 若`t1` != `t2`
    - 此时由于`str1`与`str2`的末尾元素不同，因此**最小代价修改过程**中必定包含以下两种操作之一
        - 删除`t1`
        - 在`str1`末尾添加`t2`
    - 这两种操作都需要花费1个修改代价，且不可避免需要执行一次
    - 考虑在`str1`末尾添加`t2`的情形：记添加`t2`后的`str1`为`str1t2`
        - 此时，`str1t2`与`str2`末尾元素相同. 由上一部分结论可知`str1t2 -> str2`的最小修改代价(记作$C(n+1,m)$)与`str1 -> substr2`的最小修改代价相同(记作$C(n,m-1)$), 即有$C(n+1,m) = C(n,m-1)$
        - 由于之前经历了添加`t2`的操作, 故$C(n,m) = C(n+1,m) + 1$, 即$$C(n,m) = C(n,m - 1) + 1$$
    - 考虑删除`t1`的情形: 
        - 该情形下, 显然有$$C(n,m) = C(n-1,m) + 1$$
    - 综合两种情况考量, 应当有:
    $$
        C(n,m) = \min(C(n-1,m), C(n,m-1)) + 1
    $$

综合两种情形得到**状态转移方程:**
$$
    C(n,m) = \begin{cases}
                C(n-1,m-1) &\text{if } t1 = t2\\
                \min(C(n-1,m), C(n,m-1)) + 1 &\text{if } t1\neq t2
            \end{cases}
$$

### 动态规划算法的实现v1.0
获得状态转移方程后, 我们可以容易地实现动态规划的算法:
```
//声明变量
//处理输入
//先填充边界值，按0~N, 0~M的顺序计算填充C(n,m)的值, 并记录在数组st[n][m]中
//读取st[N][M]的值
//若大于k, 则输出-1; 否则输出st[N][M]的值
//结束
```

### 复杂度分析与评价
#### 时间复杂度
本算法最耗时的步骤在于填充二维数组`st[n][m]`. 数组行数为N+1, 列数为M+1, 易知这一步的时间复杂度为$O((N+1)(M+1)) = O(NM)$

进行封底估算, 设处理器每秒的计算次数为$10^9$, $N\times M \le 2.51\times10^{11}$
可见该算法的运行时间将超过1s, 超过了题目要求.
#### 空间复杂度
同样, 主要的空间占用在于数组`st[n][m]`的创建, 空间复杂度同样为$O(NM)$级别.

进行封底估算, `st[n][m]`为`int`类型, 因此占用存储空间为$4\times N \times M \le 1\times 10^{12}\rm B \approx 1 \rm{TB}$
远大于题目所限制的256MB.

综上所述, 算法仍然需要进行进一步的优化. 


## 算法的优化

### 思路: 利用K的小规模条件
观察题目要求可以发现, K的数据规模远小于N与M. 因此, 我们希望能够利用这一点削减时间与空间的开支.
### 新条件: $C(n,m) \ge C(n-1,m-1)$
证明: 用反证法
- 假设$C(n,m) < C(n-1,m-1)$
    - 显然存在`str1 -> substr1 -> substr2 -> str2`的修改方法, 因此$C(n,m) \ge C(n-1,m-1) + 2$
        - 因此$C(n,m)$只能为$C(n-1,m-1) - 1$或$C(n-1,m-1)-2$

    - $C(n,m) = C(n-1,m-1) - 1$情形:
        - 这种情形不可能存在. 每次修改都会增加或删除元素, 对`str1 -> str2`应有$$
            n - 总删除次数 + 总增加次数 = m\\
            n - m = 总删除次数 - 总增加次数\\
            (n-m)\equiv(总删除次数 - 总增加次数)\pmod 2\\
            (n-m)\equiv(总删除次数 + 总增加次数)\pmod 2\\
            (n-m)\equiv C(n,m)\pmod 2\\
        $$
        同理对`substr1 -> substr2`有
        $$
            ((n-1) - (m-1)) = (n-m) \equiv C(n-1,m-1)\pmod2
        $$
        因此$C(n,m)\equiv C(n-1,m-1)\pmod 2$, 
        与$C(n,m) = C(n-1,m-1) - 1$矛盾. 
    - $C(n,m) = C(n-1,m-1) - 2$情形: 
        - 这种情形一定有`t1`!=`t2` (`t1`=`t2`则一定有$C(n,m) = C(n-1,m-1)$)，从而根据先前的分析，必定有修改尾部元素的操作（删除`t1`或添加`t2`）
        - 若有最小代价修改方法中有添加`t2`的操作
            - 根据上文有$C(n,m) = C(n,m-1)+1$，从而有$C(n,m-1) = C(n-1,m-1) - 3$
            - 显然存在修改方法`substr1 -> str1 -> substr2`使得$C(n-1,m-1) \le C(n,m-1) + 1$
            - 综合以上两式有$C(n-1,m-1) \le C(n-1,m-1) - 2$, **矛盾**

        - 若最小代价修改方法中有删除`t1`的操作
            - 根据上文有$C(n,m) = C(n-1,m)+1$，从而有$C(n-1,m) = C(n-1,m-1) - 3$
            - 显然存在修改方法`substr1 -> str2 -> substr2`使得$C(n-1,m-1) \le C(n-1,m) + 1$
            - 综合以上两式有$C(n-1,m-1) \le C(n-1,m-1) - 2$, **矛盾**
        - 以上两种情形均推出矛盾
    - 综上：假设错误，$C(n,m) \ge C(n-1,m-1)$得证。

### 新条件对优化算法的意义

为形象化描述，我们将二维数组`st[n][m]`的第一个分量描述为“行数”，第二个分量描述为“列数”，如下表所示：
0          |       1    |   2 
-----------|------------|-----------
`st[0][0]` | `st[0][1]` | `st[0][2]`
`st[1][0]` | `st[1][1]` | `st[1][2]`
`st[2][0]` | `st[2][1]` | `st[2][2]`
 

之前遍历`st[n][m]`数组时采用了先填充边界值、再填充内部元素的策略。这些边界值的共同特点为：它们的左上方没有元素。当边界值大于K时，位于这些边界值右下方的元素一定大于K。因此，
- 若`st[N][M]`位于这些边界值的右下方，可以直接判定`st[N][M]`>K, 不必继续遍历
    - 位于上边界（`st[0][j]`）右下方的数组单元`st[n][m]`满足$m-n=j$，边界值`st[0][j]`$=j$，
    因此当$M-N>K$时可以直接判定`st[N][M]`>K，退出循环，直接输出-1
    - 位于左边界（`st[i][0]`）右下方的数组单元`st[n][m]`满足$n-m=i$，边界值`st[i][0]`$=i$，
    因此当$N-M>K$时可以直接判定`st[N][M]`>K，退出循环，直接输出-1
    - 综上，当$M-N>K$或$N-M>K$时可以不必填充`st[n][m]`二维数组，直接输出-1，从而只需要考虑$|N-M|\le K$的情形。

- 经过过滤后，只剩下$|N-M|\le K$的情形。我们不再关注$|n-m|>K$的子问题，只需要知道这些子问题一定有`st[n][m]`>K。因此我们只需要求解$|n-m|\le K$的子问题。同时，我们可以重新组织二维数组的结构，从而节省存储空间。
- 另外，若在遍历过程中发现`st[N][M]`左上方的数组单元（满足$n-m = N - M$的数组单元）值`st[n][m]`>K，也可以直接推定`st[N][M]`>K

### 重新组织数组空间
对$|n-m|\le K$情形，其数组元素在原本的`st[n][m]`二维数组中基本沿对角排列。$n-m$共有$2K+1$种可能取值，每个值最多对应$\min(N+1,M+1)$个数组单元。因此可以将原本$N\times M$规模的数组缩小到$(2K+1)\times \min(N+1,M+1)$规模，从而有望将空间复杂度从$O(NM)$优化到$O(KN)$量级。

与原数组区分，在以下内容中新数组记作`_st[r][i]`，其中$r$分量与$n-m$值对应，$i$分量从0开始在原数组中从左上到右下递增。由于数组的下标不能为负数，考虑到数据范围中$K\le100$，有$n-m\le100$，因此定义：
- 当$n-m\ge0$时：$r = n-m$
- 当$n-m<0$时：$r=m-n+100$

从而实现了$r$与$n-m$的一一对应。

原本的状态转移方程建立在`st[n][m]`二维数组的基础上，在应用到新数组结构时，为方便实现，需要进行坐标变换。记原数组的两个坐标分量为$x,y$，新数组的两个坐标分量为$r,i$，在代码中通过下列4个函数实现了新旧坐标的互相转换：
```cpp
int x_calc(int r, int i);
int y_calc(int r, int i);
int r_calc(int x, int y);
int i_calc(int x, int y);
```
### 对边界的处理

调整数组后，对$|n-m|=K$的边界情形会出现左侧或上侧之一没有元素的情况。根据先前的分析，这些空缺的元素在之前的算法中会被填充大于K的值。若待填充单元`st[n][m]`的值与空缺元素不相关，则不需要考虑空缺元素的值；若待填充单元与空缺元素相关，那么`st[n][m]`一定大于K。此时我们不需要知道它的具体数值，我们只需要知道这是一个大于K的数，将其置为K+1即可。这种处理不会影响最终结果。

对数组单元`_st[r][i]`的填充在代码中被封装为函数`void renew_ri(int r, int i)`。


### 遍历顺序与跳出

根据状态函数的依赖关系，容易想到在原数组结构中从左上向右下填充。反映到新数组中就是沿下标$i$从小到大遍历填充。

先前的分析已经指出，在填充的过程中如果发现`_st[N-M][i]`的值超过了K，这意味着`st[N][M]`一定超过K，此时可以停止填充跳出循环。

否则，数组填充满后停止，检查`st[N][M]`的值。

### 进一步优化细节

在这次优化后，我们注意到数组存储的值不会超过K+1。鉴于数据规模中$K\le100$，数组存储的值不会超过101，因此仅需要一个字节的`char`类型即可保证算法顺利运行而不必使用4个字节的`int`。这一步可以将空间复杂度压缩为原来的1/4.


### 复杂度分析与评价
#### 时间复杂度
优化后的算法最多只需要填充$(2K+1)\times N$大小的数组，且在大多数情况下不必完全填满。时间复杂度为$O(KN)$量级。

作封底估算：设处理器每秒的计算次数为$10^9$, $K\times N \le 5.01\times10^{7}$。基本可以在1s内完成。

#### 空间复杂度
空间复杂度为$O(KN)$级别。

在代码实现中，开辟最大的数组为`char st[201][501001]`，所占用的内存空间约为$1\times10^8\rm{B}\approx 100\rm{MB} < 256\rm{MB}$，满足题目的限制条件。

## 在完成过程中遇到的问题
### 旧算法状态转移方程的发现
尽管动态规划算法的方向很明确，但我在确定状态转移方程的过程中仍然遇到了一些困难。在这过程中，我意识到了这一问题与讲义中提到的最大公共子串问题有一定的联系。删除冗余元素时`str1`变为二者的最大公共子串，再补上元素得到`str2`，这一过程的修改代价一定与最小修改代价相等。记最大公共子串的长度为$G(n,m)$，有$C(n,m) = (n-G(n,m))+(m-G(n,m))=n+m-2G(n,m)$。因此由讲义中的状态转移方程就可以得到本问题的状态转移方程。
### 寻找优化方案
旧算法在时间和空间上均无法达到题目的要求，因此我必须找到一个优化方案。在经历了一整个下午的摸索后，我发现从任意一个数组单元出发，向右下角延展得到的序列一定是非下降的。证明了这个发现后，我将其应用到算法中，终于压缩了时间与空间的复杂度。
### 具体实现过程中遇到的问题
#### 边界值处理
边界数组单元的上侧/左侧之一是缺失的，这就意味着不能直接应用状态转移方程计算。结合旧算法的实现过程，我意识到边界值外侧的缺失单元代表大于K的值，也就意味着不会对边界值产生影响（若能够产生影响，说明另一侧的值也大于K，同样会引起边界值大于K）。
#### n<m时r的取值
在选用$r=m-n+100$的方案之前，我曾在它与方案$r=m-n+K$之间徘徊。最后，我认为，尽管后一种方案使得数组中数据排列更紧凑，但对空间优化的意义不大，反而在算法实现过程中会增加出bug的可能性，同时也存在因为调用变量而一定程度上使算法变慢的风险。因此我选择了前一种方案。
#### 跳出问题
跳出问题包括2个问题：一是填充完所有有意义的r下标单元后跳出到下一个i下标的问题，二是提前终止填充过程的问题。

##### 跳到下一个i
在调试时偶尔发现输出`st[n][m]`异常等于0的情况，经查是判断i下标下r下标填充完成的条件出错。这次数组的长度为N+1，但我在设置边界判断条件时习惯性地认为长度是N，从而导致最后一行没有完全填充。修改后问题解决。
##### 判断提前终止
最终版本的代码中，在填充每一个i下标的所有单元后，判断`_st[r_calc(N,M)][i]`与K的关系，大于K则终止。但在发现这个规律之前，我采用的是判断i下标所有单元中的最小值与K的关系的方法，同样是大于K则终止。寻找最小值的算法比直接获取`_st[r_calc(N,M)][i]`要复杂，这部分算法也出现了不少bug，如没有更新数组单元导致最小值没有更新，异常判断了提前终止等。寻找最小值的算法计算次数较多，耗时相对更长，且不够精准，因此在发现`_st[r_calc(N,M)][i]`判据后被果断替代。

#### 优化存储类型
`_st[r][i]`数组最开始使用的是`int`类型。在计算空间开支时，我发现数组仍然需要占用约400MB内存空间，超过了题目限制。经过分析后，我发现对大于K的数组单元值，我们只需要知道它大于K即可，而其具体数值不影响结果。因此，我将大于K的值统一设为K+1，从而可以只使用1字节的`char`类型记录数据，将空间开支压缩为原来的1/4

## 参考资料
讲义：《动态规划：最大公共子序列》部分，P80~90