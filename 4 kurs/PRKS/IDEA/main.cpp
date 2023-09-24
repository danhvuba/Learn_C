#include <cstdio>
#include <cstdint>
#include <cstdlib>

#define whatIs(n) printf("Line %d: %s = %04x\n", __LINE__, #n, n)
#define TEST_FILE "test_idea.txt"

// Field mod 2^16+1
// "0" 1 ... 0xffff 0x10000
// ________________  0 - 2^16
// ^-1 = ^ (2^16)
uint16_t fieldMul(uint16_t x, uint16_t y)
{
    uint32_t a = (x == 0) ? 0x10000 : x;
    uint32_t b = (y == 0) ? 0x10000 : y;
    uint32_t res = 0;
    while (a != 0 && b != 0)
    {
        if (b & 1 != 0)
        {
            res += a;
            // mod 0x10001
            if (res > 0x10001)
                res -= 0x10001;
        }
        b = b >> 1;
        a = a << 1;
        if (a > 0x10001)
            a -= 0x10001;
    }
    if (res == 0)
    {
        printf("whatssssssssssssssssss\n");
    }
    // return uint16_t -> 2^16 = 0
    return res;
}

// in Field x ^ tmp
uint16_t fieldExp(uint16_t x, uint32_t tmp)
{
    uint16_t result = 1;
    while (tmp != 0)
    {
        if ((tmp & 1) != 0)
            result = fieldMul(result, x);
        tmp = tmp >> 1;
        x = fieldMul(x, x);
    }
    return result;
}

// key[52] --- 8*6 + 4
uint64_t IDEA(uint64_t text, uint16_t *key)
{
    uint16_t T[4];
    T[0] = text & 0xffff;
    T[1] = (text >> 16) & 0xffff;
    T[2] = (text >> 32) & 0xffff;
    T[3] = (text >> 48) & 0xffff;
    for (int i = 0; i < 8; i++)
    {
        T[0] = fieldMul(T[0], key[i * 6 + 3]);
        T[1] += key[i * 6 + 2];
        T[2] += key[i * 6 + 1];
        T[3] = fieldMul(T[3], key[i * 6 + 0]);

        uint16_t x1 = T[1] ^ T[3];
        uint16_t x2 = T[0] ^ T[2];
        x1 = fieldMul(x1, key[i * 6 + 4]);
        x2 += x1;
        x2 = fieldMul(x2, key[i * 6 + 5]);
        x1 += x2;

        T[0] ^= x1;
        uint16_t tmp = T[1] ^ x2;
        T[1] = T[2] ^ x1;
        T[2] = tmp;
        T[3] ^= x2;
    }
    T[0] = fieldMul(T[0], key[8 * 6 + 3]);
    uint16_t tmp = T[1] + key[8 * 6 + 1];
    T[1] = T[2] + key[8 * 6 + 2];
    T[2] = tmp;
    T[3] = fieldMul(T[3], key[8 * 6 + 0]);

    uint64_t result = T[3];
    result = (result << 16) ^ T[2];
    result = (result << 16) ^ T[1];
    result = (result << 16) ^ T[0];
    return result;
}

// 128 bit key <<< 25
void shiftKey_25(uint16_t *key)
{
    uint64_t x = 0, y = 0;
    // y-x
    for (int i = 0; i < 4; i++)
    {
        x = (x << 16) ^ key[i];
        y = (y << 16) ^ key[i + 4];
    }
    // 25 bit
    uint32_t bufferY = (y >> 39) & 0x1ffffff,
             bufferX = (x >> 39) & 0x1ffffff;
    x = (x << 25) ^ bufferY;
    y = (y << 25) ^ bufferX;
    for (int i = 0; i < 4; i++)
    {
        key[i] = (x >> (16 * i)) & 0xffff;
        key[i + 4] = (y >> (16 * i)) & 0xffff;
    }
}

// key 128 bit = 16* 8
void deploymentKeyEncrypt(uint16_t *&res, uint16_t *key)
{
    res = (uint16_t *)malloc(52 * sizeof(uint16_t));
    int index = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            res[index] = key[j];
            index++;
        }
        shiftKey_25(key);
    }
    // 4 last
    for (int i = 4; i < 8; i++)
    {
        res[index] = key[i];
        index++;
    }
}

