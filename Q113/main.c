/*
method : basic math
Last modified : 2014/05/23
*/
#include <stdio.h>
#include <math.h>

int main()
{
    double n, p; /* input */

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%lf%lf", &n, &p) == 2)
    {
        /* method 1 */
        /* printf("%.0lf\n", pow(p, 1/n)); */

        /* method 2 */
        printf("%.0lf\n", exp(log(p)/n));
    }
    return 0;
}
