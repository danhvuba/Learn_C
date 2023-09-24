#include "matrix.h"

int main()
{
    uint8_t pt[]={0x0a,0x5f,0xd7,0x9a,0x50,0x32,0x64,0x2c,0x58,0xca,0xc4,0x9d,0xbf,0xf2,0x87};
    uint8_t ct_1[]={0x2c,0xea,0x4a,0x36,0x42,0xf7,0x7b,0x6f,0x3b,0x98,0xc3,0xe7,0x3f,0x43,0xe4};
    uint8_t ct_2[]={0xb8,0x88,0x5a,0xb8,0x4b,0x9a,0x88};

    int lg = 14; 
    uint8_t *Y = new uint8_t[lg];
    for (int i = 0; i < lg; i++)
    {
        Y[i]=pt[i]^pt[1];
    }

    uint8_t *X = new uint8_t[lg];
    for (int i = 0; i < lg; i++)
    {
        X[i]=ct_1[i]^ct_1[1];
    }


    Function(Y, X, lg);
    printf("A:\n");
    for (int i = 0; i < 9; i++)
    {
        Print_bit(X[i]);
        //printf("%02x", X[i]);
        cout << endl;
    }
    uint8_t a=Mul(pt[0], X) ^ ct_1[0];
    printf("a:  %x\n", a);
    Print_bit(a);
    printf("\n");


    uint8_t *E=new uint8_t[n];
    E[0]=0x80;
    E[1]=0x40;
    E[2]=0x20;
    E[3]=0x10;
    E[4]=0x08;
    E[5]=0x04;
    E[6]=0x02;
    E[7]=0x01;
    Function(X, E, n);
    for (int i = 0; i < 7; i++)
    {
        printf("%c",(Mul(ct_2[i]^a,E)));
    }
    cout<<endl;    
}