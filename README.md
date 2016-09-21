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







