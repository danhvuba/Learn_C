#include <iostream>
using namespace std;
int SortArray(int *A, int a, int b)
{
    int value = 0;
    int tmp;
    int j;
    for (int i = a; i < b; i++)
    {
        value++;

        tmp = A[i];
        value++;
        for (int j = i - 1; (j > a - 1) && (A[j] > tmp); j--)
        {
            value++;
            value++;
            A[j + 1] = A[j];
            value++;

            A[j] = tmp;
            value++;
        }
    }
    return value;
}
void Sorting(int *A, int a, int b, int &value)
{
    int x = (b + a) / 2;
    value++;
    if (x == a)
    {
        return;
    }

    if (x > (a + 1))
    {
        Sorting(A, a, x, value);
    }

    if (x < (b - 1))
    {
        Sorting(A, x, b, value);
    }

    int tmp;
    int beg = a;
    for (int j = x; j < b; j++)
    {
        value++;
        for (int i = beg; i < j; i++)
        {
            value++;
            if (j < b)
            {
                if (A[j] < A[i])
                {
                    tmp = A[j];
                    value++;
                    A[j] = A[i];
                    value++;
                    A[i] = tmp;
                    value++;
                }
            }
        }
    }
}
int main()
{
    int n;
    cout << "enter number of elements: ";
    cin >> n;
    int *A = new int[n];
    int *B = new int[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
        B[i] = A[i];
    }
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "]= " << A[i] << "   ";
    }
    cout << "\nСортировка вставка" << endl;
    int value = SortArray(A, 0, n);

    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "]= " << A[i] << "   ";
    }
    cout << "\nfirst way " << value << endl;

    value = 0;
    Sorting(B, 0, n, value);
    cout << "Сортировка деления" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "]= " << B[i] << "   ";
    }
    cout << "\nsecond way " << value << endl;
}