/*
method : find out each sum started from num[0][0] and calculate each sum by that result.
time complexity : O(n^4)
Last modified : 2014/05/15
*/

#include <stdio.h>
#include <string.h>

int main()
{
    int N, num[100][100]; /* input */
    int sum[100][100]; /* rectangle from num[0][0] with i height and j width */
    int i, j, k, m, n, o, x, y, z; /* for loop */
    int max = -127;
    int value;

    /* freopen("input.txt", "r", stdin); */

    memset(sum, 0, sizeof(sum));

    scanf("%d", &N);
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            scanf("%d", &num[i][j]);
        }
    }

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(i==0 && j==0)
            {
                sum[0][0] = num[0][0];
            }
            else if(i==0)
            {
                sum[0][j] = sum[0][j-1] + num[0][j];
            }
            else if(j==0)
            {
                sum[i][0] = sum[i-1][0] + num[i][0];
            }
            else
            {
                sum[i][j] = sum [i-1][j] + sum[i][j-1] - sum[i-1][j-1] + num[i][j];
            }
        }
    }

    /* value : sum of the rectangle value from sum[i][j] with m height and n width */
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            for(m=1;m+i<=N;m++)
            {
                for(n=1;n+j<=N;n++)
                {
                    if(i==0 && j==0)
                    {
                        value = sum[m-1][n-1];
                    }
                    else if(i==0)
                    {
                        value = sum[m+i-1][n+j-1] - sum[m+i-1][j-1];
                    }
                    else if(j==0)
                    {
                        value = sum[m+i-1][n+j-1] - sum[i-1][n+j-1];
                    }
                    else
                    {
                        value = sum[m+i-1][n+j-1] - sum[m+i-1][j-1] - sum[i-1][n+j-1] + sum[i-1][j-1];
                    }
                    if(value > max)
                    {
                        max = value;
                    }
                }
            }
        }
    }

    printf("%d\n", max);

    return 0;
}
