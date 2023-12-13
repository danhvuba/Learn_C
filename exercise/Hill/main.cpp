#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include "matrix.h"

using namespace std;

string Decryption(string src, int **K)
{
    string res = "";
    int len = src.length();
    uint8_t ct[len];
    int i = 0;
    for (i = 0; i < len; i++)
    {
        ct[i] = (int)src[i] - 97;
    }

    int a, b, c;
    for (i = 0; i < len; i = i + 3)
    {
        a = (ct[0 + i] * K[0][0] + ct[1 + i] * K[1][0] + ct[2 + i] * K[2][0]) % 26;
        b = (ct[0 + i] * K[0][1] + ct[1 + i] * K[1][1] + ct[2 + i] * K[2][1]) % 26;
        c = (ct[0 + i] * K[0][2] + ct[1 + i] * K[1][2] + ct[2 + i] * K[2][2]) % 26;
        ct[0 + i] = a;
        ct[1 + i] = b;
        ct[2 + i] = c;
    }

    for (i = 0; i < len; i++)
    {
        res += (char)(ct[i] + 97);
    }
    return res;
}

float Function(string str, float *bigram)
{
    float f[26 * 26] = {0};

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
        {
            string x = "";
            x = x + (char)(97 + i) + char(97 + j);
            int pos = 0;
            while ((pos = str.find(x, pos)) != string::npos)
            {
                if (pos % 2 == 0)
                    f[26 * i + j]++;
                pos += x.length();
            }
            f[26 * i + j] = f[26 * i + j] * 2 / str.length();
        }

    float s = 0;
    for (int i = 0; i < (26 * 26); i++)
    {
        float x = f[i] - bigram[i];
        if (x > 0)
        {
            s = s + x;
        }
        else
            s = s - x;
    }
    return s;
}

int main()
{
    float delta = 2;
    FILE *file;
    file = fopen("bigram.txt", "r");
    if (file == NULL)
        return -1;
    float f[676];
    for (int i = 0; i < 676; i++)
    {
        fscanf(file, "%f", f + i);
    }
    fclose(file);

    // read text
    ////////////////////////////////////////////////////////
    char *file_path = (char *)"1207081514_6362.ktg";
    file = fopen(file_path, "r");
    if (file == NULL)
        return -1;
    fseek(file, 0L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);
    uint8_t *buff = (uint8_t *)malloc(length);
    int c = 0;
    for (int i = 0; i < length; i++)
    {
        fscanf(file, "%c", buff + i);
        if (buff[i] == (char)0x0a)
        {
            c = i;
        }
    }
    fclose(file);
    c = c + 5;
    int key[3];
    key[0] = ((buff[c - 4] - '0') * 10 + (buff[c - 3] - '0'));
    key[1] = buff[c - 2] - 97;
    key[2] = buff[c - 1] - 97;
    printf("%d  %d  %d  %d  %d\n", key[0], key[1], key[2], key[3], key[4]);

    string ct = "";
    for (; c < length - 2; c = c + 2)
    {
        ct = ct + (char)(((buff[c] - '0') * 10 + (buff[c + 1] - '0')) + 97);
    }
    cout << "length " << ct.length() << endl;

    Matrix K(3, 26);
    K.Mtr[0] = new int[3]{1, 0, 0};
    K.Mtr[1] = new int[3]{0, 1, 0};
    K.Mtr[2] = new int[3]{0, 0, 1};

    string pt;

    for (int i1 = 0; i1 < 3; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            for (int i3 = 0; i3 < 3; i3++)
                for (int i4 = 0; i4 < 3; i4++)
                    for (int i5 = 0; i5 < 3; i5++)
                        for (int i6 = 0; i6 < 3; i6++)
                        {
                            K.Mtr[0][0] = key[i1];
                            K.Mtr[0][1] = key[i2];
                            K.Mtr[0][2] = key[i3];
                            K.Mtr[1][1] = key[i4];
                            K.Mtr[1][2] = key[i5];
                            K.Mtr[2][2] = key[i6];

                            Matrix K1(K.Inverse_matrix());
                            pt = Decryption(ct, K1.Mtr);
                            // if (Is_Text(pt))
                            {
                                float del = Function(pt, f);
                                // cout << del << endl;
                                if (del < delta)
                                {
                                    delta = del;
                                    cout << pt << endl
                                         << endl;
                                    K.Print_matrix();
                                }
                            }
                        }

    // float del = Function(pt, f);
    cout << delta << endl;
}