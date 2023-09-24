//#pragma once
#include <iostream>
#include <string>
using namespace std;

struct student
{
    string *name;
    int *number;
    student *next;
};
class Stack
{
    student *top;
public:
    Stack();
    ~Stack();
    void Push(student *);
    student *Pop();
    student *GetTop();
    bool IsEmpty();
    void OutputStack();
};
student *Enter_student();
