#include <iostream>
#include <math.h>
#include <ctime>

using namespace std;

#define Keeloq_NF 0x3A5C742E
#define bit(x, n) ((x >> n) & 1)
#define g5(x, a, b, c, d, e) (bit(x, a) * 16 + bit(x, b) * 8 + bit(x, c) * 4 + bit(x, d) * 2 + bit(x, e))

// full encoder 528 round
uint32_t Keeloq_Encrypt(uint32_t data, const uint64_t key);

// encoder 'r' round
uint32_t Keeloq_Encrypt(uint32_t data, const uint64_t key, int r);

// decoder
uint32_t Keeloq_Descrypt(uint32_t data, const uint64_t key);

void Print_bit(uint32_t data);
void Print_bit(uint64_t key);

//////////////////////
#define Rotation(key) ((key & 1) << 63) ^ (key >> 1)
// shift key 'r' round
uint64_t Rotation_key(uint64_t key, int r);

// Is data2 = data shift by 'r' round
bool Is_Shift_r(uint32_t data, uint32_t data2,int r);

// find true data2 = data encoder by key 'r' round
int Find_encode_data(uint32_t data, uint64_t key, int r);

// print '____________' 'r' times
void Print_(int r);

int Find_data(uint32_t data, uint64_t key, int r);