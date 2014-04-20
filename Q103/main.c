#include <stdio.h>

/* LIS algorithm is referenced from http://www.csie.ntnu.edu.tw/~u91029/LongestIncreasingSubsequence.html */

struct kv{
    int key;
    int value;
};

int box[30][10]; /* box[boxes][situation of each boxes] */
struct kv order[30];
int k, n; /* k = number of boxes, n = dimensionality of the boxes */

int qsortCompare(const void *a1, const void *a2)
{
    return *(int *)a1 - *(int *)a2;
}

int qsortCompareByValue(const void *a1, const void *a2)
{
    struct kv t1 = *(struct kv*) a1;
    struct kv t2 = *(struct kv*) a2;
    return t1.value - t2.value;
}

int main()
{
    int i, j, m, n; /* for loop */
    int temp, temp2, check; /* save the value of variable temporarily */
    int counter;
    int length[30];
    int rank[30];
    int previous[30];
    int max_length, last_box;

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d %d\n", &k, &n) == 2)
    {
        /* initialize */
        for(i=0;i<k;i++)
        {
            length[i] = 1;
            previous[i] = -1;
        }

        for(i=0;i<k;i++)
        {
            counter = 0;
            for(j=0;j<n;j++)
            {
                scanf("%d", &box[i][counter++]);
            }
        }

        /* reorder n dimension of each box by quick sort  */
        for(i=0;i<k;i++)
        {
            qsort(box[i], n, sizeof(int), qsortCompare);
        }

        /* reorder the boxs using the first dimensionality by quick sort  */
        counter = 0;
        for(i=0;i<k;i++)
        {
            order[counter].key = i;
            order[counter].value = box[i][0];
            counter++;
        }
        qsort(order, k, sizeof(struct kv), qsortCompareByValue);
        for(i=0;i<k;i++)
        {
            rank[i] = order[i].key;
        }

        /* LIS algorithm */
        for(i=0;i<k;i++)
        {
            for(j=i+1;j<k;j++)
            {
                temp = rank[i];
                temp2 = rank[j];
                check = 0;
                for(m=0;m<n;m++)
                {
                    if(box[temp][m] >= box[temp2][m])
                    {
                        check = 1;
                        break;
                    }
                }
                /* if box[temp][x] < box[temp2][x] for 0<=x<n */
                if(check == 0)
                {
                    if(length[temp]+1 > length[temp2])
                    {
                        length[temp2] = length[temp] + 1;
                        previous[temp2] = temp;
                    }
                }
            }
        }

        /* find out the longest nesting string */
        max_length = 0;
        for(i=0;i<k;i++)
        {
            if(max_length < length[i])
            {
                max_length = length[i];
                last_box = i;
            }
        }

        /* output */
        printf("%d\n", max_length);
        counter = 0;
        while(last_box != -1)
        {
            rank[counter] = last_box;
            last_box = previous[last_box];
            counter++;
        }
        for(i=counter-1;i>=0;i--)
        {
            printf("%d ",rank[i]+1);
        }
        printf("\n");

    }
    return 0;
}
