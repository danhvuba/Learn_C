#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t C[32][4] = {0};
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            C[i][j] = ((4 * i + j + 1) * 7) % 256;
        }
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%02x ", C[i][j]);
        }
        printf("\n");
    }
    printf("---------------------\n");
    for (int i = 0; i < 32; i++)
    {
        for (int t = 0; t < 32; t++)
        {
            // if ((t != i))
            // {
            //     if ((C[i][0] == C[t][0]) && (C[i][1] == C[t][1]) && (C[i][2] == C[t][2]) && (C[i][3] == C[t][3]))
            //     {
            //         printf("%d - %d\n", t, i);
            //     }
            // }
            for (int j1 = 0; j1 < 4; j1++)
                for (int j2 = 0; j2 < 4; j2++)
                {
                    if ((t != i) || (j1 != j2))
                    {
                        if ((C[i][j2] == C[t][j1]))
                        {
                            printf("%d-%d = %d-%d\n", t, j1, i, j2);
                        }
                    }
                }
        }
    }
}
