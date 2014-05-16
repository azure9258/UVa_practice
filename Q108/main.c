/*
method : find out each sum started from num[0][0] and calculate each sum by that result.
time complexity : O(n^4)
Last modified : 2014/05/15
*/

#include <stdio.h>
#include <string.h>

int main()
{
    int N, num[101][101]; /* input */
    int sum[101][101]; /* rectangle from num[1][1] with i height and j width */
    int i, j, k, m, n, o, x, y, z; /* for loop */
    int max = -127;
    int value;

    /* freopen("input.txt", "r", stdin); */

    memset(sum, 0, sizeof(sum));

    scanf("%d", &N);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            scanf("%d", &num[i][j]);
        }
    }

    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            sum[i][j] = sum [i-1][j] + sum[i][j-1] - sum[i-1][j-1] + num[i][j];
        }
    }

    /* value : sum of the rectangle value from sum[i][j] with m height and n width */
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            for(m=1;m+i-1<=N;m++)
            {
                for(n=1;n+j-1<=N;n++)
                {
                    value = sum[m+i-1][n+j-1] - sum[m+i-1][j-1] - sum[i-1][n+j-1] + sum[i-1][j-1];
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