uint16_t inverse(uint16_t x)
{
    return fieldExp(x, 0xffff);
}

uint16_t _element(uint16_t x)
{
    return (0x10000 - x);
}

void deploymentKeyDecrypt(uint16_t *&keyDecrypt, uint16_t *keyEncrypt)
{
    keyDecrypt = (uint16_t *)malloc(52 * sizeof(uint16_t));
    // Z1(9) Z2(9) Z3(9) Z4(9)
    keyDecrypt[0 * 6] = inverse(keyEncrypt[51 - 0 * 6 - 3]);
    keyDecrypt[0 * 6 + 1] = _element(keyEncrypt[51 - 0 * 6 - 2]);
    keyDecrypt[0 * 6 + 2] = _element(keyEncrypt[51 - 0 * 6 - 1]);
    keyDecrypt[0 * 6 + 3] = inverse(keyEncrypt[51 - 0 * 6]);
    // Z5(8) Z6(8)
    keyDecrypt[0 * 6 + 4] = keyEncrypt[51 - 0 * 6 - 5];
    keyDecrypt[0 * 6 + 5] = keyEncrypt[51 - 0 * 6 - 4];
    for (int i = 1; i < 8; i++)
    {
        // Z1(9) Z2(9) Z3(9) Z4(9)
        keyDecrypt[i * 6] = inverse(keyEncrypt[51 - i * 6 - 3]);
        // 3 - 2
        keyDecrypt[i * 6 + 1] = _element(keyEncrypt[51 - i * 6 - 1]);
        keyDecrypt[i * 6 + 2] = _element(keyEncrypt[51 - i * 6 - 2]);
        //
        keyDecrypt[i * 6 + 3] = inverse(keyEncrypt[51 - i * 6]);
        // Z5(8) Z6(8)
        keyDecrypt[i * 6 + 4] = keyEncrypt[51 - i * 6 - 5];
        keyDecrypt[i * 6 + 5] = keyEncrypt[51 - i * 6 - 4];
    }
    keyDecrypt[8 * 6] = inverse(keyEncrypt[51 - 8 * 6 - 3]);
    keyDecrypt[8 * 6 + 1] = _element(keyEncrypt[51 - 8 * 6 - 2]);
    keyDecrypt[8 * 6 + 2] = _element(keyEncrypt[51 - 8 * 6 - 1]);
    keyDecrypt[8 * 6 + 3] = inverse(keyEncrypt[51 - 8 * 6]);
}

void printKey(uint16_t *key)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%04x  ", key[i * 6 + j]);
        }
        printf("\n");
    }
    for (int j = 0; j < 4; j++)
    {
        printf("%04x  ", key[8 * 6 + j]);
    }
    printf("\n");
}

int main()
{
    FILE *test = fopen(TEST_FILE, "rb");
    uint64_t text;
    uint16_t *key = (uint16_t *)malloc(8 * sizeof(uint16_t));
    printf("Key = ");
    for (int i = 0; i < 8; i++)
    {
        fscanf(test, "%4hx", &key[7 - i]);
        printf("%4x", key[7 - i]);
    }
    fscanf(test, "%16lx", &text);
    printf("\nText = %16lx\n", text);
    fclose(test);

    uint16_t *keyEncrypt, *keyDecrypt;
    deploymentKeyEncrypt(keyEncrypt, key);
    //printKey(keyEncrypt);
    uint64_t c = IDEA(text, keyEncrypt);
    printf("cipher = %16lx\n", c);

    deploymentKeyDecrypt(keyDecrypt, keyEncrypt);
    //printKey(keyDecrypt);
    uint64_t t = IDEA(c, keyDecrypt);
    printf("text = %16lx\n", t);

    // test 
    c=text;
    int n=1000;
    for (int i = 0; i < n; i++)
    {
        c = IDEA(c, keyEncrypt);
    }
    printf("Iterated %d times = %16lx\n",n, c);
    
    return 0;
}