#include "Stack.h"
Stack::Stack() : top(NULL){};
Stack::~Stack()
{
    student *tmp;
    while (top)
    {
        tmp = top;
        top = top->next;
        delete tmp;
    }
};

void Stack::Push(student *new_std)
{
    new_std->next = top;
    top = new_std;
};

student *Stack::Pop()
{
    if (this->IsEmpty())
    {
        cout << "Stack is empty" << endl;
        return NULL;
    }
    student *tmp = top;
    top = top->next;
    return tmp;
};

student *Stack::GetTop()
{
    return top;
}

bool Stack::IsEmpty()
{
    if (top)
        return false;
    else
        return true;
}

void Stack::OutputStack()
{
    if (this->IsEmpty())
    {
        cout << "Stack is empty" << endl;
        return;
    }
    student *tmp = top;
    cout << "Stack is:" << endl;
    while (tmp)
    {
        cout << "student's name: " << *tmp->name << ", score: " << *tmp->number << endl;
        tmp = tmp->next;
    }
};

student *Enter_student()
{
    student *newstd = new student;
    newstd->name = new string;
    newstd->number = new int;
    cout << "student's name: ";
    getline(cin, *newstd->name);
    cout << "student's score: ";
    cin >> *newstd->number;
    cin.ignore();
    newstd->next = NULL;
    return newstd;
};