#include "header.h"
#include <vector>
int main()
{
    vector<float> p={0.25,0.3,0.4,0.65};
    bitset<n> X1;
    srand(clock());
    Set_Bit(X1, p[0]);
    cout << "X1X2X3.... = " << X1 << "    " << Probability_Bit(X1) << "    " << X1.to_ulong() << endl;


    bitset<n> X2;
    srand(clock());
    Set_Bit(X2, p[1]);
    cout << "X1X2X3.... = " << X2 << "    " << Probability_Bit(X2) << "    " << X2.to_ulong() << endl;


    bitset<n> X3;
    srand(clock());
    Set_Bit(X3, p[2]);
    cout << "X1X2X3.... = " << X3 << "    " << Probability_Bit(X3) << "    " << X3.to_ulong() << endl;

    bitset<n> X4;
    srand(clock());
    Set_Bit(X4, p[3]);
    cout << "X1X2X3.... = " << X4 << "    " << Probability_Bit(X4) << "    " << X4.to_ulong() << endl;

    //////////////////////////////////
    bitset<t> fx = Func_res(X1, X2, X3, X4);
}