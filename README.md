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
    char* getpText(){
        return pText;
    }
    CTextBlock();

    CTextBlock(char *pText);

    std::size_t length() const;
};

std::size_t CTextBlock::length() const {
    cout<<lengthIsValid<<endl;
    if(!lengthIsValid){
        //cout<<"ok"<<endl;
        textLength = std::strlen(pText); //现在可以改变。
        lengthIsValid = true;
    }
    return textLength;
}

CTextBlock::CTextBlock(char *pText) : pText(pText) {
    lengthIsValid = true; //成员变量初始化很重要，不然会出现奇怪的错误。
    textLength = std::strlen(pText);
}

CTextBlock::CTextBlock() {
    lengthIsValid = false;
    textLength = 0;
}


```

__使用成员变量的时候确保已经初始化__ (编译器不会为你做初始化的工作！) 上述代码在测试的过程中，由于自身疏忽，如果构造函数中没有对成员变量初始化时，成员变量的值为随机数，因此不安全会出现很奇怪的错误，为了规范编程的要求，避免不必要的错误发生，在构造函数中一定要初始化。


--

###non-const调用const 避免代码重复

例如 

``` c++
class TextBlock{
public:
    static const int Num = 30;
    char text[Num];
public:
    char& operator[](std::size_t position) ;
    const char& operator[](std::size_t position) const;
};

char& TextBlock::operator[](std::size_t position)  {
    text[position]++;
    //边界检验（bounds checking）
    //志记数据访问(log access data)
    //检验数据完整性(verify data integrity)
    return text[position];
}
const char &TextBlock::operator[](std::size_t position) const {
    //text[position]++;
    //边界检验（bounds checking）
    //志记数据访问(log access data)
    //检验数据完整性(verify data integrity)
    return text[position];
}
```
在上述代码中，const 和 non－const 的函数实现中都出现了，同样的内容，在规模较大的项目中，编译时间过长，维护，代码膨胀都是令人很头疼的问题。解决上述问题的方式就是常量转型 __(casting away constness)__。具体实现如下：

``` c++
class TextBlock{
public:
    static const int Num = 30;
    char text[Num];
public:
    char& operator[](std::size_t position) ;
    const char& operator[](std::size_t position) const;
};

char& TextBlock::operator[](std::size_t position)  {
    return const_cast<char&>( //将op[]返回值的const转除
            static_cast<const TextBlock&>(*this)[position] //为*this 加上const 然后调用const op[]。 
    );
    
}
const char &TextBlock::operator[](std::size_t position) const {
    //text[position]++;
    //边界检验（bounds checking）
    //志记数据访问(log access data)
    //检验数据完整性(verify data integrity)
    return text[position];
}
```
__Singleton__ 模式
上述实现过程中有两个转型操作：

+ 将__*this__  从原始类型TextBlock& 转型为 const TextBlock& （转型类似强制类型转换）用来调用 operator[ ] const版本。
+ 从const operator[ ]的返回值中移除const

注意：反向操作是不允许的：令const 版本调用 non-const 版本。因为const 成员函数承诺绝不改变其对象的逻辑状态(logical state)。

--
###请记住
+ 将某些东西声明为const可以帮助编译器报错。
+ 编译器强制实施bitwise constness。但是编写程序是应该使用 “概念上的常量性” （__conceptual constness__）。
+ 当const 和 non-const 成员函数有着实质等价的实现时，令non-const 版本调用const版本，可以避免代码的重复。

--
###确定对象被使用前已先被初始化。
为了避免随机初始化的值，导致不可测知的程序行为。我们应当在对象，变量在使用之前保证其已经被初始化。这样初始化的责任就落到了构造函数(__constructors__)

构造函数的初始化分为 __赋值(assignment)__ 和 __初始化(initialization)__ 通常来说在构造函数中使用 __成员初值列(member initialization list)__ 在效率上面更优于赋值初始化。

``` c++
class PhoneNumber {
};

class ABEntry {
private:
    std::string theName;
    std::string theAddress;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;
public:
    ABEntry();

    ABEntry(const std::string &name, const std::string &address,
            const std::list<PhoneNumber> &phones);
};

ABEntry::ABEntry(const std::string &name, const std::string &address,
                 const std::list<PhoneNumber> &phones)
        : theName(name), theAddress(address), thePhones(phones), numTimesConsulted(0) {}

ABEntry::ABEntry() : theName(), theAddress(), thePhones(), numTimesConsulted(0)
{ }
```

上述代码是在构造函数中用 __成员初值列(member initalization list)__  的方法去完成初始化的工作。相比如果用简单的赋值操作进行初始，这样效率要高。赋值初始化，要经过default 构造函数，然后调用 __copy assignment__ ，而成员初值列是单次调用copy 构造函数效率要高。在上述代码中  default 构造中对numTimesConsulted 成员做了显式的初始化。

注：在成员初值列中初始化的顺序最好和 __内置型对象的声明__ 顺序一致。

--

### static 对象使用初始化顺序问题

所谓static 对象，其寿命从被构造出来直到程序结束为止，因此 stack 和 heap-based对象都被排除。

+ __local static__ :包括global对象，定义于namespace作用域内的对象，在class内，在函数内，以及在file作用域内被声明为static的对象。
+ __non-local static__ :其他,程序结束时static对象会被自动销毁，也就是它们的析构函数会在main()函数结束时被自动调用。

编译单元 (__translation unit__) :是指产出单一目标文件（__single object file__）的那些源码。基本上它是单一源码文件加上它所含入的头文件。

问题:多个源码文件，每一个至少一个non-local static。当某个源码文件中的non-local static 的动作使用了另一个编译单元中的的某个对象，但是这个对象并 __未初始化__ 因此出现问题。

``` c++
class FileSystem{
public:
    std::size_t numDisk() const;
};

std::size_t FileSystem::numDisk() const {
    return 0;
}
extern FileSystem tfs;
FileSystem& tfs1(){    //这个函数用来替换tfs对象
    static FileSystem fs; //它在FileSystem class中可能是个static。
    return fs; //定义并初始化一个local static对象 并返回一个reference指向上述对象。
}
class Directory{
public:
    Directory();

};

Directory::Directory() {
    std::size_t disks = tfs1().numDisk();
}
extern Directory tempDir;
Directory& tempDir1(){
    static Directory td; //同上
    return td;
}
```
解决方法如上所示。Singleton 模式。
__C++保证，函数内的local static对象会在“该函数被调用期间” “首次遇上该对象之定义式”时被初始化。

注意：任何一种non-const static对象，不论它是local还是non-local，在多线程的环境下“等待某种事情发生”都会有麻烦，处理这个麻烦的做法是: __在程序单线程启动阶段(single-threaded startup portion )手工调用所有reference－returning函数(也就是上述代码实现),这可以消除与初始化有关的“竞速形势”(race conditions)。__

+ 为内置对象进行手工初始化。
+ 使用构造函数的__成员初值列(member initialization list)__。
+ 为了免除 __"跨编译单元之初始化次序"__ 问题，请以local static 对象替换 non-static对象。具体实现是 reference-returning 函数。

此处较难理解，在以后的编程中用到深究。
##总结
const 对于c++规范编程，效率方面十分重要。需要熟练掌握。第1章的学习笔记结束，相关代码通过测试同步[github Dream_going](https://github.com/Dreamgoing)。近期更新之后的学习笔记。












