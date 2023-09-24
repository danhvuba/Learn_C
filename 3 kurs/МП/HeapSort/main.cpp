#include <iostream>
using namespace std;
void Swap(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
void SetHeap(int *A, int last)
{
    for (int i = last - 1; i > 0; i--)
    {
        int j;
        if ((i % 2) == 0)
        {
            j = (i - 2) / 2;
        }
        else
            j = (i - 1) / 2;
        if ((j >= 0) && (A[i] > A[j]))
        {
            Swap(A[i], A[j]);
        }
    }
}
void HeapSort(int *A, int last)
{
    for (int i = last; i >= 1; i--)
    {
        SetHeap(A, i);
        Swap(A[0], A[i - 1]);
        for (int x = 0; x < i - 1; x++)
        {
            cout << "a[" << x << "]= " << A[x] << "  ";
        }
        cout << "---";
        for (int x = i-1; x < last; x++)
        {
            cout << "a[" << x << "]= " << A[x] << "  ";
        }
        cout<<endl;
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

    HeapSort(A, 10);

    for (int i = 0; i < n; i++)
    {
        cout << "a[" << i << "]= " << A[i] << "  ";
    }
    cout << endl;
}