/*
method :
Last modified : 2014/05/1
*/

struct point
{
    int x;
    int y;
};

#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, k, m, n, o, x, y, z; /* for loop */
    int num; /* input */
    struct point kingdom[20][100], missile[30];
    int num_sites[20], num_kingdom = 0, num_missile = 0;

    freopen("input.txt", "r", stdin);

    while((scanf("%d", &num) == 1) && (num != -1))
    {
        num_sites[num_kingdom] = num;
        for(i=0;i<num;i++)
        {
            scanf("%d %d", &(kingdom[num_kingdom][i].x), &(kingdom[num_kingdom][i].y));
        }
        num_kingdom++;
    }
    while(scanf("%d %d", &missile[num_missile].x, &missile[num_missile].y) == 2)
    {
        num_missile++;
    }


    return 0;
}
