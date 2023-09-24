#include <iostream>
#include <iomanip>
using namespace std;
template <typename T>
void Print(T *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << *(A+i);
    }
    cout << endl;
}
template <typename T>
void ShellSort(T *A, T *B,int lg)
{
    int n=(B-A);

    for (int d = lg; d >= 1; d = d / 2)
    {
        cout<<setw(5)<<n/d;
       for (int i = 0; i < n; i++)
       {
           for (int j = i; j < n; j=j+d)
           {
               if (*(A+j)>*(A+i))
               {
                   int tmp= *(A+j);
                   *(A+j)=*(A+i);
                   *(A+i)=tmp;
               }
           }
           
       }
       
    }
}

int main()
{
    int n = 20;
    int *Arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        Arr[i] = rand() % 100;
    }
    cout<<"maccub"<<endl;
    Print<int>(Arr, n);
    ShellSort<int>(Arr+2,Arr+12,5);
    cout<<endl<<"new maccub "<<endl;
    Print<int>(Arr,n);
}