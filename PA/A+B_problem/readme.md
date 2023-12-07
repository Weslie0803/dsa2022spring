# 解题报告

郑劭轩 材91 2019011852

## `LongInt`类

为方便代码的实现和后续的调试，我封装了`LongInt`类。类中的变量包括

```cpp
int a[2580];//每个单元存储4位10进制数，如123321在数组中为[3321, 12]
bool sign = true; // 存储长整型数的符号，非负数为true，负数为false
int length; //存储数组的长度，方便后续调用。
```

函数包括

```cpp
void self_check(); //运算后的自我检测，负责保证数组每一个单元的值在[0,9999]范围内
void de_zero(); //同样是运算后的自我检测，去除首位的0以保证位数length的准确
void push_back();
int pop_back(); //为方便实现self_check与de_zero而实现了这两个函数，控制数组尾部数据的增加与删除，与vector的push_back、pop_back功能基本一致。

LongInt(); //默认构造函数
LongInt(int); //由整型数构造长整型
LongInt(char str[], int len); //由字符串构造长整型

LongInt operator+(const LongInt &)const;//实现长整型的加法
LongInt operator-(const LongInt &)const;//实现长整型的减法
LongInt operator*(const LongInt &)const;//实现乘法
bool operator>(const LongInt &)const;//实现>运算

friend std::ostream & operator<<(std::ostream &, const LongInt &);
```

## 自我检测self_check()与de_zero()

为保证长整型数在运算中不出错，我设计了自我检测函数自动实现运算中的进位与退位，以使得每个数组单元的值维持在`[0,9999]`区间内。

### self_check()函数

#### 实现

该函数主要负责实现进位与退位。自低位开始向高位扫描，若某数组单元`a[i]>=10000`，则将变量`tmp`置为`a[i]/10000`，`a[i]`置为`a[i]%10000`；若`a[i]<0`，则`tmp`置为-1，`a[i]`置为`a[i]+10000`。`tmp`自动加入下一位数组单元中，若需要增加位数则自动增加。代码实现如下：

```cpp
void LongInt::self_check(){
    int length = this->length;
    int tmp = 0;
    for(int i = 0; i < length; i++){
        this->a[i] += tmp;
        if(this->a[i] >= 10000){
            tmp = this->a[i]/10000;
            this->a[i] %= 10000; 
        }
        else if(this->a[i] < 0){
            tmp = -1;
            this->a[i] += 10000;
        }
        else{
            tmp = 0;
        }
    }
    while(tmp != 0){
        this->push_back(tmp%10000);
        tmp /= 10000;
    }
}
```



#### 复杂度分析





## 加法与减法的实现

由于乘法计划使用讲义P65的算法，因此在实现乘法前需要先实现加法与减法

### 加法

加法采用的实现方式是对位相加，然后使用`self_check()`函数完成进位的操作，保证数组格式的准确性。为应对正负问题，在实现代码前对两加数的正负性作了判断，双方异号转入减法，均为负数则预先将和置为负数，再进行加和。代码实现如下所示：

```cpp
LongInt LongInt::operator+(const LongInt & _LI)const{
    LongInt sum;
    if(this->sign == false && _LI.sign == false){
        sum.sign = false;
    }
    else if(this->sign == true && _LI.sign == false){
        LongInt tmp = _LI;
        tmp.sign = true;
        sum = *this - tmp;
        return sum;
    }
    else if(this->sign == false && _LI.sign == true){
        sum = *this;
        sum.sign = true;
        return _LI - sum;
    }
    if(this->length > _LI.length){
        sum = *this;
        for(int i = 0; i < _LI.length; i++){
            sum.a[i] += _LI.a[i];
        }
    }
    else {
        sum = _LI;
        for(int i = 0; i < this->length; i++){
            sum.a[i] += this->a[i];
        }
    }
    sum.self_check();
    return sum;
}
```



#### 正确性分析

