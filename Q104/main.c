#include <stdio.h>

int main()
{
    int n;
    float input[20][20];
    int i, j, k; /* for loop */

    freopen("input.txt", "r", stdin);

    while(scanf("%d", &n) == 1)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i==j)
                {
                    input[i][j] = 1.0;
                    continue;
                }
                scanf("%f", &input[i][j]);
            }
        }

    }

    return 0;
}
