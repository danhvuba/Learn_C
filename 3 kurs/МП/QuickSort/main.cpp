#include <iostream>
using namespace std;
void Swap(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
void QickSort(int *A, int first, int last)
{
    if (first == last)
    {
        return;
    }
    cout << "\n\nARRAY" << endl;
    for (int i = first; i <= last; i++)
    {
        cout << "a[" << i << "]= " << A[i] << "  ";
    }
    cout << endl;
    int j = last;
    int tmp;
    for (int i = first + 1; i <= j; i++)
    {
        if (A[i] > A[first])
        {
            tmp = i;
            while (j > i)
            {
                if (A[j] <= A[first])
                {
                    Swap(A[i], A[j]);
                    break;
                }
                else
                    j--;
            }
        }
        else
            tmp = last + 1;
    }
    tmp--;
    Swap(A[first], A[tmp]);
    for (int i = first; i < tmp; i++)
    {
        cout << "a[" << i << "]= " << A[i] << "  ";
    }
    cout << "---a[" << tmp << "]= " << A[tmp] << "----   ";
    for (int i = tmp + 1; i <= last; i++)
    {
        cout << "a[" << i << "]= " << A[i] << "  ";
    }
    cout << endl;
    if (tmp > first)
    {
        QickSort(A, first, tmp - 1);
    }

    if (tmp < last)
    {
        QickSort(A, tmp + 1, last);
    }
}

int main()
{
    int n;
    cout << "enter n:";
    cin >> n;
    int *A = new int[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "a[" << i << "]= " << A[i] << "  ";
    }
    cout << endl;

    QickSort(A, 0, n - 1);
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "a[" << i << "]= " << A[i] << "  ";
    }
    cout << endl;
}