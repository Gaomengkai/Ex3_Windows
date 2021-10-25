#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class QUEUE {
    int* const  elems;	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	//elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
    QUEUE(int m);		//��ʼ�����У��������m��Ԫ��
    QUEUE(const QUEUE& q); 			//��q�����ʼ������
    QUEUE(QUEUE&& q)noexcept;		//��q�ƶ���ʼ������
    virtual operator int() const noexcept;	//���ض��е�ʵ��Ԫ�ظ���
    virtual int size() const noexcept;		//���ض�����������Ԫ�ظ���max
    virtual QUEUE& operator<<(int e);  	//��e�����β���������ص�ǰ����
    virtual QUEUE& operator>>(int& e); 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    virtual QUEUE& operator=(const QUEUE& q);//�����ֵ�����ر���ֵ����
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//�ƶ���ֵ�����ر���ֵ����
    virtual char* print(char* s) const noexcept;//��ӡ������s������s
    virtual ~QUEUE();	 					//���ٵ�ǰ����
};
class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);                    		//��ʼ��ջ�������2m-2��Ԫ��
    STACK(const STACK& s);         		//��ջs�����ʼ��ջ
    STACK(STACK&& s)noexcept;     		//��ջs�ƶ�������ʼ��ջ
    int  size()const noexcept;		  		//����ջ��������2m
    operator int() const noexcept;	   		//����ջ��ʵ��Ԫ�ظ���
    STACK& operator<<(int e); 	     		//��e��ջ�������ص�ǰջ
    STACK& operator>>(int& e);     		//��ջ��e�������ص�ǰջ
    STACK& operator=(const STACK& s);	//�����ֵ�����ر���ֵջ
    STACK& operator=(STACK&& s)noexcept;//�ƶ���ֵ�����ر���ֵջ
    char* print(char* b)const noexcept;	//��ջ�׵�ջ����ӡջԪ�� 
    ~STACK()noexcept;	              	//����ջ
};


/// <summary>
/// ��ʼ�����У��������m��Ԫ��
/// </summary>
/// <param name="m"></param>
QUEUE::QUEUE(int m) :elems(new int[m]), max(m), head(0), tail(0) {}


/// <summary>
/// ��q�����ʼ������
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
/// ��q�ƶ���ʼ������
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
/// ���ض��е�ʵ��Ԫ�ظ���
/// </summary>
/// <returns></returns>
QUEUE::operator int() const noexcept
{
    return max == 0 ? 0 : (tail + max - head) % max;
}



/// <summary>
/// ���ض�����������Ԫ�ظ���max
/// </summary>
/// <returns></returns>
int QUEUE::size() const noexcept
{
    return this->max;
}



/// <summary>
/// ��e�����β���������ص�ǰ����
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
/// �Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
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
/// �����ֵ�����ر���ֵ����
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
/// �ƶ���ֵ�����ر���ֵ����
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
/// ��ӡ������s������s
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
/// ���ٵ�ǰ����
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
/// ��ʼ��ջ�������2m-2��Ԫ��
/// </summary>
/// <param name="m"></param>
STACK::STACK(int m) :QUEUE(m), q(m) {}



/// <summary>
/// ��ջs�����ʼ��ջ
/// </summary>
/// <param name="s"></param>
STACK::STACK(const STACK& s) : QUEUE((QUEUE&)s), q(s.q) {}



/// <summary>
/// ��ջs�ƶ�������ʼ��ջ
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK::STACK(STACK&& s) noexcept :QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {}



/// <summary>
/// ����ջ��������2m
/// </summary>
/// <returns></returns>
int STACK::size() const noexcept
{
    return QUEUE::size() + q.size();
}



/// <summary>
/// ����ջ��ʵ��Ԫ�ظ���
/// </summary>
/// <returns></returns>
STACK::operator int() const noexcept
{
    return QUEUE::operator int() + q.operator int();
}



/// <summary>
/// ��e��ջ�������ص�ǰջ
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
/// ��ջ��e�������ص�ǰջ
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
/// �����ֵ�����ر���ֵջ
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
/// �ƶ���ֵ�����ر���ֵջ
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
/// ��ջ�׵�ջ����ӡջԪ��
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
/// ����ջ
/// </summary>
/// <returns></returns>
STACK::~STACK() noexcept
{
    QUEUE::~QUEUE();
    q.~QUEUE();
}