#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class QUEUE {
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    QUEUE(int m);		//初始化队列：最多申请m个元素
    QUEUE(const QUEUE& q); 			//用q深拷贝初始化队列
    QUEUE(QUEUE&& q)noexcept;		//用q移动初始化队列
    virtual operator int() const noexcept;	//返回队列的实际元素个数
    virtual int size() const noexcept;		//返回队列申请的最大元素个数max
    virtual QUEUE& operator<<(int e);  	//将e入队列尾部，并返回当前队列
    virtual QUEUE& operator>>(int& e); 	//从队首出元素到e，并返回当前队列
    virtual QUEUE& operator=(const QUEUE& q);//深拷贝赋值并返回被赋值队列
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//移动赋值并返回被赋值队列
    virtual char* print(char* s) const noexcept;//打印队列至s并返回s
    virtual ~QUEUE();	 					//销毁当前队列
};
class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);                    		//初始化栈：最多存放2m-2个元素
    STACK(const STACK& s);         		//用栈s深拷贝初始化栈
    STACK(STACK&& s)noexcept;     		//用栈s移动拷贝初始化栈
    int  size()const noexcept;		  		//返回栈的容量即2m
    operator int() const noexcept;	   		//返回栈的实际元素个数
    STACK& operator<<(int e); 	     		//将e入栈，并返回当前栈
    STACK& operator>>(int& e);     		//出栈到e，并返回当前栈
    STACK& operator=(const STACK& s);	//深拷贝赋值并返回被赋值栈
    STACK& operator=(STACK&& s)noexcept;//移动赋值并返回被赋值栈
    char* print(char* b)const noexcept;	//从栈底到栈顶打印栈元素 
    ~STACK()noexcept;	              	//销毁栈
};


/// <summary>
/// 初始化队列：最多申请m个元素
/// </summary>
/// <param name="m"></param>
QUEUE::QUEUE(int m) :elems(new int[m]), max(m), head(0), tail(0) {}


/// <summary>
/// 用q深拷贝初始化队列
/// </summary>
/// <param name="q"></param>
QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max)
{
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i != q.tail; i = (i + 1) % max)
    {
        this->elems[i] = q.elems[i];
    }
}


/// <summary>
/// 用q移动初始化队列
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
QUEUE::QUEUE(QUEUE&& q) noexcept :elems(q.elems), max(q.max)
{
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i != q.tail; i = (i + 1) % max)
    {
        this->elems[i] = q.elems[i];
    }
    q.head = 0;
    q.tail = 0;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
}



/// <summary>
/// 返回队列的实际元素个数
/// </summary>
/// <returns></returns>
QUEUE::operator int() const noexcept
{
    return max == 0 ? 0 : (tail + max - head) % max;
}



/// <summary>
/// 返回队列申请的最大元素个数max
/// </summary>
/// <returns></returns>
int QUEUE::size() const noexcept
{
    return this->max;
}



/// <summary>
/// 将e入队列尾部，并返回当前队列
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
QUEUE& QUEUE::operator<<(int e)
{
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";
        return *this;
    }
    this->elems[tail] = e;
    this->tail = (tail + 1) % max;
    return *this;
}



/// <summary>
/// 从队首出元素到e，并返回当前队列
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
QUEUE& QUEUE::operator>>(int& e)
{
    if (this->tail == this->head) {
        throw "QUEUE is empty!";
        return *this;
    }
    e = this->elems[head];
    head = (head + 1) % max;
    return *this;
}



/// <summary>
/// 深拷贝赋值并返回被赋值队列
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
QUEUE& QUEUE::operator=(const QUEUE& q)
{
    if (this->elems == q.elems) return *this;
    if (this->elems != NULL) {
        delete this->elems;
    }
    *(int**)&(this->elems) = new int[q.max];
    *(int*)&(this->max) = q.max;
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i <= q.tail; i++) {
        this->elems[i % q.max] = q.elems[i % q.max];
    }
    return *this;
}



