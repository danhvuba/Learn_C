#include <iostream>
#include <string>
using namespace std;

struct student
{
    string *name;
    int *number;
    student *next;
    student *prev;
};
class List
{
    student *head;
    student *tail;

public:
    List()
    {
        head = NULL;
        tail = NULL;
    }
    ~List()
    {
        student *tmp;
        while (head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void Insert(student *new_std)
    {
        if (head)
        {
            head->prev = new_std;
        }
        else
            tail = new_std;
        new_std->next = head;
        head = new_std;
        new_std->prev = head;
    }
    void Delete(string name);
    bool IsEmpty()
    {
        if (head)
            return false;
        else
            return true;
    }
    void Find(string name)
    {
        if (this->IsEmpty())
        {
            cout << "List is empty" << endl;
            return;
        }
        student *tmp = tail;

        while (tmp)
        {
            if (*tmp->name == name)
            {
                cout << "student's name: " << *tmp->name << ", score: " << *tmp->number << endl;
                break;
            }
            tmp = tmp->prev;
            if (tmp->prev == NULL)
            {
                cout << "not here" << endl;
            }
        }
    }
    void Print()
    {
        if (this->IsEmpty())
        {
            cout << "List is empty" << endl;
            return;
        }
        student *tmp = head;
        cout << "List is:" << endl;
        while (tmp)
        {
            cout << "student's name: " << *tmp->name << ", score: " << *tmp->number << endl;
            tmp = tmp->next;
        }
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
    newstd->prev = NULL;
    return newstd;
}

int main()
{
    cout << "hello" << endl;
    List L;
    for (int i = 0; i < 3; i++)
    {
        L.Insert(Enter_student());
    }

    L.Print();
    string name;
    cout << "student's name: ";
    getline(cin, name);
    L.Find(name);
    L.~List();
    L.Print();
}