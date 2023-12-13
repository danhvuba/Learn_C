#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef unsigned char u8;
typedef unsigned int  u32;

/* Read data from Vigenere encrypted file */
char str_to_char(char *str)
{
    return 'a' + (str[0] - '0') * 10 + (str[1] - '0');
}

void print_vigenere_data(char *fileName)
{
    FILE *fptr = fopen(fileName, "r");

    char *str = (char *)malloc(10000 * sizeof(char));
    // str[0] = '\0';
    fgets(str, 9999, fptr);
    fgets(str, 9999, fptr);

    char *ct = str + 4;
    // printf("%s\n", ct);

    for (int i = 0; i < strlen(ct) / 2; ++i)
        printf("%c", str_to_char(ct + 2 * i));
    printf("\n");

    free(str);
    fclose(fptr);
}



void transposition_solver(char *fileName,char *fN)
{
    // Read data from file
    FILE *fptr = fopen(fileName, "r");

    char *str = (char *)malloc(10000 * sizeof(char));
    fgets(str, 9999, fptr);
    fgets(str, 9999, fptr);

    char *ct = str + 4;
    u32 sz = strlen(ct) / 2, tmp;

    // create key from data, example: 15hh
    u8 n1 = (str[0] - '0') * 10 + (str[1] - '0'), n2 = str[2] - 'a' + 1, n3 = str[3] - 'a' + 1;

    assert(sz % n1 == 0);

    u32 *  p = (u32 *)malloc(n1 * sizeof(u32));     // permutation
    // u32 *ivp = (u32 *)malloc(n1 * sizeof(u32));     // inverse of p

    /* create key and find inverse */
    for (int i = 0; i < n1; ++i)
    {
        tmp = (n3 + (n2 - 1) * i) % n1;
        p[i] = (tmp == 0)? n1 : tmp;
    }

    // for (int i = 0; i < n1; ++i)
    //     printf("%2d ", p[i]);
    // printf("\n");

    // for (int i = 0; i < n1; ++i)
    //     ivp[p[i] - 1] = i + 1;

    // for (int i = 0; i < n1; ++i)
    //     printf("%2d ", ivp[i]);
    // printf("\n");

    char *pt = (char *)malloc(10000 * sizeof(char));
    for (int i = 0; i < sz; ++i)
        pt[i] = str_to_char(ct + 2 * i);

    FILE *fct=fopen(fN,"wb");
    // print output in screen
    for (int i = 0; i < sz / n1; ++i)
    {
        for (int j = 0; j < n1; ++j)
            //printf("%c", (pt[n1 * i + p[j] - 1]));
            fputc((pt[n1 * i + p[j] - 1]+'A'-'a'),fct);
    }
    printf("%s\n",fN);

    free(pt);
    // free(ivp);
    free(p);
    free(str);
    fclose(fptr);
}
int main()
{   
    transposition_solver("1207081514_6357.ktg","6357.psw");

    return 0;
}