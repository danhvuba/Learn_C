#include <iostream>

using namespace std;

#define File_key "key.txt"
#define File_in "in.txt"
#define File_out "out.txt"

#define Shift_left_11(x) ((x >> 21) ^ ((((x >> 21) << 21) ^ x) << 11))

const int n[8][16] = {{12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
                      {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
                      {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
                      {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
                      {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
                      {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
                      {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
                      {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2}};

uint32_t Function_t(uint32_t a)
{
    uint32_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        res = res ^ (n[i][(a >> (4 * i)) & 15] << (4 * i));
    }
    return res;
}

uint64_t Encrypt(uint64_t a, uint32_t *Key)
{
    uint32_t l = a >> 32;
    uint32_t r = ((a >> 32) << 32) ^ a;
    for (int i = 0; i < 32; i++)
    {
        uint32_t g = r;
        r = l ^ (Shift_left_11(Function_t(r + Key[i])));
        l = g;
    }
    uint64_t res = r;
    res = (res << 32) ^ l;
    return res;
}

uint64_t Decrypt(uint64_t a, uint32_t *Key)
{
    uint32_t l = a >> 32;
    uint32_t r = ((a >> 32) << 32) ^ a;

    for (int i = 0; i < 32; i++)
    {
        uint32_t g = r;
        r = l ^ (Shift_left_11(Function_t(r + Key[31 - i])));
        l = g;
    }
    uint64_t res = r;
    res = (res << 32) ^ l;
    return res;
}

void Take_text(char *name, uint64_t *&text, int &length)
{
    FILE *in = fopen(name, "rb");
    // open file in
    if (!in)
    {
        printf("problem with file in\n");
        system("pause");
        return;
    }
    if (fscanf(in, "%16lx", &text[0]) == EOF)
    {
        printf("empty\n");
        return;
    }
    length++;
    uint64_t x;
    while (fscanf(in, "%16lx", &x) != EOF)
    //for (int i = 0; i < 2; i++)
    {
        length++;
        cout << length - 1 << endl;
        text = (uint64_t *)realloc(text, length * sizeof(uint64_t));
        text[length - 1] = x;
    }
    fclose(in);
}

uint32_t *Take_key(char *name)
{
    uint32_t *K = new uint32_t[8];
    FILE *key_in = fopen(name, "rb");
    if (!key_in)
    {
        printf("problem with file key_in\n");
        system("pause");
        return NULL;
    }
    for (int i = 0; i < 8; i++)
    {
        fscanf(key_in, "%8x", &K[i]);
    }
    return K;
}

uint32_t *Make_key(uint32_t *K)
{
    uint32_t *Key = new uint32_t[32];
    for (int i = 0; i < 24; i++)
    {
        Key[i] = K[i % 8];
    }
    for (int i = 0; i < 8; i++)
    {
        Key[24 + i] = K[7 - i];
    }
    return Key;
}

int main()
{
    // text
    char file_in[20] = File_in;
    uint64_t *text = (uint64_t *)malloc(1 * sizeof(uint64_t));
    int length = 0;
    Take_text(file_in, text, length);
    printf("text:          ");
    for (int i = 0; i < length; i++)
    {
        printf("%016lx  ", text[i]);
    }

    // key
    char file_key[20] = File_key;
    uint32_t *K = Take_key(file_key);
    printf("\n\nkey:           ");
    for (int i = 0; i < 8; i++)
    {
        printf("%08x", K[i]);
    }
    uint32_t *Key = Make_key(K);

    // cipher_text
    uint64_t *cipher_text = new uint64_t[length];
    printf("\n\ncipher text:   ");
    for (int i = 0; i < length; i++)
    {
        cipher_text[i] = Encrypt(text[i], Key);
        printf("%016lx  ", cipher_text[i]);
    }

    // Decrypt
    uint64_t *decrypt_text = new uint64_t[length];
    printf("\n\ndecrypt text:  ");
    for (int i = 0; i < length; i++)
    {
        decrypt_text[i] = Decrypt(cipher_text[i], Key);
        printf("%016lx  ", decrypt_text[i]);
    }
    printf("\n");

    ///////////////////////
    // open file out
    // FILE *out;
    // if (fopen_s(&out, File_out, "a") != 0)
    // {
    //     printf("problem with file out\n");
    //     system("pause");
    //     return 1;
    // }
    // fprintf(out,"cipher text:   ");
    // for (int i = 0; i < length; i++)
    // {
    //     fprintf(out,"%llx  ", cipher_text[i]);
    // }
    // fprintf(out,"\n\ndecrypt text:  ");
    // for (int i = 0; i < length; i++)
    // {
    //     fprintf(out,"%llx  ", decrypt_text[i]);
    // }
    // fclose(out);
    /////////////////
}