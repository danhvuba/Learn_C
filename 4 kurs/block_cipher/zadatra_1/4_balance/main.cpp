#include <iostream>
#include <math.h>
using namespace std;

#define Rotation(x) (((x & (0x3)) << 1) ^ (x >> 2))
#define u8 uint8_t

void Print(u8 a)
{
	for (int i = 3; i >= 0; i--)
	{
		printf("%d", ((a >> i) & 0x1));
	}
	printf("\n");
}

int Function(u8 x, int k1, int k2, int r)
{
	u8 x1 = (x >> 1) | k1;
	u8 x2 = ((x & 7) + k2) % 8;
	for (int i = 0; i < r; i++)
		x1 = Rotation(x1);
	return x1 ^ x2;
}

bool Test_balance(int k1, int k2, int r)
{
	int *count = (int *)calloc(8, sizeof(int));

	for (int i = 0; i < 16; i++)
	{
		int y = Function(i, k1, k2, r);
		// 0
		if ((y == 0) || (y == 6))
		{
			printf("phi^-1 (%d)= ", y);
			Print(i);
		}
		count[y]++;
	}

	// // print result
	// for (int i = 0; i < 8; i++)
	// {
	// 	printf("%d   ", count[i]);
	// 	printf("%d   \n", i);
	// }

	for (int i = 0; i < 8; i++)
		if (count[i] != 2)
			return false;
	return true;
}

int main()
{
	int k1 = 7, k2 = 6, r = 1;
	if (Test_balance(k1, k2, r))
		printf("yes balance\n");
	else
		printf("no\n");
}