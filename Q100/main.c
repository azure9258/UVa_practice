#include <stdio.h>

int cycle_length(int n)
{
    int length = 1;
    while(n!=1)
    {
        if(n%2==1)
        {
            n = 3 * n + 1;
        }
        else
        {
            n = n / 2;
        }
        length++;
    }
    return length;
}

int main()
{
    int i, j; /* input used to count from i to j */
    int ni, nj, nk; /* used to check i<j */
    int count; /* for loop */
    int max_length;
    int length; /* temp max length */
    while(scanf("%d %d", &i, &j) == 2)
    {
        max_length = 1; /* initial */
        ni = i;
        nj = j;
        if(ni > nj)
        {
            nk = ni;
            ni = nj;
            nj = nk;
        }
        for(count = ni; count <=nj; count++)
        {
            if((length = cycle_length(count)) > max_length)
            {
                max_length = cycle_length(count);
            }
        }
        printf("%d %d %d\n", i, j, max_length);
    }
    return 0;
}
