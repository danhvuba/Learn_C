#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>

using namespace std;

void SortArray(int *A, int n)
{
    int tmp;
    for (int i = 1; i < n; i++)
    {
        tmp = A[i];
        int j;
        for (j = i - 1; (j >= 0) && (A[j] > tmp); j--)
        {
            A[j + 1] = A[j];
        }
        A[j + 1] = tmp;
    }
}
// сортировать массив

bool Is(int *a, int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            return true;
        }
    }
    return false;
}
// провеприть ключ 'key' уже есть в массив или нет

int *Array(int n)
{
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        int key = rand() % (10 * n);
        while (Is(a, i, key))
        {
            key = rand() % (10 * n);
        }
        // выбрать случайое новое число
        a[i] = key;
    }
    return a;
}
// создать новый массив из n элементов

int Linear(int *a, int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            return i + 1;
        }
    }
    return n;
}
// линейно-последовательный

int Binary(int *a, int l, int r, int key)
{
    int step = 0;
    while ((l + 1) < r)
    {
        step++;
        int i = (l + r) / 2;
        if (a[i] == key)
        {
            return step;
        }
        else if (a[i] > key)
        {
            r = i;
        }
        else if (a[i] < key)
        {
            l = i;
        }
    }
    return step;
}
// бинарный поиск

int fib(int n)

{
    if (n < 1)
        return 0;
    if (n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}
// функция выйчислить n-ое число фибоначи

int Fibonacci(int *a, int l, int r, int key)
{
    int m = 0, step = 0;
    while (fib(m) < (r - l))
        m++;
    // определить найбольшое m-ое число фибоначи, которое меньше 'r-l'
    if (fib(m - 1) == 0)
    {
        step++;
        return step;
    }
    // то есть r=l, m=l-r=0;

    if (a[l + fib(m - 1)] == key)
    {
        step++;
        return step;
    }
    else if (a[l + fib(m - 1)] > key)
    {
        step++;
        return step + Fibonacci(a, l, l + fib(m - 1), key);
    }
    else if (a[l + fib(m - 1)] < key)
    {
        step++;
        return step + Fibonacci(a, l + fib(m - 1), r, key);
    }
    return step;
}
// фибоначии поиск

int Interpolation(int *a, int l, int r, int key)
{
    int step = 0;
    while ((l + 1) < r)
    {
        step++;
        int i = l + ((key - a[l]) * (r - l) / (a[r] - a[l]));
        if (a[i] == key)
        {
            return step;
        }
        else if (a[i] > key)
        {
            r = i - 1;
        }
        else if (a[i] < key)
        {
            l = i + 1;
        }
    }
    return step;
}
// интерполяционный поиск

int IdSearch(int *a, int n, int key)
{
    int p = static_cast<int>(sqrt(n));
    int m = n / p, id[m];
    for (int i = 0; i < m; i++)
    {
        id[i] = i * p;
    }
    // создать массив индексов 0,p,2p,...,m*p(<=n)

    int step = 0, i = 0;
    while ((i < m) && (a[id[i]] <= key))
    {
        step++;
        if (a[id[i]] == key)
        {
            return step;
        }
        i++;
    }
    // найти первый элемент, который > key

    int l, r;
    if (i < m)
    {
        l = id[i - 1], r = id[i];
    }
    else
    {
        l = id[i - 1], r = n;
    }
    step = step + Binary(a, l, r, key);
    return step;
}
// индексно-последовательный поиск

void OutT(int *a, int n)
{
    int const x = 1000;
    // вычислить за 1000 раз
    float T[5]{0, 0, 0, 0, 0};
    for (int i = 0; i < x; i++)
    {
        int id = rand() % n;
        T[0] = T[0] + Linear(a, n, a[id]);
    }

    // линейно-последовательный

    SortArray(a, n);
    // сортировать массив
    for (int i = 0; i < x; i++)
    {
        int id = rand() % n;
        T[1] = T[1] + Binary(a, 0, n - 1, a[id]);
        // бинарный поиск
        T[2] = T[2] + Fibonacci(a, 0, n - 1, a[id]);
        // фибоначии поиск
        T[3] = T[3] + Interpolation(a, 0, n - 1, a[id]);
        // интерполяционный поиск
        T[4] = T[4] + IdSearch(a, n, a[id]);
        // индексно-последовательный поиск
    }
    cout << setw(5) << n << setw(15) << T[0] / x << setw(15) << T[1] / x << setw(15) << T[2] / x << setw(15) << T[3] / x << setw(15) << T[4] / x << endl;
}
// функция выводить результаты


int main()
{
    int x;
    cout << "Вводить количество экспериментов: ";
    cin >> x;
    int n[x];
    cout << "Вводить количество элементов N" << endl;
    for (int i = 0; i < x; i++)
    {
        cout << i + 1 << "-й эксперимент: ";
        cin >> n[i];
    }

    cout << setw(5) << "N" << setw(21) << "Линей." << setw(20) << "Бинар." << setw(22) << "Фибона." << setw(19) << "Интер." << setw(22) << "Инд.-пос." << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < x; i++)
    {
        int *a = Array(n[i]);
        OutT(a, n[i]);
    }
}