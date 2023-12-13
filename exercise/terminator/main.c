#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

void make(char *key, char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    assert(!(file == NULL));
    char ct[10000];
    fgets(ct, 10000, file);
    fgets(ct, 5, file);
    fgets(ct, 10000, file);
    fclose(file);
    char out[9];
    char tlg[6];
    memcpy(out, filePath + 11, 4);
    memcpy(tlg, filePath + 11, 4);
    memcpy(out + 4, ".psw", 5);
    tlg[4] = ' ';

    file = fopen(out, "wb");
    char *val = (char *)("6417 ");
    fputs(tlg, file);
    int length = strlen(ct);

    char res[10000];
    int c = 0;
    for (int i = 0; i < length; i += 2)
    {
        res[c] = ((key[ct[i + 1] - '0'] + ct[i] - '0' - 'a') % 26 + 'A');
        c++;
    }
    printf("%s\n", res);
    printf("%s", res + c - 20);
    fputs(res + c - 20, file);
    fclose(file);
}

int main()
{
    make("complexity", "1207081514_6403.ktg");
}
