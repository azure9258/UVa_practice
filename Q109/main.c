/*
method : Monotone Chain Convex Hull (reference : http://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull)
Last modified : 2014/05/1
*/
#include <stdio.h>
#include <string.h>

struct point
{
    int x;
    int y;
};

int qsortCompareByxy(const void *a1, const void *a2)
{
    struct point p1 = *(struct point*) a1;
    struct point p2 = *(struct point*) a2;
    if(p1.x == p2.x)
    {
        return p1.y - p2.y;
    }
    return p1.x - p2.x;
}

int main()
{
    int i, j, k, m, n, o, x, y, z; /* for loop */
    int num; /* input */
    struct point kingdom[20][100], missile[30];
    int num_sites[20], num_kingdom = 0, num_missile = 0;
    struct point hull1[100], hull2[100];
    int num_hull1, num_hull2;
    double temp_y;
    struct point new_hull[20][100];
    int num_newhull[20];
    int counter;

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

    for(i=0;i<num_kingdom;i++)
    {
        qsort(kingdom[i], num_sites[i], sizeof(struct point), qsortCompareByxy);
    }

    for(i=0;i<num_kingdom;i++)
    {
        num_hull1 = 0;
        for(j=0;j<num_sites[i];j++)
        {
            while(num_hull1 >= 2)
            {
                temp_y = (double)hull1[num_hull1-2].y + (double)(hull1[num_hull1-1].x - hull1[num_hull1-2].x) * (double)(kingdom[i][j].y - hull1[num_hull1-2].y) / (double)(kingdom[i][j].x - hull1[num_hull1-2].x);
                if(temp_y > (double)hull1[num_hull1-1].y)
                {
                    break;
                }
                else
                {
                    num_hull1--;
                }
            }
            hull1[num_hull1].x = kingdom[i][j].x;
            hull1[num_hull1].y = kingdom[i][j].y;
            num_hull1++;
        }
        num_hull1--;
        num_hull2 = 0;
        for(j=num_sites[i]-1;j>=0;j--)
        {
            while(num_hull2 >= 2)
            {
                temp_y = (double)hull2[num_hull2-2].y + (double)(hull2[num_hull2-1].x - hull2[num_hull2-2].x) * (double)(kingdom[i][j].y - hull2[num_hull2-2].y) / (double)(kingdom[i][j].x - hull2[num_hull2-2].x);
                if(temp_y < (double)hull2[num_hull2-1].y)
                {
                    break;
                }
                else
                {
                    num_hull2--;
                }
            }
            hull1[num_hull2].x = kingdom[i][j].x;
            hull1[num_hull2].y = kingdom[i][j].y;
            num_hull2++;
        }
        num_hull2--;

        counter = 0;
        for(k=0;k<num_hull1;k++)
        {
            new_hull[i][counter].x = hull1[k].x;
            new_hull[i][counter].y = hull1[k].y;
            counter++;
        }
        for(k=0;k<num_hull2;k++)
        {
            new_hull[i][counter].x = hull2[k].x;
            new_hull[i][counter].y = hull2[k].y;
            counter++;
        }
        num_newhull[i] = counter;
    }

    return 0;
}
