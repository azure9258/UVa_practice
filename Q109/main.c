/*
tip : if no line feed at output, it would get "Wrong answer"
method : Monotone Chain Convex Hull (reference : http://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull)
Last modified : 2014/05/18
*/
#include <stdio.h>
#include <string.h>

struct point
{
    int x;
    int y;
};

/* for qsort */
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

/* calcute the area of polygon */
double area(struct point kingdom[], int num_sites)
{
    int i; /* for loop */
    double counter = 0.0;
    for(i=1;i<num_sites;i++)
    {
        counter += kingdom[i-1].x * kingdom[i].y - kingdom[i].x * kingdom[i-1].y;
    }
    counter *= 0.5;
    return counter;
}

/* check if missile hit inside the kingdom */
/* method : find the sum of area of missile with all two neighbor site.
            if equal to area of kingdom, missile is inside the kingdom */
int missile_hit(int x, int y, struct point kingdom[], int num_sites)
{
    int i; /* for loop */
    double kingdom_area = area(kingdom, num_sites); /* area of kingdom */
    double counter = 0.0;
    double temp;

    /* accumulative total */
    for(i=0;i<num_sites-1;i++)
    {
        struct point tri[4]; /* the first one and the last one is duplicated, so 3+1=4 */
        tri[0].x = tri[3].x = kingdom[i].x;
        tri[0].y = tri[3].y = kingdom[i].y;
        tri[1].x = kingdom[i+1].x;
        tri[1].y = kingdom[i+1].y;
        tri[2].x = x;
        tri[2].y = y;

        /* equal to counter += fabs(area(tri, 4)) */
        temp = area(tri, 4);
        if(temp < 0)
        {
            counter += (-1) * temp;
        }
        else
        {
            counter += temp;
        }
    }
    if(counter == kingdom_area)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int i, j, k, m, n, o, x, y, z; /* for loop */
    int num; /* input */
    struct point kingdom[20][100], missile[30]; /* input data */
    int num_sites[20], num_kingdom = 0, num_missile = 0;
    struct point hull1[100], hull2[100]; /* for Monotone Chain Convex Hull algorithm used */
    int num_hull1, num_hull2; /* number of hull1 and hull2 */
    double temp_y;
    struct point new_hull[20][100]; /* result of Convex Hull */
    int num_newhull[20];
    int counter;
    int hit_kingdom[20] = {0}; /* check if kingdom hit or not */
    int hit_missile[30] = {0};
    double result = 0.0, temp;

    /* freopen("input.txt", "r", stdin); */

    /* get input */
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

    /* sort by coordinate in order to use Monotone Chain Convex Hull algorithm */
    for(i=0;i<num_kingdom;i++)
    {
        qsort(kingdom[i], num_sites[i], sizeof(struct point), qsortCompareByxy);
    }

    /* run Monotone Chain Convex Hull algorithm */
    for(i=0;i<num_kingdom;i++)
    {
        num_hull1 = 0;
        for(j=0;j<num_sites[i];j++)
        {
            while(num_hull1 >= 2)
            {
                if(kingdom[i][j].x == hull1[num_hull1-2].x)
                {
                    num_hull1--;
                    continue;
                }
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
                if(kingdom[i][j].x == hull2[num_hull2-2].x)
                {
                    num_hull2--;
                    continue;
                }
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
            hull2[num_hull2].x = kingdom[i][j].x;
            hull2[num_hull2].y = kingdom[i][j].y;
            num_hull2++;
        }

        /* save the result to new_hull */
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

    /* process the missile */
    for(i=0;i<num_missile;i++)
    {
        for(j=0;j<num_kingdom;j++)
        {
            if(hit_missile[i] == 1)
            {
                break;
            }
            if(hit_kingdom[j] == 1)
            {
                continue;
            }
            if(missile_hit(missile[i].x, missile[i].y, new_hull[j], num_newhull[j]) == 1)
            {
                hit_missile[i] = 1;
                hit_kingdom[j] = 1;
            }
        }
    }

    /* calculate the sum of all hit kingdom */
    for(i=0;i<num_kingdom;i++)
    {
        if(hit_kingdom[i] == 1)
        {
            /* equal to result += fabs(area(new_hull[i], num_newhull[i])) */
            temp = area(new_hull[i], num_newhull[i]);
            if(temp < 0)
            {
                result += (-1) * temp;
            }
            else
            {
                result += temp;
            }
        }
    }

    /* output the result */
    printf("%.2lf\n", result);

    return 0;
}
