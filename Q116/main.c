/*
tip : not accept if space existed at the end of the line
method : Dynamic Programming
Last modified : 2014/05/28
*/
#include <stdio.h>
#define max_m 10
#define max_n 100

/* used to find out the lexicographically smaller matrix,
return 0 : same
return 1 : first matrix is lexicographically smaller
return 2 : second matrix is lexicographically smaller
 */
int lexicographicallyCompare();

int main()
{
    int i, j, k; /* for loop */
    int m, n; /* input, m*n matrix*/
    int matrix[max_m][max_n]; /* input matrix */
    int path[2][max_m][max_n]; /* two 2D matrix to save the path. Use by turn. */
    int sumPath[max_m][max_n], sum1, sum2, sum3; /* the sum value of each path */
    int nowPath, nextPath;
    int result, min;
    int cPath; /* path choice */

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif

    while(scanf("%d %d", &m, &n) == 2)
    {

        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }

        /* processing special case */
        if(m == 1)
        {
            min = matrix[0][0];
            printf("1");
            for(i=1;i<n;i++)
            {
                printf(" 1");
                min += matrix[0][i];
            }
            printf("\n");
            printf("%d\n", min);
            continue;
        }
        else if(m == 2)
        {
            nowPath = 1;
            nextPath = 0;
            path[0][0][0] = 0;
            path[0][1][0] = 1;
            sumPath[0][0] = matrix[0][0];
            sumPath[1][0] = matrix[1][0];
            for(i=1;i<n;i++)
            {
                nextPath = nowPath;
                nowPath = (nextPath+1) % 2;
                if(sumPath[0][i-1] < sumPath[1][i-1])
                {
                    cPath = 1;
                }
                else if(sumPath[0][i-1] > sumPath[1][i-1])
                {
                    cPath = 2;
                }
                else
                {
                    cPath = 1;
                }
                if(cPath == 1)
                {
                    for(k=0;k<i;k++)
                    {
                        path[nextPath][0][k] = path[nowPath][0][k];
                        path[nextPath][1][k] = path[nowPath][0][k];
                    }
                    path[nextPath][0][i] = 0;
                    path[nextPath][1][i] = 1;
                    sumPath[0][i] = sumPath[0][i-1] + matrix[0][i];
                    sumPath[1][i] = sumPath[0][i-1] + matrix[1][i];
                }
                else
                {
                    for(k=0;k<i;k++)
                    {
                        path[nextPath][0][k] = path[nowPath][1][k];
                        path[nextPath][1][k] = path[nowPath][1][k];
                    }
                    path[nextPath][0][i] = 0;
                    path[nextPath][1][i] = 1;
                    sumPath[0][i] = sumPath[1][i-1] + matrix[0][i];
                    sumPath[1][i] = sumPath[1][i-1] + matrix[1][i];
                }
            }
            if(sumPath[0][n-1] < sumPath[1][n-1])
            {
                result = 0;
            }
            else if(sumPath[0][n-1] > sumPath[1][n-1])
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
            printf("%d", path[nextPath][result][0]+1);
            for(i=1;i<n;i++)
            {
                printf(" %d", path[nextPath][result][i]+1);
            }
            printf("\n");
            printf("%d\n", sumPath[result][n-1]);
            continue;
        }

        /* if m >= 3 */
        nowPath = 1;
        nextPath = 0;
        for(i=0;i<m;i++)
        {
            path[0][i][0] = i;
            sumPath[i][0] = matrix[i][0];
        }

        for(i=1;i<n;i++)
        {
            nextPath = nowPath;
            nowPath = (nextPath+1) % 2;
            for(j=0;j<m;j++)
            {
                sum1 = sumPath[(j+m-1)%m][i-1] + matrix[j][i];
                sum2 = sumPath[j][i-1] + matrix[j][i];
                sum3 = sumPath[(j+1)%m][i-1] + matrix[j][i];
                if(sum1 < sum2)
                {
                    if(sum2 <= sum3) /* sum1 is min */
                    {
                        cPath = 1;
                    }
                    else if(sum1 < sum3) /* sum1 is min */
                    {
                        cPath = 1;
                    }
                    else if(sum1 > sum3) /* sum3 is min*/
                    {
                        cPath = 3;
                    }
                    else /* both sum1 and sum3 is min */
                    {
                        result = lexicographicallyCompare(path[nowPath][(j+m-1)%m], path[nowPath][(j+1)%m], i);
                        if(result == 1) /* sum1 is lexicographically smaller */
                        {
                            cPath = 1;
                        }
                        else if(result == 2) /* sum3 is lexicographically smaller */
                        {
                            cPath = 3;
                        }
                        else /* sum1 and sum3 is lexicographically equal */
                        {
                            cPath = 1;
                        }
                    }
                }
                else if(sum1 > sum2)
                {
                    if(sum2 > sum3) /* sum3 is min*/
                    {
                        cPath = 3;
                    }
                    else if(sum2 < sum3) /* sum2 is min*/
                    {
                        cPath = 2;
                    }
                    else /* both sum2 and sum3 is min */
                    {
                        result = lexicographicallyCompare(path[nowPath][j], path[nowPath][(j+1)%m], i);
                        if(result == 1) /* sum2 is lexicographically smaller */
                        {
                            cPath = 2;
                        }
                        else if(result == 2) /* sum3 is lexicographically smaller */
                        {
                            cPath = 3;
                        }
                        else /* sum2 and sum3 is lexicographically equal */
                        {
                            cPath = 2;
                        }
                    }
                }
                else /* sum1 == sum2 */
                {
                    if(sum1 > sum3) /* sum3 is min */
                    {
                        cPath = 3;
                    }
                    else if(sum1 < sum3) /* both sum1 and sum2 is min */
                    {
                        result = lexicographicallyCompare(path[nowPath][(j+m-1)%m], path[nowPath][j], i);
                        if(result == 1) /* sum1 is lexicographically smaller */
                        {
                            cPath = 1;
                        }
                        else if(result == 2) /* sum2 is lexicographically smaller */
                        {
                            cPath = 2;
                        }
                        else /* sum1 and sum2 is lexicographically equal */
                        {
                            cPath = 1;
                        }
                    }
                    else /* sum1, sum2, sum3 is same*/
                    {
                        result = lexicographicallyCompare(path[nowPath][(j+m-1)%m], path[nowPath][j], i);
                        if(result == 1) /* sum1 is lexicographically smaller than sum2 */
                        {
                            result = lexicographicallyCompare(path[nowPath][j], path[nowPath][(j+1)%m], i);
                            if(result == 1) /* sum1 is lexicographically smallest */
                            {
                                cPath = 1;
                            }
                            else if(result == 2) /* both sum1 and sum3 is lexicographically smaller than sum2 */
                            {
                                result = lexicographicallyCompare(path[nowPath][(j+m-1)%m], path[nowPath][(j+1)%m], i);
                                if(result == 1) /* sum1 is lexicographically smallest */
                                {
                                    cPath = 1;
                                }
                                else if(result == 2) /* sum3 is lexicographically smallest */
                                {
                                    cPath = 3;
                                }
                                else /* both sum1 and sum3 is the lexicographically smallest */
                                {
                                    cPath = 1;
                                }
                            }
                            else /* sum1 is lexicographically smallest */
                            {
                                cPath = 1;
                            }
                        }
                        else if(result == 2) /* sum2 is lexicographically smaller than sum1 */
                        {
                            result = lexicographicallyCompare(path[nowPath][(j+m-1)%m], path[nowPath][(j+1)%m], i);
                            if(result == 1) /* sum2 is lexicographically smallest */
                            {
                                cPath = 2;
                            }
                            else if(result == 2) /* both sum2 and sum3 is lexicographically smaller than sum1 */
                            {
                                result = lexicographicallyCompare(path[nowPath][j], path[nowPath][(j+1)%m], i);
                                if(result == 1) /* sum2 is lexicographically smallest */
                                {
                                    cPath = 2;
                                }
                                else if(result == 2) /* sum3 is lexicographically smallest */
                                {
                                    cPath = 3;
                                }
                                else /* both sum2 and sum3 is the lexicographically smallest */
                                {
                                    cPath = 2;
                                }
                            }
                            else /* sum2 is lexicographically smallest */
                            {
                                cPath = 2;
                            }
                        }
                        else /* sum1 and sum2 is lexicographically equal */
                        {
                            result = lexicographicallyCompare(path[nowPath][(j+m-1)%m], path[nowPath][(j+1)%m], i);
                            if(result == 1) /* both sum1 and sum2 is the lexicographically smallest */
                            {
                                cPath = 1;
                            }
                            else /* (lexicographically) sum3 < sum1 = sum2 or sum1 = sum2 = sum3 */
                            {
                                cPath = 3;
                            }
                        }
                    }
                }
                if(cPath == 1)
                {
                    for(k=0;k<i;k++)
                    {
                        path[nextPath][j][k] = path[nowPath][(j+m-1)%m][k];
                    }
                    path[nextPath][j][i] = j;
                    sumPath[j][i] = sum1;
                }
                else if(cPath == 2)
                {
                    for(k=0;k<i;k++)
                    {
                        path[nextPath][j][k] = path[nowPath][j][k];
                    }
                    path[nextPath][j][i] = j;
                    sumPath[j][i] = sum2;
                }
                else /* cPath == 3 */
                {
                    for(k=0;k<i;k++)
                    {
                        path[nextPath][j][k] = path[nowPath][(j+1)%m][k];
                    }
                    path[nextPath][j][i] = j;
                    sumPath[j][i] = sum3;
                }
            }
        }

        result = 0;
        min = sumPath[0][n-1];
        for(i=1;i<m;i++)
        {
            if(sumPath[i][n-1] < min)
            {
                result = i;
                min = sumPath[i][n-1];
            }
            else if(sumPath[i][n-1] == min)
            {
                k = lexicographicallyCompare(path[nextPath][result], path[nextPath][i], n);
                if(k == 2)
                {
                    result = i;
                }
            }
        }
        printf("%d", path[nextPath][result][0]+1);
        for(i=1;i<n;i++)
        {
            printf(" %d", path[nextPath][result][i]+1);
        }
        printf("\n");
        printf("%d\n", min);

    }

    return 0;
}

int lexicographicallyCompare(int* a, int* b, int num)
{
    int i; /* for loop */
    for(i=0;i<num;i++)
    {
        if(a[i] < b[i])
        {
            return 1;
        }
        else if(a[i] > b[i])
        {
            return 2;
        }
        else
        {
            continue;
        }
    }
    return 0;
}
