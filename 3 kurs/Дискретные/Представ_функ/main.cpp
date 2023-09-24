#include "header.h"
#include "matrix.h"

int main()
{
    ////////////////////////////////////// fx
    bitset<n> a;
    bitset<l> fx;
    for (int i = 0; i < l; i++)
    {
        a = i;
        fx[i] = (a[0] & a[1]) | (a[0] & a[2]) | (a[1] & a[2]);
    }
    cout << "fx:  " << fx << endl<<fx[0]<<endl;
    

    /////////////////////////////////////// Fx
    vector<int> Fx;
    for (int i = 0; i < l; i++)
    {
        Fx.push_back(pow(-1, (int)fx[i]));
    }
    cout << "Fx:  ";
    for (int i = 0; i < Fx.size(); i++)
    {
        cout << Fx[i];
    }
    cout << endl;

    /////////////////////////////// Cf
    vector<float> Cf;
    for (int i = 0; i < l; i++)
    {
        a = i;
        float Ca = 0;
        bitset<n> c;
        for (int j = 0; j < l; j++)
        {
            c = j;
            Ca = Ca + fx[j] * pow(-1, mul(a, c));
        }
        Ca = Ca / pow(2, n);
        Cf.push_back(Ca);
    }
    cout << "Cf:  ";
    for (int i = 0; i < l; i++)
    {
        cout << Cf[i] << "  ";
    }
    cout << endl;

    /////////////////////////////////// Wf
    vector<float> Wf;
    for (int i = 0; i < l; i++)
    {
        a = i;
        float Ca = 0;
        bitset<n> c;
        for (int j = 0; j < l; j++)
        {
            c = j;
            Ca = Ca + pow(-1, (fx[j] + mul(a, c)));
        }
        Ca = Ca / pow(2, n);
        Wf.push_back(Ca);
    }
    cout << "Wf:  ";
    for (int i = 0; i < l; i++)
    {
        cout << Wf[i] << "  ";
    }
    cout << endl;

    ////////////////////////////////////// matrix A
    Matrix A(l);
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            bitset<n> b;
            a = i;
            b = j;
            A.Mtr[i][j] = pow(-1, mul(a, b) % 2);
        }
    }
    cout<<"\nMatrix A"<<endl;
    A.Print_matrix();
    Matrix B(A.Inverse_matrix());
    cout<<"\nMatrix A^-1"<<endl;
    B.Print_matrix();
    cout << "-------------------" << endl;

    //////////////////////////////  A^-1 * f
    vector<float> ff;
    for (int i = 0; i < l; i++)
    {
        float tmp = 0;
        for (int j = 0; j < l; j++)
        {
            tmp = tmp + B.Mtr[i][j] * fx[j];
        }
        ff.push_back(tmp);
    }
    cout << "ff: ";
    for (int i = 0; i < ff.size(); i++)
    {
        cout << ff[i] << "  ";
    }
    cout << endl;

    //////////////////////////////  A^-1 * F
    vector<float> FF;
    for (int i = 0; i < l; i++)
    {
        float tmp = 0;
        for (int j = 0; j < l; j++)
        {
            tmp = tmp + B.Mtr[i][j] * Fx[j];
        }
        FF.push_back(tmp);
    }
    cout << "FF: ";
    for (int i = 0; i < FF.size(); i++)
    {
        cout << FF[i] << "  ";
    }
    cout << endl;
}