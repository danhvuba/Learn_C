#include "Stack.h"

int main()
{
    Stack S;
    S.OutputStack();
    int n;
    cout << "enter number of element: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        S.Push(Enter_student());
    };
    S.OutputStack();
    student *PopS = S.Pop();
    cout << "POP student's name: " << *PopS->name << ", score: " << *PopS->number << endl;
    student *TopS = S.GetTop();
    cout << "TOP student's name: " << *TopS->name << ", score: " << *TopS->number << endl;
    cout << "New ";
    S.OutputStack();
    cout << "delete stack." << endl;
    S.~Stack();
    if (S.IsEmpty())
        cout << "Stack is empty" << endl;
    else
        cout << "Stack isn't empty" << endl;
    return 0;
}