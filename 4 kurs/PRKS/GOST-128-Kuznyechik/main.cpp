#include <iostream>
#include <stdio.h>
#include <string>
#include <ctime>

using namespace std;

#define fx 0b111000011
#define bit(a, i) ((a >> i) & 1)
#define u8 uint8_t
#define n 8
#define Shift_left(a, n, fx) (((a ^ (((a >> (n - 1)) & 1) << (n - 1))) << 1) ^ (fx * ((a >> (n - 1)) & 1)))

int Mul_fx(u8 ax, u8 bx)
{
    u8 result = 0;
    for (int i = 0; i < n; i++)
    {
        if (bit(bx, i))
        {
            result = result ^ ax;
        }
        ax = Shift_left(ax, n, fx);
    }
    return result;
}

const u8 pi[256] = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77,
                    233, 119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193,
                    249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132,
                    2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44,
                    81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181, 112, 14, 86,
                    8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21, 161, 150, 41, 16, 123,
                    154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117, 25, 61, 255, 53, 138,
                    126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67, 201, 215,
                    121, 214, 246, 124, 34, 185, 3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40,
                    80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38,
                    65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163, 165, 125, 105, 213, 149, 59, 7, 88, 179,
                    64, 134, 172, 29, 247, 48, 55, 107, 228, 136, 217, 231, 137, 225, 27, 131, 73, 76, 63, 248,
                    254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208,
                    190, 229, 108, 82, 89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

u8 pi_1[256];
u8 poleFx[256][256];

// 128 = 16 u8
#define l(a) (poleFx[148][a[15]] ^ poleFx[32][a[14]] ^  \
              poleFx[133][a[13]] ^ poleFx[16][a[12]] ^  \
              poleFx[194][a[11]] ^ poleFx[192][a[10]] ^ \
              poleFx[1][a[9]] ^ poleFx[251][a[8]] ^     \
              poleFx[1][a[7]] ^ poleFx[192][a[6]] ^     \
              poleFx[194][a[5]] ^ poleFx[16][a[4]] ^    \
              poleFx[133][a[3]] ^ poleFx[32][a[2]] ^    \
              poleFx[148][a[1]] ^ poleFx[1][a[0]])

// 128 = 16 u8, result in 'a'
inline void X(u8 *a, const u8 *k)
{
    for (int i = 0; i < 16; i++)
    {
        a[i] ^= k[i];
    }
}

void Print_128bit(u8 *tmp)
{
    for (int i = 15; i >= 0; i--)
    {
        printf("%02x", tmp[i]);
    }
}

// 128 = 16 u8, result in 'a'
inline void S(u8 *a)
{
    for (int i = 0; i < 16; i++)
    {
        a[i] = pi[a[i]];
    }
}

// 128 = 16 u8, result in 'a'
void S_1(u8 *a)
{
    for (int i = 0; i < 16; i++)
    {
        a[i] = pi_1[a[i]];
    }
}

// 128 = 16 u8, result in 'a'
inline void R(u8 *a)
{
    u8 tmp = l(a);
    for (int i = 0; i < 15; i++)
    {
        a[i] = a[i + 1];
    }
    a[15] = tmp;
}

// 128 = 16 u8, result in 'a'
void R_1(u8 *a)
{
    u8 tmp = a[15];
    for (int i = 15; i > 0; i--)
    {
        a[i] = a[i - 1];
    }
    a[0] = tmp;
    a[0] = l(a);
}

// 128-128-128 = (16 u8)*x3, result in 'a1, a0'
void F(u8 *a1, u8 *a0, u8 *k)
{
    // tmp* = a1*
    u8 tmp[16];
    for (int i = 0; i < 16; i++)
    {
        tmp[i] = a1[i];
    }

    // LSX[k](a1) <=> X - S - L
    {
        X(a1, k);
        S(a1);
        // L = R^16
        for (int i = 0; i < 16; i++)
        {
            R(a1);
        }
    }

    // (a1'^a0, a1)
    for (int i = 0; i < 16; i++)
    {
        a1[i] ^= a0[i];
        a0[i] = tmp[i];
    }
}

// assign 128=16u8 from *source to *res
void Assign(u8 *source, u8 *res)
{
    for (int i = 0; i < 16; i++)
    {
        res[i] = source[i];
    }
}

