#ifndef HIVUS_INCLUDED
#define HIVUS_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <stdint.h>

using namespace std;

typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;

#define rl 1
#define rr 2
#define Takt 4
#define rotl(a) (((a >> 3) & 1) ^ (a << 1)) & 0xF
#define rotr(a) (((a >> 2) & 0x3) ^ (a << 2)) & 0xF
#define Rl(a) (a >> 4) & 0xF
#define Rr(a) a & 0xF

UINT32 crc32table[256] =
    {0x000000000, 0x077073096, 0x0EE0E612C, 0x0990951BA, 0x0076DC419, 0x0706AF48F, 0x0E963A535, 0x09E6495A3,
     0x00EDB8832, 0x079DCB8A4, 0x0E0D5E91E, 0x097D2D988, 0x009B64C2B, 0x07EB17CBD, 0x0E7B82D07, 0x090BF1D91,
     0x01DB71064, 0x06AB020F2, 0x0F3B97148, 0x084BE41DE, 0x01ADAD47D, 0x06DDDE4EB, 0x0F4D4B551, 0x083D385C7,
     0x0136C9856, 0x0646BA8C0, 0x0FD62F97A, 0x08A65C9EC, 0x014015C4F, 0x063066CD9, 0x0FA0F3D63, 0x08D080DF5,
     0x03B6E20C8, 0x04C69105E, 0x0D56041E4, 0x0A2677172, 0x03C03E4D1, 0x04B04D447, 0x0D20D85FD, 0x0A50AB56B,
     0x035B5A8FA, 0x042B2986C, 0x0DBBBC9D6, 0x0ACBCF940, 0x032D86CE3, 0x045DF5C75, 0x0DCD60DCF, 0x0ABD13D59,
     0x026D930AC, 0x051DE003A, 0x0C8D75180, 0x0BFD06116, 0x021B4F4B5, 0x056B3C423, 0x0CFBA9599, 0x0B8BDA50F,
     0x02802B89E, 0x05F058808, 0x0C60CD9B2, 0x0B10BE924, 0x02F6F7C87, 0x058684C11, 0x0C1611DAB, 0x0B6662D3D,
     0x076DC4190, 0x001DB7106, 0x098D220BC, 0x0EFD5102A, 0x071B18589, 0x006B6B51F, 0x09FBFE4A5, 0x0E8B8D433,
     0x07807C9A2, 0x00F00F934, 0x09609A88E, 0x0E10E9818, 0x07F6A0DBB, 0x0086D3D2D, 0x091646C97, 0x0E6635C01,
     0x06B6B51F4, 0x01C6C6162, 0x0856530D8, 0x0F262004E, 0x06C0695ED, 0x01B01A57B, 0x08208F4C1, 0x0F50FC457,
     0x065B0D9C6, 0x012B7E950, 0x08BBEB8EA, 0x0FCB9887C, 0x062DD1DDF, 0x015DA2D49, 0x08CD37CF3, 0x0FBD44C65,
     0x04DB26158, 0x03AB551CE, 0x0A3BC0074, 0x0D4BB30E2, 0x04ADFA541, 0x03DD895D7, 0x0A4D1C46D, 0x0D3D6F4FB,
     0x04369E96A, 0x0346ED9FC, 0x0AD678846, 0x0DA60B8D0, 0x044042D73, 0x033031DE5, 0x0AA0A4C5F, 0x0DD0D7CC9,
     0x05005713C, 0x0270241AA, 0x0BE0B1010, 0x0C90C2086, 0x05768B525, 0x0206F85B3, 0x0B966D409, 0x0CE61E49F,
     0x05EDEF90E, 0x029D9C998, 0x0B0D09822, 0x0C7D7A8B4, 0x059B33D17, 0x02EB40D81, 0x0B7BD5C3B, 0x0C0BA6CAD,
     0x0EDB88320, 0x09ABFB3B6, 0x003B6E20C, 0x074B1D29A, 0x0EAD54739, 0x09DD277AF, 0x004DB2615, 0x073DC1683,
     0x0E3630B12, 0x094643B84, 0x00D6D6A3E, 0x07A6A5AA8, 0x0E40ECF0B, 0x09309FF9D, 0x00A00AE27, 0x07D079EB1,
     0x0F00F9344, 0x08708A3D2, 0x01E01F268, 0x06906C2FE, 0x0F762575D, 0x0806567CB, 0x0196C3671, 0x06E6B06E7,
     0x0FED41B76, 0x089D32BE0, 0x010DA7A5A, 0x067DD4ACC, 0x0F9B9DF6F, 0x08EBEEFF9, 0x017B7BE43, 0x060B08ED5,
     0x0D6D6A3E8, 0x0A1D1937E, 0x038D8C2C4, 0x04FDFF252, 0x0D1BB67F1, 0x0A6BC5767, 0x03FB506DD, 0x048B2364B,
     0x0D80D2BDA, 0x0AF0A1B4C, 0x036034AF6, 0x041047A60, 0x0DF60EFC3, 0x0A867DF55, 0x0316E8EEF, 0x04669BE79,
     0x0CB61B38C, 0x0BC66831A, 0x0256FD2A0, 0x05268E236, 0x0CC0C7795, 0x0BB0B4703, 0x0220216B9, 0x05505262F,
     0x0C5BA3BBE, 0x0B2BD0B28, 0x02BB45A92, 0x05CB36A04, 0x0C2D7FFA7, 0x0B5D0CF31, 0x02CD99E8B, 0x05BDEAE1D,
     0x09B64C2B0, 0x0EC63F226, 0x0756AA39C, 0x0026D930A, 0x09C0906A9, 0x0EB0E363F, 0x072076785, 0x005005713,
     0x095BF4A82, 0x0E2B87A14, 0x07BB12BAE, 0x00CB61B38, 0x092D28E9B, 0x0E5D5BE0D, 0x07CDCEFB7, 0x00BDBDF21,
     0x086D3D2D4, 0x0F1D4E242, 0x068DDB3F8, 0x01FDA836E, 0x081BE16CD, 0x0F6B9265B, 0x06FB077E1, 0x018B74777,
     0x088085AE6, 0x0FF0F6A70, 0x066063BCA, 0x011010B5C, 0x08F659EFF, 0x0F862AE69, 0x0616BFFD3, 0x0166CCF45,
     0x0A00AE278, 0x0D70DD2EE, 0x04E048354, 0x03903B3C2, 0x0A7672661, 0x0D06016F7, 0x04969474D, 0x03E6E77DB,
     0x0AED16A4A, 0x0D9D65ADC, 0x040DF0B66, 0x037D83BF0, 0x0A9BCAE53, 0x0DEBB9EC5, 0x047B2CF7F, 0x030B5FFE9,
     0x0BDBDF21C, 0x0CABAC28A, 0x053B39330, 0x024B4A3A6, 0x0BAD03605, 0x0CDD70693, 0x054DE5729, 0x023D967BF,
     0x0B3667A2E, 0x0C4614AB8, 0x05D681B02, 0x02A6F2B94, 0x0B40BBE37, 0x0C30C8EA1, 0x05A05DF1B, 0x02D02EF8D};

