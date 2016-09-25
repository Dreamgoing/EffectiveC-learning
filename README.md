# EffectiveC-learning



#Effective C++ 0 导读


##术语（Terminology）

###1.声明式（declaration）：告诉编译器某个东西的名称和类型。忽略其中的细节。

```  c++
extern int x; // object 声明式
std::size_t numDigits(int number); // 函数（function）声明式
class Widget;  //类声明式

template <typename T> //模版（template） 声明式
class GraphNode;

```
其中__size_t__只是一个typedef,是c++计算个数时的某种不带正负号(unsigned)的类型。

###2.定义式（definition）：提供编译器一些声明式所遗漏的细节。对对象而言定义式为编译器为此对象拨发内存的地点。

``` c++
int x;
std::size_t numDigits(int number){
    std::size_t digitsSoFar = 1;
    while ((number/=10)!=0) ++digitsSoFar;
    return digitsSoFar;
}

class Widget{
public:
    Widget();
    ~Widget();
    
};
template <typename T>
class GraphNode{
    GraphNode();
    ~GraphNode();
};
```

###3.explicit 声明构造函数
explicit 声明构造函数可以防止被执行隐式类型转换（__implicit type conversions__）,但是仍然可以用来显式类型转换。

``` c++
class B{
public:
    explicit B(int x = 0,bool b = true);
};
```
被声明为explicit的构造函数通常比其non－explici更好。因为禁止编译器执行非预期的类型转换。

###4.copy 构造函数

copy构造函数用来“以同类型对象初始化自我对象”，通俗的说就是复制一份。具体实现如下：

``` c++
class Widget{
public:
    int id;

    Widget(int id);

public:
    Widget();
    ~Widget();
    Widget(const Widget& rhs);
    Widget& operator=(const Widget &rhs);
    void printWidget();


};

Widget::Widget() {

}

Widget::~Widget() {

}
Widget::Widget(int id) : id(id) {}

Widget::Widget(const Widget &rhs):id(rhs.id) {  //copy构造

}

Widget &Widget::operator=(const Widget &rhs) {  //copy assignment 操作符
    id = rhs.id;
    return *this;
}

```

copy构造函数是一个重要的函数，它定义了一个对象如何__passed by value__.
通常来说以__by value__ 传递用户自定义类型通常不是很好的选择，__pass by reference to const__ 是更好的选择。

###5.其他

命名习惯方面 __lhs__ 与 __rhs__ 为二元操作符（__binary operators__）
TR1 (Technical Report 1) 是一份规范，描述加入c++标准程序库的诸多新机能。
Boost开源库。

##附录

此后会写一系列相关的c++学习专栏。推荐书籍《stl源码刨析》 《Effective c++》等等。
相关代码同步 [github](https://github.com/Dreamgoing/EffectiveC-learning)
欢迎关注互相交流学习。

#Effective c++ 01 习惯于c++

##1. c++是一个语言联邦

+ 多重范型编程语言（multiparadigm programming language）
+ 支持过程 (procedural)
+ 支持面向对象 (object-oriented)
+ 函数形式 (functional)
+ 泛型形式 (generic)
+ 元编程形式 (metaprogramming)

##2. 尽量使用const,enum,inline 替换 #define

这个的意思是，__尽可能多的让编译器替换预处理器__。因为预处理器会根据宏定义的内容，在源代码中直接盲目替换，有可能会导致未知的错误发生。

``` c++
const char* const author = "wangruoxuan";
const std::string authorStr("wangruoxuan");

class GamePlayer{
private:
    static const int numTurns = 5; // class 类中专属的常量。
    int wins[numTurns];
};
```

上图代码为两种字符串常量的定义，第二种更优。 __numTurns__ 为class GamePlayer 的专属常量，为了将常量的作用域( __scope__ ) 限制在class类，必须为class 的一个member；而为了确保此常量至多只有一份实体，声明该变量为 __static__ 成员。

注意： 也可以用enum hack 替换上述实现。

``` c++
 enum {Num = 5};
 int fail[Num];
```
--
__用inline 替换宏定义的函数。__

``` c++
template <typename T>
inline T callWithMax(const T& a,const T& b){
    return a>b?a:b;
}
```

+ 对于单纯的常量用const enums 替换 #define
+ 对于形似函数的宏 (macros) ，最好使用 inline 函数替换 ＃defines.


##3. 使用const

###在声明常量时

+ const 修饰符用来修饰在不同作用域下的常量。例如class global namespace 等等。
+ const 可以用来指出指针或者所指的事物是不是const

``` c++
char greet[] = "hello";
const char *p = greet; // non-const pointer ,const data
char* const p1 = greet; // const pointer, non-const data
const char*  const p2 = greet; // const pointer, const data
```
其中 const char * p 与 char const * p 相同。但是 __char* const p__ 与 
__const char ＊p__ 不同。 前者为指针常量，后者为数据常量。

--

###在STL中const

如果关键字const出现在星号左边，表示所指物是常量；如果出现在星号右边，表示指针自身是常量，如果在星号两边都出现了const则表示指针和指物都是常量。

``` c++
const std::vector<int>::iterator iter = vec.begin();  
// T* const 可以改变iter所指的值，但是不能改变iter指针。
std::vector<int>::const_iterator cIter = vec.begin(); 
// const *T 不可改变cIter所指的值，但是可以改变iter的指针。

```
--
###const 令函数返回一个常量值

为了避免 （a*b）= c; 的情况发生。当然这样的错误应该避免。
使用const 令重载的操作符返回一个const的值就避免了上述不必要的情况发生。

``` c++
class Rational{
public:
    const Rational operator*(const Rational& lhs,const Rational& rhs);
};

const Rational Rational::operator*(const Rational &lhs, const Rational &rhs) {
    return Rational();
}
```

--

###const 成员函数
 
将const 实施于成员函数的目的，是为了确认该成员函可以作用于const对象身上。基于两个理由：

+ 使const接口比较容易理解。得知哪个函数可以改动对象内容而哪个函数不行。
+ 使操作const对象成为可能。因为改善c++ 程序效率的一个根本办法是pass by reference-to-const

``` c++
class TextBlock{
public:
    static const int Num = 30;
    char text[Num];
public:
    const char& operator[](std::size_t position) const;
};

const char &TextBlock::operator[](std::size_t position) const {
    return text[Num];
}
```

上面const成员函数的实现，是返回一个const值且text[] 成员在函数中__不可改变__。


``` c++
class TextBlock{
public:
    static const int Num = 30;
    char text[Num];
public:
    char& operator[](std::size_t position) ;
};

char& TextBlock::operator[](std::size_t position)  {
    text[position]++;
    return text[position];
}
```

此种实现，不同与前者，此种返回的值可以改变（reference to char实现），并且，成员变量的内容在重载操作符中的可以被改变。

总结：const前置声明函数返回const值，后置声明保证了成员变量的稳定性，即在函数执行的过程中__不被改变__,这就是 __bitwise const__原则。

--

const 成员函数，保证了成员变量在函数实现中__不能改变__ ,但是有时候需要改变成员变量，此时用一个与const相关的 __mutable__(可变的) 修饰成员变量来实现。

``` c++
class CTextBlock{
private:
    char *pText;
    mutable std::size_t textLength;
    mutable bool lengthIsValid;
public:
    CTextBlock(char *pText);

    std::size_t length() const;
};

std::size_t CTextBlock::length() const {
    if(!lengthIsValid){
        textLength = std::strlen(pText); //现在可以改变。
        lengthIsValid = true;
    }
    return textLength;
}

CTextBlock::CTextBlock(char *pText) : pText(pText) {}

```









