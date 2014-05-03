/*
method : Dynamic Programming
Last modified : 2014/05/03
*/

#include <stdio.h>

struct shortest
{
    double profit;
    int path[21];
};

int main()
{
    int n; /* numbers of currency */
    double profit[20][20]; /* table of currency exchanges */
    struct shortest table[20][20][20]; /* table[i][j][k] means the best way from i to j in (k+2) exchanges */
    double max_profit, temp_profit;
    int max; /* which one get the maximum profit */
    int i, j, k, x, y, z; /* for loop */
    int final_i, final_j, final_n, finish; /* recognize finish or not & get the result */

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d", &n) == 1)
    {
        finish = 0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i==j)
                {
                    profit[i][j] = 1.0;
                    continue;
                }
                scanf("%lf", &profit[i][j]);
            }
        }

        /*
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                printf("%lf ", profit[i][j]);
            }
            printf("\n");
        }
        printf("----------------------------\n");
        */

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i == j)
                {
                    continue;
                }
                table[i][j][0].profit = profit[i][j];
                table[i][j][0].path[0] = i;
                table[i][j][0].path[1] = j;
                if(profit[i][j] * profit[j][i] > 1.01)
                {
                    finish = 1;
                    final_i = i;
                    final_j = j;
                    final_n = 0;
                    table[i][j][0].path[2] = i;
                    break;
                }
            }
            if(finish == 1)
            {
                break;
            }
        }
        if(finish == 0)
        {
            for(x=1;x<n-1;x++)
            {
                for(i=0;i<n;i++)
                {
                    for(j=0;j<n;j++)
                    {
                        max_profit = 0.0;
                        for(k=0;k<n;k++)
                        {
                            if(k==j)
                            {
                                continue;
                            }
                            temp_profit = table[i][k][x-1].profit * profit[k][j];
                            if(temp_profit * profit[j][i] > 1.01)
                            {
                                finish = 1;
                                final_i = i;
                                final_j = j;
                                final_n = x;

                                for(y=0;y<x+1;y++)
                                {
                                    table[i][j][x].path[y] = table[i][k][x-1].path[y];
                                }
                                table[i][j][x].path[x+1] = j;
                                table[i][j][x].path[x+2] = i;

                                break;
                            }
                            if(temp_profit > max_profit)
                            {
                                max_profit = temp_profit;
                                max = k;
                            }
                        }
                        if(finish == 1)
                        {
                            break;
                        }
                        table[i][j][x].profit = max_profit;
                        for(y=0;y<x+1;y++)
                        {
                            table[i][j][x].path[y] = table[i][max][x-1].path[y];
                        }
                        table[i][j][x].path[x+1] = j;

                    }
                    if(finish == 1)
                    {
                        break;
                    }
                }
                if(finish == 1)
                {
                    break;
                }
            }
        }

        if(finish == 1)
        {
            for(i=0;i<final_n+2;i++)
            {
                printf("%d ",table[final_i][final_j][final_n].path[i]+1);
            }

            printf("%d\n", table[final_i][final_j][final_n].path[final_n+2]+1);
        }
        else
        {
            printf("no arbitrage sequence exists\n");
        }
    }

    return 0;
}
