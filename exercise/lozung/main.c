#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void setK(char Ka[100], int a, int b, char *key)
{
    int K[26];
    for (int i = 0; i < 26; i++)
        K[i] = -1;
    int l = strlen(key);
    int c[10];
    for (int i = 0; i < 10; i++)
    {
        c[i] = i;
    }
    c[a] = 8;
    c[b] = 9;
    c[8] = a;
    c[9] = b;

    for (int i = 0; i < l; i++)
    {
        if (i == a)
        {
            K[key[i] - 'A'] = 8;
        }
        else if (i == b)
        {
            K[key[i] - 'A'] = 9;
        }
        else
            K[key[i] - 'A'] = i;
        // printf("%C-%d, ", key[i], K[key[i] - 'A']);
    }

    int i = 0, count = 0;
    while (count < 10)
    {
        // printf("k= %d\n", K[i]);
        if (K[i] == -1)
        {
            K[i] = a * 10 + c[count];
            count++;
        }
        i++;
    }
    while (i < 26)
    {
        if (K[i] == -1)
        {
            K[i] = b * 10 + c[count % 10];
            count++;
        }
        i++;
    }

    for (i = 0; i < 26; i++)
    {
        Ka[K[i]] = 'A' + i;
    }
}

void makeTask(char *key, char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    char ct[10000];
    int a, b;
    fgets(ct, 1000, file);
    fgets(ct, 5, file);
    a = ct[0] - '0';
    b = ct[1] - '0';
    printf("%s %d,%d\n", ct, a, b);
    fgets(ct, 10000, file);
    fclose(file);

    char fileOut[9];
    memcpy(fileOut, filePath + 11, 4);
    memcpy(fileOut + 4, ".psw", 5);
    char out[6];
    memcpy(out, filePath + 11, 4);
    out[4] = ' ';

    file = fopen(fileOut, "wb");
    fputs(out, file);

    int length = strlen(ct);
    printf("%d\n", length);
    char K[100] = {0};
    setK(K, a, b, key);

    char pt[10000];
    int i = 0;
    int count = 0;
    for (; i < length;)
    {
        if (((ct[i] - '0') != a) && ((ct[i] - '0') != b))
        {
            printf("%c", K[ct[i] - '0']);
            pt[count] = K[ct[i] - '0'];
            i++;
        }
        else
        {
            printf("%c", K[(ct[i] - '0') * 10 + (ct[i + 1] - '0')]);
            pt[count] = K[(ct[i] - '0') * 10 + (ct[i + 1] - '0')];
            i = i + 2;
        }
        count++;
    }
    fputs(pt + count - 20, file);
    fclose(file);
    printf("\n%s\n%d\n", pt + count - 20, count);

    // printf("\nhello\n");
    // for (int i = 0; i < count; i++)
    // {
    //     if (pt[i]==(char)0)
    //     {
    //         printf("i= %d",i);
    //     }
}
int main()
{
    makeTask("TWISTER", "1207081514_6358.ktg");
}
