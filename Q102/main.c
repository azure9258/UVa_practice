#include <stdio.h>

int main()
{
    int bottles[3][3]; /* numbers of B, G, C bottles in each bins */
    int bin[3][3]; /* situation of each bins */
    int i, j, k; /* for loop */
    int BCG[6]; /* 3!=6 possible permutation */
    int counter, min_value;
    int min[6] = {0};

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d %d %d %d %d %d %d %d %d\n", &bottles[0][0], &bottles[0][1], &bottles[0][2], &bottles[1][0], &bottles[1][1], &bottles[1][2], &bottles[2][0], &bottles[2][1], &bottles[2][2]) == 9)
    {
        counter = 0;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                bin[i][j] = bottles[(i+1)%3][j] + bottles[(i+2)%3][j];
            }
        }
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                for(k=0;k<3;k++)
                {
                    if(i==j || j==k || i==k) continue;
                    /* BGC BCG GBC GCB CBG CGB */
                    BCG[counter] = bin[0][i] + bin[1][j] + bin[2][k];
                    counter++;
                }
            }
        }

        /* guess the 1st permutation is minimum initially */
        min_value = BCG[0];
        min[0] = 1;
        for(i=1;i<6;i++)
        {
            min[i] = 0;
        }

        for(i=1;i<6;i++)
        {
            if(min_value > BCG[i])
            {
                for(j=0;j<6;j++)
                {
                    min[j] = 0;
                }
                min[i] = 1;
                min_value = BCG[i];
            }
            else if(min_value == BCG[i])
            {
                min[i] = 1;
            }
        }

        /* according to alphabetically first, the priority is 104523 */
        if(min[1] == 1)
        {
            printf("BCG %d\n", BCG[1]);
        }
        else if(min[0] == 1)
        {
            printf("BGC %d\n", BCG[0]);
        }
        else if(min[4] == 1)
        {
            printf("CBG %d\n", BCG[4]);
        }
        else if(min[5] == 1)
        {
            printf("CGB %d\n", BCG[5]);
        }
        else if(min[2] == 1)
        {
            printf("GBC %d\n", BCG[2]);
        }
        else
        {
            printf("GCB %d\n", BCG[3]);
        }
    }
    return 0;
}
