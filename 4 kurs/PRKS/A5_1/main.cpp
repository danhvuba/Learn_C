#include <cstdio>
#include <cstdint>
#include <cstdlib>

#define Fuction(x, y, z) (y * z ^ x * z ^ x * y)
#define Bit(x, n) ((x >> n) & 1)

// key 8* uint8_t
// res 14 * uint8_t
void A5Function(uint8_t *res1, uint8_t *res2, uint8_t *key, uint32_t frame)
{
     // 19 22 23
     uint32_t R1 = 0, R2 = 0, R3 = 0;

     for (int i = 0; i < 64; i++)
     {
          // clock all three
          R1 = (R1 << 1) & 0x7ffff ^
               ((R1 >> 18) ^ (R1 >> 17) ^ (R1 >> 16) ^ (R1 >> 13)) & 1;
          R2 = (R2 << 1) & 0x3fffff ^
               ((R2 >> 21) ^ (R2 >> 20)) & 1;
          R3 = (R3 << 1) & 0x7fffff ^
               ((R3 >> 22) ^ (R3 >> 21) ^ (R3 >> 20) ^ (R3 >> 7)) & 1;
          uint8_t keyBit = (key[i / 8] >> (i & 7)) & 0x1;
          R1 ^= keyBit;
          R2 ^= keyBit;
          R3 ^= keyBit;
     }

     for (int i = 0; i < 22; i++)
     {
          // clock all three
          R1 = (R1 << 1) & 0x7ffff ^
               ((R1 >> 18) ^ (R1 >> 17) ^ (R1 >> 16) ^ (R1 >> 13)) & 1;
          R2 = (R2 << 1) & 0x3fffff ^
               ((R2 >> 21) ^ (R2 >> 20)) & 1;
          R3 = (R3 << 1) & 0x7fffff ^
               ((R3 >> 22) ^ (R3 >> 21) ^ (R3 >> 20) ^ (R3 >> 7)) & 1;
          uint8_t frameBit = (frame >> i) & 0x1;
          R1 ^= frameBit;
          R2 ^= frameBit;
          R3 ^= frameBit;
     }

     for (int i = 0; i < 100; i++)
     {
          // clock by majority bit
          bool f = Fuction(Bit(R1, 8), Bit(R2, 10), Bit(R3, 10));
          R1 = (R1 << (!(Bit(R1, 8) ^ f))) & 0x7ffff ^
               ((R1 >> 18) ^ (R1 >> 17) ^ (R1 >> 16) ^ (R1 >> 13)) & (!(Bit(R1, 8) ^ f));
          R2 = (R2 << (!(Bit(R2, 10) ^ f))) & 0x3fffff ^
               ((R2 >> 21) ^ (R2 >> 20)) & (!(Bit(R2, 10) ^ f));
          R3 = (R3 << (!(Bit(R3, 10) ^ f))) & 0x7fffff ^
               ((R3 >> 22) ^ (R3 >> 21) ^ (R3 >> 20) ^ (R3 >> 7)) & (!(Bit(R3, 10) ^ f));
     }

     // 114 bit result
     for (int i = 0; i < 114; i++)
     {
          // clock by majority bit
          bool f = Fuction(Bit(R1, 8), Bit(R2, 10), Bit(R3, 10));
          R1 = (R1 << (!(Bit(R1, 8) ^ f))) & 0x7ffff ^
               ((R1 >> 18) ^ (R1 >> 17) ^ (R1 >> 16) ^ (R1 >> 13)) & (!(Bit(R1, 8) ^ f));
          R2 = (R2 << (!(Bit(R2, 10) ^ f))) & 0x3fffff ^
               ((R2 >> 21) ^ (R2 >> 20)) & (!(Bit(R2, 10) ^ f));
          R3 = (R3 << (!(Bit(R3, 10) ^ f))) & 0x7fffff ^
               ((R3 >> 22) ^ (R3 >> 21) ^ (R3 >> 20) ^ (R3 >> 7)) & (!(Bit(R3, 10) ^ f));
          // result
          res1[i / 8] ^= (((R1 >> 18) & 0x1) ^ ((R2 >> 21) & 0x1) ^ ((R3 >> 22) & 0x1)) << (7 - (i & 7));
     }

     // 114 bit next
     for (int i = 0; i < 114; i++)
     {
          // clock by majority bit
          bool f = Fuction(Bit(R1, 8), Bit(R2, 10), Bit(R3, 10));
          R1 = (R1 << (!(Bit(R1, 8) ^ f))) & 0x7ffff ^
               ((R1 >> 18) ^ (R1 >> 17) ^ (R1 >> 16) ^ (R1 >> 13)) & (!(Bit(R1, 8) ^ f));
          R2 = (R2 << (!(Bit(R2, 10) ^ f))) & 0x3fffff ^
               ((R2 >> 21) ^ (R2 >> 20)) & (!(Bit(R2, 10) ^ f));
          R3 = (R3 << (!(Bit(R3, 10) ^ f))) & 0x7fffff ^
               ((R3 >> 22) ^ (R3 >> 21) ^ (R3 >> 20) ^ (R3 >> 7)) & (!(Bit(R3, 10) ^ f));
          // result
          res2[i / 8] ^= (((R1 >> 18) & 0x1) ^ ((R2 >> 21) & 0x1) ^ ((R3 >> 22) & 0x1)) << (7 - (i & 7));
     }
}

int main()
{
     uint8_t *result_1 = (uint8_t *)calloc(14, sizeof(uint8_t));
     uint8_t *result_2 = (uint8_t *)calloc(14, sizeof(uint8_t));
     uint8_t key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
     uint32_t frame = 0x135;
     
     A5Function(result_1, result_2, key, frame);
     for (int i = 0; i < 14; i++)
     {
          printf("%02x", result_1[i]);
     }
     printf("\n");

     for (int i = 0; i < 14; i++)
     {
          printf("%02X", result_2[i]);
     }
     printf("\n");
}
