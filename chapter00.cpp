//
// Created by 王若璇 on 16/9/21.
//

//第一章代码测试通过

#include <iostream>
#include <algorithm>

#define DEBUG_EXPLICIT
#define DEBUG_COPY
using namespace std;

extern int x; // object 声明式
std::size_t numDigits(int number); // 函数（function）声明式
class Widget;  //类声明式

template <typename T> //模版（template） 声明式
class GraphNode;


int x;
std::size_t numDigits(int number){
    std::size_t digitsSoFar = 1;
    while ((number/=10)!=0) ++digitsSoFar;
    return digitsSoFar;
}

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

void Widget::printWidget() {
    std::cout<<id<<endl;

}


template <typename T>
class GraphNode{
    GraphNode();
    ~GraphNode();
};

class B{
public:
    int x;
    bool b;
public:
    explicit B(int x = 0,bool b = true);
    void printB();
};

B::B(int x , bool b) {
    this->x = x;
    this->b = b;
}

void B::printB() {
    std::cout<<x<<" "<<b<<endl;

}

class Rational{

};
int main(){
#ifdef DEBUG_EXPLICIT
    B obj(9,9);
    B obj1;
    obj.printB();
    obj1.printB();
    B obj2(2);
    obj2.printB();
#endif

#ifdef DEBUG_COPY
    Widget a;
    a.id = 1;
    //a.printWidget();
    Widget b;
    b = a;
    b.printWidget();
    Widget c(a);
    c.printWidget();
#endif
    return 0;
}
