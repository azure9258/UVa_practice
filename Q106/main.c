/*
method : if a=m^2-n^2, b=2mn, c=m^2+n^2, a^2+b^2=c^2, which m>n
Last modified : 2014/05/09
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* return the greatest common divisor of a and b */
int gcd(int a, int b)
{
    int t;
    while(t = a % b)
    {
        a = b;
        b = t;
    }
    return b;
}

int main()
{
	int n; /* input */
    int i, j, k; /* for loop */
    int *exist = malloc(1000001*sizeof(int));
    int num_prime_tuple = 0;
    int num_exist;

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d", &n) == 1)
    {
        /* initialize the variable */
        memset(exist, 0, sizeof(int)*1000001);
        num_prime_tuple = 0;
        num_exist = n;

        for(i=1;i*i<=n;i++)
        {
            for(j=i+1;(i*i+j*j)<=n;j+=2)
            {
                if(gcd(j,i) != 1)
                {
                    continue;
                }

                k = 1;
                while(k*(i*i+j*j)<=n)
                {
                    exist[(j*j-i*i)*k] = 1;
                    exist[(2*i*j)*k] = 1;
                    exist[(j*j+i*i)*k] = 1;
                    k++;
                }
                num_prime_tuple++;
            }
        }
        for(i=1;i<=1000000;i++)
        {
            num_exist -= exist[i];
        }
        printf("%d %d\n", num_prime_tuple, num_exist);
    }

    free(exist);
    return 0;
}