// res = 10*128= matrix 10*16 u8
// key 256 = 2*128= matrix 2*16 u8
void Deployment_key(u8 **res, u8 **key)
{
    // C= 32*128= matrix 32*16 u8
    u8 C[32][16];
    // C[i]= L( vec_128(i+1))
    for (int i = 0; i < 32; i++)
    {
        // C[i]= vec_128(i+1)
        for (int j = 0; j < 16; j++)
        {
            C[i][j] = 0;
        }
        C[i][0] = i + 1;

        // L = R^16
        for (int t = 0; t < 16; t++)
        {
            R(C[i]);
        }
    }

    Assign(key[0], res[0]);
    Assign(key[1], res[1]);
    for (int i = 1; i <= 4; i++)
    {
        Assign(res[2 * i - 2], res[2 * i]);
        Assign(res[2 * i - 1], res[2 * i + 1]);
        for (int j = 0; j < 8; j++)
        {
            F(res[2 * i], res[2 * i + 1], C[8 * (i - 1) + j]);
        }
    }
}

// key 256 = 2*128= matrix 2*16 u8
void Take_key(char *path, u8 **key)
{
    FILE *key_in = fopen(path, "rb");
    if (!key_in)
    {
        printf("problem with file key_in\n");
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 15; j >= 0; j--)
        {
            int x = fscanf(key_in, "%2hhx", &key[i][j]);
        }
    }
}

// text *128=16 u8
void Take_text(char *path, u8 *text)
{
    FILE *in = fopen(path, "rb");
    if (!in)
    {
        printf("problem with file key_in\n");
        return;
    }
    for (int i = 15; i >= 0; i--)
    {
        int x = fscanf(in, "%2hhx", &text[i]);
    }
    fclose(in);
}

void Encrypt(u8 *a, u8 **K)
{
    for (int i = 0; i < 9; i++)
    {
        // LSX(K[i])  X->S->L
        X(a, K[i]);
        S(a);
        // L = R^16
        for (int t = 0; t < 16; t++)
        {
            R(a);
        }
    }
    X(a, K[9]);
}

void Decrypt(u8 *a, u8 **K)
{
    X(a, K[9]);
    for (int i = 8; i >= 0; i--)
    {
        // X(K[i])S_1L_1    L_1->S_1->X
        // L_1 = R_1^16
        for (int i = 0; i < 16; i++)
        {
            R_1(a);
        }
        S_1(a);
        X(a, K[i]);
    }
}

int main()
{
    clock_t start, end;
    double time_use;
    // pi_1
    for (int i = 0; i < 256; i++)
    {
        pi_1[pi[i]] = i;
    }

    // poleFx
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            poleFx[i][j] = Mul_fx(i, j);
        }
    }

    //    255------128  127------0
    //       Key[0]       Key[1]
    u8 **key = new u8 *[2];
    key[0] = new u8[16];
    key[1] = new u8[16];
    char path[20] = "key.txt";
    Take_key(path, key);
    printf("key:\n");
    Print_128bit(key[0]);
    Print_128bit(key[1]);

    // Deployment_key = K1.. K10 (128 bit)
    u8 **K = new u8 *[10];
    for (int i = 0; i < 10; i++)
    {
        K[i] = new u8[16];
    }
    Deployment_key(K, key);
    printf("\nK[ ]");
    for (int i = 0; i < 10; i++)
    {
        printf("\n  %d :  ", i);
        Print_128bit(K[i]);
    }

    u8 *text = new u8[16];
    char path_text[20] = "text.txt";
    Take_text(path_text, text);
    printf("\n\ntext:           ");
    Print_128bit(text);

    // encrypt
    printf("\nencrypt text:   ");
    //////////////////////////////////////////////////
    start = clock();
    //for (int i = 0; i < 1000000; i++)
    {
        Encrypt(text, K);
    }
    // Encrypt(text, K);
    end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;

    Print_128bit(text);
    cout << endl
         << "times: " << time_use << endl;

    // decrypt
    printf("\ndecrypt text:   ");
    Decrypt(text, K);
    Print_128bit(text);
    printf("\n");

    cout<<sizeof(int_fast8_t)<<endl;
    cout<<sizeof(uint8_t)<<endl;
}