/// <summary>
/// 移动赋值并返回被赋值队列
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
QUEUE& QUEUE::operator=(QUEUE&& q) noexcept
{
    if (this->elems == q.elems) return *this;
    if (this->elems != nullptr) {
        delete this->elems;
    }
    *(int**)&(this->elems) = q.elems;
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i <= q.tail; i++) {
        this->elems[i % q.max] = q.elems[i % q.max];
    }
    q.head = 0;
    q.tail = 0;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
    return *this;
}



/// <summary>
/// 打印队列至s并返回s
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
char* QUEUE::print(char* s) const noexcept
{
    char a[10];
    int i; s[0] = 0;
    for (i = this->head; i != tail; i = (i + 1) % max)
    {
        sprintf_s(a, "%d,", this->elems[i]);
        strcat(s, a);
    }
    return s;
}



/// <summary>
/// 销毁当前队列
/// </summary>
QUEUE::~QUEUE()
{
    if (this->elems != NULL)
    {
        delete this->elems;
        this->head = 0;
        this->tail = 0;
        *(int**)&(this->elems) = NULL;
        *(int*)&(this->max) = 0;
    }
}


/// <summary>
/// 初始化栈：最多存放2m-2个元素
/// </summary>
/// <param name="m"></param>
STACK::STACK(int m) :QUEUE(m), q(m) {}



/// <summary>
/// 用栈s深拷贝初始化栈
/// </summary>
/// <param name="s"></param>
STACK::STACK(const STACK& s) : QUEUE((QUEUE&)s), q(s.q) {}



/// <summary>
/// 用栈s移动拷贝初始化栈
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK::STACK(STACK&& s) noexcept :QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {}



/// <summary>
/// 返回栈的容量即2m
/// </summary>
/// <returns></returns>
int STACK::size() const noexcept
{
    return QUEUE::size() + q.size();
}



/// <summary>
/// 返回栈的实际元素个数
/// </summary>
/// <returns></returns>
STACK::operator int() const noexcept
{
    return QUEUE::operator int() + q.operator int();
}



/// <summary>
/// 将e入栈，并返回当前栈
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
STACK& STACK::operator<<(int e)
{
    if (QUEUE::operator int() < QUEUE::size() - 1)
    {
        QUEUE::operator<<(e);
        return *this;
    }
    else if (q.operator int() < q.size() - 1)
    {
        int tmp = 0;
        QUEUE::operator>>(tmp);
        q.operator<<(tmp);
        QUEUE::operator<<(e);
        return *this;
    }
    else
    {
        throw("STACK is full!");
    }
}



/// <summary>
/// 出栈到e，并返回当前栈
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
STACK& STACK::operator>>(int& e)
{
    if (QUEUE::operator int())
    {
        int sizebase = QUEUE::operator int(), tmp = 0;
        for (int i = 0; i < sizebase - 1; i++)
        {
            QUEUE::operator>>(tmp);
            QUEUE::operator<<(tmp);
        }
        QUEUE::operator>>(e);
        return *this;
    }
    else if (q.operator int())
    {
        int sizebase = q.operator int(), tmp = 0;
        for (int i = 0; i < sizebase - 1; i++)
        {
            q.operator>>(tmp);
            q.operator<<(tmp);
        }
        q.operator>>(e);
        return *this;
    }
    else
    {
        throw("STACK is empty!");
    }
}



/// <summary>
/// 深拷贝赋值并返回被赋值栈
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK& STACK::operator=(const STACK& s)
{
    QUEUE::operator=((QUEUE&)s);
    q.operator=((QUEUE&)s.q);
    return *this;
}



/// <summary>
/// 移动赋值并返回被赋值栈
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK& STACK::operator=(STACK&& s) noexcept
{
    QUEUE::operator=((QUEUE&&)s);
    q.operator=((QUEUE&&)s.q);
    return *this;
}



/// <summary>
/// 从栈底到栈顶打印栈元素
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
char* STACK::print(char* b) const noexcept
{
    char* s = (char*)malloc(sizeof(char) * size());
    s = QUEUE::print(s);
    b = q.print(b);
    strcat(b, s);
    free(s);
    return b;
}



/// <summary>
/// 销毁栈
/// </summary>
/// <returns></returns>
STACK::~STACK() noexcept
{
    QUEUE::~QUEUE();
    q.~QUEUE();
}