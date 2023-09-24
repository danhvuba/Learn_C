
#include "header.h"
#include <ctime>
int main()
{
    clock_t start, end;
    double time_use;

    uint64_t key = 0xB3952B5CA8D06B3D; // 0xB8952F5C78D06B3D; // 13300589148719049533;
    printf("key: K= %lX\n", key);
    Print_bit(key);
    cout << endl;
    printf("key >>> 16: K'= %lX\n", Rotation_key(key, 16));
    Print_bit(Rotation_key(key, 16));

    uint32_t data = 0x7AEB6B3D; // 0x458A2B7C;//
    cout << endl
         << "------------------------------------------------------------------------" << endl;
    printf("text: P= %X\n", data);
    Print_bit(data);
    cout << endl
         << "------------------------------------------------------------------------" << endl;
    srand(time(NULL));

    ///// ex1+2
    cout << "Search P':\n";
    start = clock();
    Find_data(data, key, 16);
    end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "time use: " << time_use << endl;

    ///// ex3
    // start = clock();
    // int count = 0;
    // for (int i = 0; i < 3; i++)
    // {
    //     key = rand();
    //     key = (key << 32) ^ rand();
    //     printf("key: K= %lX\n", key);
    //     Print_bit(key);
    //     cout << endl;
    //     uint32_t data = 0x458A2B7C; // 0x7AEB6B4D; // 2026924861;
    //     for (int i = 0; i < 5; i++)
    //     {
    //         data = rand();
    //         printf("      text: P= %08X     ", data);

    //         count += Find_data(data, key, 16);
    //         time_use += ((double)(end - start) / CLOCKS_PER_SEC);
    //     }
    //     cout << "------------------------------------------------------------------------" << endl;
    // }
    // end = clock();
    // time_use = ((double)(end - start) / CLOCKS_PER_SEC);
    // cout<<((float)count/15)<<endl;
    // cout << "time use: " << time_use << endl;

    //////////////////////////////////////////////  2
    // for (int r = 1; r < 10; r++)
    // {
    //     start = clock();
    //     int count = 0;
    //     for (int i = 0; i < 100; i++)
    //     {
    //         uint64_t key = rand();
    //         uint32_t data = rand();
    //         count = count + Find_encode_data(data, key, r);
    //     }
    //     end = clock();
    //     time_use = (double)(end - start) / CLOCKS_PER_SEC;
    //     cout << "r= " << r << "  result= " << (float)count/100 << "   times: " << time_use << endl;
    // }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ////////// search key
    // uint32_t keyP = 0b10101000110100000110101100111101; // P'-1
    // // uint32_t keyP=0b11010011001000101100000100101010;// P'-2
    // uint32_t trueData = Keeloq_Encrypt(data, key);

    // for (uint32_t tmp = 0; tmp < 0xffffffff; tmp++)
    // {
    //     uint64_t fKey = tmp;
    //     fKey = (fKey << 32) ^ keyP;
    //     if (Keeloq_Encrypt(data, fKey) == trueData)
    //     {
    //         printf("true Key: %x", tmp);
    //     }
    // }
}