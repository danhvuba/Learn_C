#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Test(uint8_t **m)
{
    *m = (uint8_t *)realloc(*m, 2);
    (*m)[0] = 1;
}

int main()
{
    uint8_t *m = (uint8_t *)malloc(1);
    Test(&m);
}