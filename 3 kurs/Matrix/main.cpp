#include "matrix.h"

int main()
{
    Matrix A(3,26);
    A.Mtr[0]=new int[3]{3,3,5};
    A.Mtr[1]=new int[3]{3,2,4};
    A.Mtr[2]=new int[3]{7,11,2};
    // A.Set_matrix();
    cout << "Det= " << A.Det_matrix() << endl;
    A.Print_matrix();
    if (A.Det_matrix() != 0)
    {
        cout << "B:\n";
        Matrix B(A.Inverse_matrix());
        B.Print_matrix();

        cout << "A*B:\n";
        Matrix C(A * B);
        C.Print_matrix();
    }
}