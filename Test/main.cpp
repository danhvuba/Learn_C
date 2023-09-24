#include<stdio.h>
#include<stdint.h>

int main()
{
    FILE *file;
    file = fopen("text.txt", "r");
    fseek(file, 0L, SEEK_END);

    //// messenger: text of hex number
    uint64_t length = ftell(file)/2;
    uint8_t mess[length];
    fseek(file, 0L, SEEK_SET);
    for (int i = 0; i < length; i++)
    {
        fscanf(file,"%2hhx",mess+i);
        printf("%02x ",mess[i]);
    }
    printf("\n");

}