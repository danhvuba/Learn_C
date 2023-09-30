#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    uint8_t *x = (uint8_t *)malloc(3 );
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    x=x+1;
    printf("%d\n",x[0]);
    uint8_t *c=(uint8_t*)realloc(x+1,4);
    printf("aaa%d\n",x[0]);
}