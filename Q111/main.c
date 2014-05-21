/*
tip : the order should transform to correct sequence first
method : LIS (N^2)
Last modified : 2014/05/21
*/
#include <stdio.h>

int main()
{
    int i, j, k; /* for loop */
    int N;
    int correct0[20], correct1[20]; /* correct order */
    int student0[20], student1[20]; /* student order */
    int best[20];
    int check;
    int max;

    /* freopen("input.txt", "r", stdin); */

    scanf("%d", &N);
    for(i=0;i<N;i++)
    {
        scanf("%d", &correct0[i]);
    }
    for(i=0;i<N;i++)
    {
        correct1[correct0[i]-1] = i;
    }

    while(scanf("%d", &student0[0]) == 1)
    {
        for(i=1;i<N;i++)
        {
            scanf("%d", &student0[i]);
        }
        for(i=0;i<N;i++)
        {
            student1[student0[i]-1] = i;
        }

        for(i=0;i<N;i++)
        {
            best[i] = 1;
        }

        for(i=0;i<N;i++)
        {
            for(j=i+1;j<N;j++)
            {
                for(k=0;k<N;k++)
                {
                    if(correct1[k] == student1[i])
                    {
                        check = 1;
                        break;
                    }
                    if(correct1[k] == student1[j])
                    {
                        check = 0;
                        break;
                    }
                }

                if(check == 1)
                {
                    if(best[i]+1 > best[j])
                    {
                        best[j] = best[i] + 1;
                    }
                }
            }
        }

        max = best[0];
        for(i=1;i<N;i++)
        {
            if(best[i] > max)
            {
                max = best[i];
            }
        }
        printf("%d\n", max);
    }

    return 0;
}
