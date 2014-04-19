#include <stdio.h>

int box[30][10]; /* box[boxes][situation of each boxes] */
int k, n; /* k = number of boxes, n = dimensionality of the boxes */

int qsortCompare(const void *a1, const void *a2)
{
    return *(int *)a1 - *(int *)a2;
}

int main()
{
    int i, j; /* for loop */
    int counter;
    int finish[30];
    int rank[30];
    freopen("input.txt", "r", stdin);

    while(scanf("%d %d\n", &k, &n) == 2)
    {
        /* initialize */
        for(i=0;i<k;i++)
        {
            finish[i] = 0;
        }

        for(i=0;i<k;i++)
        {
            counter = 0;
            for(j=0;j<n;j++)
            {
                scanf("%d", &box[i][counter++]);
            }
        }
        for(i=0;i<k;i++)
        {
            qsort(box[i], n, sizeof(int), qsortCompare);
        }

    }
    return 0;
}
