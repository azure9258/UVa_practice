/*
method : brute-force (save all the height of each x-coordinate)
Last modified : 2014/05/08
*/

#include <stdio.h>

int main()
{
    int buildings[5000][3]; /* [0]:left, [1]:height, [2]:right */
    int i, j; /* for loop */
    int x_coordinate[10000] = {0};
    int counter = 0;
    int rightmost = 0;
    int temp;

    /*freopen("input.txt", "r", stdin);*/

    while(scanf("%d %d %d", &buildings[counter][0], &buildings[counter][1], &buildings[counter][2]) == 3)
    {
        counter++;
    }

    for(i=0;i<counter;i++)
    {
        for(j=buildings[i][0];j<=buildings[i][2]-1;j++)
        {
            if(x_coordinate[j] < buildings[i][1])
            {
                x_coordinate[j] = buildings[i][1];
            }
        }
        if(rightmost < buildings[i][2])
        {
            rightmost = buildings[i][2];
        }
    }

    temp = buildings[0][0];
    printf("%d %d", temp, x_coordinate[temp]);

    for(i=buildings[0][0]+1;i<rightmost;i++)
    {
        if(x_coordinate[i] == x_coordinate[temp])
        {
            continue;
        }
        temp = i;
        printf(" %d %d", i, x_coordinate[i]);

    }
    printf(" %d 0\n",rightmost);


    return 0;
}