UINT32 crc32;

UINT8 F(UINT8 *x, const UINT8 *k)
{
    UINT8 x0, x1, k0, k1;
    x0 = Rl(*x);
    x1 = Rr(*x);
    k0 = Rl(*k);
    k1 = Rr(*k);
    x0 += x1;
    x0 = rotl(x0);
    x1 += k1;
    x1 = rotr(x1);
    x0 += k0;
    x1 += x0;
    return ((x0 << 4) ^ x1) & 0xF;
}

void cryptblock(UINT8 *X0, UINT8 *X1, const UINT8 *RK)
{
    UINT8 Y;
    // printf("       %02x%02x\n",*X0,*X1);
    for (unsigned char i = 0; i < 9; ++i)
    {
        Y = *X0;
        *X0 = F(X0, &RK[i]);
        *X0 = (*X0) ^ (*X1);
        *X1 = Y;
        // printf("%d  %02x  %02x%02x\n",i,RK[i],*X0,*X1);
    }
    Y = *X0;
    *X1 ^= F(X0, &RK[9]);
    *X0 = Y;
    // printf("%d  %02x  %02x%02x\n",9,RK[9],*X0,*X1);
}

UINT32 Crc32comp(unsigned char *buf, size_t len)
{
    UINT32 crc_table[256];
    UINT32 crc;
    int i, j;

    for (i = 0; i < 256; i++)
    {
        crc = i;
        for (j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

        crc_table[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
}

void crypt_cmd(const char *fot_, const char *fst_, const char *fkey_)
{
    UINT8 K[10];
    UINT8 RK[10];
    UINT8 iRK[10];

    FILE *fot = NULL;
    FILE *fst = NULL;
    FILE *fkey = NULL;

    fot = fopen(fot_, "rb");
    fst = fopen(fst_, "wb");
    fkey = fopen(fkey_, "rb");

    if ((fkey == NULL) || (fot == NULL) || (fst == NULL))
    {
        printf("File KEY||OT||ST open error!\n");
        return;
    }

    // ���������� �����
    UINT8 temp;
    for (unsigned char i = 0; i < 5; ++i)
    {
        fread(&temp, 1, 1, fkey);
        K[2 * i] = temp >> 4;
        K[2 * i + 1] = temp & 0xf;
    }
    for (unsigned char i = 0; i < 10; ++i)
        RK[i] = (K[i] << 4) ^ (K[(i + 1) % 10]);
    for (unsigned char i = 0; i < 10; ++i)
        iRK[i] = RK[9 - i];
    fclose(fkey);
    // ��������� ��������
    UINT8 B0, B1;
    for (unsigned char i = 0; i < Takt; ++i)
    {
        B0 = (rand() % 0xff) + 1;
        B1 = (rand() % 0xff) + 1;
        fwrite(&B0, 1, 1, fst);
        fwrite(&B1, 1, 1, fst);
        cryptblock(&B0, &B1, RK);
        fwrite(&B0, 1, 1, fst);
        fwrite(&B1, 1, 1, fst);
        cryptblock(&B0, &B1, iRK);
        fwrite(&B0, 1, 1, fst);
        fwrite(&B1, 1, 1, fst);
    }

    // ���������� ��
    UINT8 Check;

    crc32 = 0xFFFFFFFF;

    while (!feof(fot))
    { // �� ����� �����
        Check = 0;
        if (fread(&B0, 1, 1, fot) == 1)
            Check = 0xf0;
        if (fread(&B1, 1, 1, fot) == 1)
            Check = 0xff;
        switch (Check)
        {
        case 0xff: // ������ ����
            crc32 = crc32table[(crc32 ^ B0) & 0xFF] ^ (crc32 >> 8);
            crc32 = crc32table[(crc32 ^ B1) & 0xFF] ^ (crc32 >> 8);
            cryptblock(&B0, &B1, RK);
            fwrite(&B0, 1, 1, fst);
            fwrite(&B1, 1, 1, fst);
            break;
        case 0xf0: // �������� ����
            B1 = 0x00;
            crc32 = crc32table[(crc32 ^ B0) & 0xFF] ^ (crc32 >> 8);
            crc32 = crc32table[(crc32 ^ B1) & 0xFF] ^ (crc32 >> 8);
            cryptblock(&B0, &B1, RK);
            fwrite(&B0, 1, 1, fst);
            fwrite(&B1, 1, 1, fst);
            B0 = 0x00;
            B1 = 0x00;
            crc32 = crc32table[(crc32 ^ B0) & 0xFF] ^ (crc32 >> 8);
            crc32 = crc32table[(crc32 ^ B1) & 0xFF] ^ (crc32 >> 8);
            cryptblock(&B0, &B1, RK);
            fwrite(&B0, 1, 1, fst);
            fwrite(&B1, 1, 1, fst);
            break;
        case 0x00: // ������ ���� ��� ������
            B0 = 0xff;
            B1 = 0xff;
            crc32 = crc32table[(crc32 ^ B0) & 0xFF] ^ (crc32 >> 8);
            crc32 = crc32table[(crc32 ^ B1) & 0xFF] ^ (crc32 >> 8);
            cryptblock(&B0, &B1, RK);
            fwrite(&B0, 1, 1, fst);
            fwrite(&B1, 1, 1, fst);
            break;
        }
    } // �� ����� �����
    //

    crc32 ^= 0xFFFFFFFF;

    B0 = (crc32 >> 24) & 0xff;
    B1 = (crc32 >> 16) & 0xff;
    cryptblock(&B0, &B1, RK);
    fwrite(&B0, 1, 1, fst);
    fwrite(&B1, 1, 1, fst);
    B0 = (crc32 >> 8) & 0xff;
    B1 = (crc32) & 0xff;
    cryptblock(&B0, &B1, RK);
    fwrite(&B0, 1, 1, fst);
    fwrite(&B1, 1, 1, fst);

    fclose(fot);
    fclose(fst);

    return;
}

UINT8 uncrypt_cmd(const char *fot_, const char *fst_, const char *fkey_)
{
    UINT8 K[10];
    UINT8 RK[10];
    UINT8 iRK[10];

    FILE *fot = NULL;
    FILE *fst = NULL;
    FILE *fkey = NULL;

    fst = fopen(fst_, "rb");
    fkey = fopen(fkey_, "rb");
    //////////// clear first line
    char val[1000];
    fgets(val, 1000, fst);

    if (fst == NULL)
    {
        printf("File ST open error!\n");
        return 0;
    }
    if (fkey == NULL)
    {
        printf("File KEY for uncrypt open error!\n");
        return 0;
    }

    // ���������� �����
    UINT8 temp;
    for (unsigned char i = 0; i < 5; ++i)
    {
        fread(&temp, 1, 1, fkey);
        K[2 * i] = temp >> 4;
        K[2 * i + 1] = temp & 0xf;
    }
    fclose(fkey);
    for (unsigned char i = 0; i < 10; ++i)
        RK[i] = (K[i] << 4) ^ (K[(i + 1) % 10]);
    for (unsigned char i = 0; i < 10; ++i)
        iRK[i] = RK[9 - i];

    UINT32 VolOT = 0;
    UINT8 B0, B1, B0_, B1_, B0__, B1__;

    while (!feof(fst))
    {
        if (fread(&B0, 1, 1, fst) == 1)
            ++VolOT;
    }

    if (VolOT < 6 * Takt + 2 + 4)
    {
        printf("ST Error!\n");
        fclose(fst);
        return 0;
    }
    if (VolOT == 6 * Takt + 2 + 4)
    {
        fclose(fst);
        return 0;
    }
    VolOT -= 6 * Takt + 2 + 4;
    if ((VolOT & 1) == 1)
    {
        printf("ST Error!\n");
        fclose(fst);
        return 0;
    }
    VolOT >>= 1;
    rewind(fst);
    //////////// clear first line
    fgets(val, 1000, fst);

    // ��������� ��������
    for (unsigned char i = 0; i < Takt; ++i)
    {
        if ((fread(&B0, 1, 1, fst) != 1) || (fread(&B1, 1, 1, fst) != 1))
        {
            printf("ST read Error!\n");
            fclose(fst);
            return 0;
        }
        if ((fread(&B0_, 1, 1, fst) != 1) || (fread(&B1_, 1, 1, fst) != 1))
        {
            printf("ST read Error!\n");
            fclose(fst);
            return 0;
        }
        if ((fread(&B0__, 1, 1, fst) != 1) || (fread(&B1__, 1, 1, fst) != 1))
        {
            printf("ST read Error!\n");
            fclose(fst);
            return 0;
        }
        if ((B0 != B0__) || (B1 != B1__))
        {
            printf("ST format Error!\n");
            fclose(fst);
            return 0;
        }
        cryptblock(&B0, &B1, RK);
        if ((B0 != B0_) || (B1 != B1_))
        {
            printf("Key %02x%02x%02x%02x%02x error\n", iRK[9], iRK[7], iRK[5], iRK[3], iRK[1]);
            fclose(fst);
            return 0;
        }
        cryptblock(&B0, &B1, iRK);
        if ((B0 != B0__) || (B1 != B1__))
        {
            printf("Key %02x%02x%02x%02x%02x error\n", iRK[9], iRK[7], iRK[5], iRK[3], iRK[1]);
            fclose(fst);
            return 0;
        }
    }

    crc32 = 0xFFFFFFFF;
    fot = fopen(fot_, "wb");
    if (fot == NULL)
    {
        printf("File OT open error!\n");
        return 0;
    }
    // ������������� ��
    for (UINT32 i = 0; i < VolOT - 1; ++i)
    {
        fread(&B0, 1, 1, fst);
        fread(&B1, 1, 1, fst);
        cryptblock(&B0, &B1, iRK);
        crc32 = crc32table[(crc32 ^ B0) & 0xFF] ^ (crc32 >> 8);
        crc32 = crc32table[(crc32 ^ B1) & 0xFF] ^ (crc32 >> 8);
        fwrite(&B0, 1, 1, fot);
        fwrite(&B1, 1, 1, fot);
    }
    fread(&B0, 1, 1, fst);
    fread(&B1, 1, 1, fst);
    cryptblock(&B0, &B1, iRK);
    crc32 = crc32table[(crc32 ^ B0) & 0xFF] ^ (crc32 >> 8);
    crc32 = crc32table[(crc32 ^ B1) & 0xFF] ^ (crc32 >> 8);
    fread(&B0_, 1, 1, fst);
    fread(&B1_, 1, 1, fst);
    cryptblock(&B0_, &B1_, iRK);
    crc32 = crc32table[(crc32 ^ B0_) & 0xFF] ^ (crc32 >> 8);
    crc32 = crc32table[(crc32 ^ B1_) & 0xFF] ^ (crc32 >> 8);
    crc32 ^= 0xFFFFFFFF;
    if ((B0_ == 0x00) && (B0_ == 0x00))
    {
        fwrite(&B0, 1, 1, fot);
    }
    if ((B0_ == 0xff) && (B0_ == 0xff))
    {
        fwrite(&B0, 1, 1, fot);
        fwrite(&B1, 1, 1, fot);
    }

    UINT32 crc32_ = 0;
    for (UINT8 i = 0; i < 2; ++i)
    {
        fread(&B0, 1, 1, fst);
        fread(&B1, 1, 1, fst);
        cryptblock(&B0, &B1, iRK);
        crc32_ <<= 16;
        crc32_ ^= (B0 << 8) ^ B1;
    }

    fclose(fot);
    fclose(fst);
    if (crc32 != crc32_)
    { // printf("crc32 OT ERROR!\n");
        return 0;
    }
    return 1;
}

#endif // HIVUS_INCLUDED