分别记两个长整型数为$a$和$b$，数组各单元用$a_i$、$b_i$表示，数组长度分别为$l_a$、$l_b$，则有：
$$
a=\sum_{i=0}^{l_a - 1}a_i\times 10000^i\\
b=\sum_{i=0}^{l_b - 1}b_i\times 10000^i
$$
不妨设$l_a \ge l_b$，上下两式相加显然有
$$
a+b=\sum_{i=0}^{l_b-1}(a_i+b_i)\times 10000^i + \sum_{i = l_b}^{l_a-1}a_i \times10000^i
$$
即为对位相加结果。故对位相加可以保证正确性。



对`self_check()`函数：考虑每一次进位操作。
$$
a[i] \rightarrow a[i]\%10000: a减少了a[i]/10000\\
a[i+1] \rightarrow a[i+1]+a[i]/10000: a增加了a[i]/10000
$$
减少和增加的数量相同，因此每次进位操作可以保证a数值不变。

另外，由于对位相加前各单元的值均小于10000，因此对位相加后的值不会大于20000，远小于int型变量的上限，不会发生溢出的问题。

综上所述，加法的正确性可以保证。

#### 复杂度分析

对位相加部分：运算的次数取决于最短加数的长度，复杂度应为$O(n)$

`self_check()`部分：运算次数取决于最长加数的长度。若最高位无进位，复杂度应为$O(n)$；若最高位有进位，由于在对位相加前最高位的值小于10000，因此对位相加后最高位至多进位1次，故复杂度应为$O(n+1)$。综上，`self_check()`部分的复杂度应为$O(n)$

故加法的复杂度为$O(n)$



### 减法

减法同样使用对位相减的方法实现，对位相减的结果可以是负数。负数引起的退位问题由`self_check()`函数与`de_zero()`函数处理。由于在后续的乘法算法中可以保证参与减法运算的两个数一定是非负数，因此省去了对减数与被减数符号的判断步骤。但为了处理结果的正负号问题，仍然需要在计算前判断被减数与减数的相对大小，以确定结果的符号。代码实现如下：

```cpp
LongInt LongInt::operator-(const LongInt & _LI)const{
    LongInt result;
    if(_LI > *this){
        result = _LI - *this;
        result.sign = false;
    }
    else{
        result = *this;
        for(int i = 0; i < _LI.length; i++){
            result.a[i] -= _LI.a[i];
        }
        result.self_check();
        result.de_zero();
    }
    return result;
}
```

若减数大于被减数，则调换减数与被减数的位置，并将结果标记为负数。对位相减结束后，用`self_check()`函数处理数组中的负数单元并完成退位；用`de_zero()`函数处理退位带来的位于最高位的0单元，修正结果的长度位数。

#### >运算的实现及分析

大于运算的实现参考了直观理解下比较两个数大小的步骤，即先比较符号，再比较位数，再从最高位向下比较。代码实现如下：

```cpp
bool LongInt::operator>(const LongInt & _LI)const{
    if(this->sign == true && _LI.sign == false){
        return true;
    }
    else if(this->sign == false && _LI.sign == true){
        return false;
    }
    else if(this->sign == true && _LI.sign == true){
        if(this->length > _LI.length){
            return true;
        }
        else if(this->length < _LI.length){
            return false;
        }
        else{
            int length = this->length;
            for(int i = length - 1; i >= 0; i--){
                if(this->a[i] > _LI.a[i]){
                    return true;
                }
                if(this->a[i] < _LI.a[i]){
                    return false;
                }
            }
            return false;
        }
    }
    else{// double minus situation
        if(this->length > _LI.length){
            return false;
        }
        else if(this->length < _LI.length){
            return true;
        }
        else{
            int length = this->length;
            for(int i = length - 1; i >= 0; i--){
                if(this->a[i] > _LI.a[i]){
                    return false;
                }
                if(this->a[i] < _LI.a[i]){
                    return true;
                }
            }
            return false;
        }
    }
}
```

参考平常比较数字大小的方式，算法的正确性不言而喻；复杂度在最佳情形（即仅通过符号、位数信息就能比较出两数的大小）为$O(1)$，最差情形为$O(n)$。



#### 减法算法的正确性分析

对位相减部分：参考对位相加部分的证明，正确性可以得到保证。

`self_check()`部分：对位相减后

