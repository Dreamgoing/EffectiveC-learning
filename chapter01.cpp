//
// Created by 王若璇 on 16/9/21.
//

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>


using namespace std;
const char *const author = "wangruoxuan";
const std::string authorStr("wangruoxuan");

class GamePlayer {
public:
    static const int numTurns = 5; // class 类中专属的常量。
    int wins[numTurns];

    enum {
        Num = 5
    };
    int fail[Num];
};

template<typename T>
inline T callWithMax(const T &a, const T &b) {
    return a > b ? a : b;
}

char greet[] = "hello";
const char *p = greet; // non-const pointer ,const data
char *const p1 = greet; // const pointer, non-const data
const char *const p2 = greet; // const pointer, const data
void test1() {
    char tmp[] = "suffix";
    *p1 = 'a';
    p1[2] = '3';
    cout << p1 << endl;
    //strcat(p,tmp);

}

void test2() {
    std::vector<int> vec;
    vec.clear();
    for (int i = 1; i <= 10; i++) {
        vec.push_back(i);
    }
    const std::vector<int>::iterator iter = vec.begin();  // T* const 可以改变iter所指的值，但是不能改变iter指针。
    std::vector<int>::const_iterator cIter = vec.begin(); // const *T 不可改变cIter所指的值，但是可以改变iter的指针。

}

class Rational {
public:
    const Rational operator*(const Rational &rhs);
};

const Rational Rational::operator*(const Rational &rhs) {
    return Rational();
}

/*class TextBlock{
public:
    static const int Num = 30;
    char text[Num];
public:
    const char& operator[](std::size_t position) const;
};

const char &TextBlock::operator[](std::size_t position) const {
    //text[position]++;
    return text[position];
}*/
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
void test3(){
    TextBlock t;
    char tmp[30] = "abc";
    t.text[0] = 'a';
    t[0] = 'd';
    cout<<t[0]<<endl;

}
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
void text4(){
    char s[] = "hello world";
    CTextBlock a(s);
    std::cout<<a.length()<<endl;
}

int main() {
    //test1();
    //test3();
    text4();



    return 0;
}