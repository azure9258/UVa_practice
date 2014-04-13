#include <stdio.h>
#include <string.h>

int block[25][25]; /* the situation of the blocks on each position */
int num_block[25]; /* the number of blocks on each position */
int pos_block[25][2]; /* pos_block[i][0] is the horizontal postion of i, pos_block[i][1] is the height of i */

void move_onto(int a, int b)
{
    int i; /* for loop */
    int temp; /* save the value of variable temporarily */
    int a1, a2, b1, b2; /* save a, b information */

    a1 = pos_block[a][0]; /* original horizontal postion of a block */
    a2 = pos_block[a][1]; /* original height of a block */
    b1 = pos_block[b][0]; /* original horizontal postion of b block */
    b2 = pos_block[b][1]; /* original height of b block */
    for(i=a2+1;i<num_block[a1];i++)
    {
        temp = block[a1][i];
        num_block[temp] = 1;
        pos_block[temp][0] = temp;
        pos_block[temp][1] = 0;
    }
    num_block[a1] -= num_block[a1]-a2-1;

    for(i=b2+1;i<num_block[b1];i++)
    {
        temp = block[b1][i];
        num_block[temp] = 1;
        pos_block[temp][0] = temp;
        pos_block[temp][1] = 0;
    }
    num_block[b1] -= num_block[b1]-b2-1;

    pos_block[a][0] = pos_block[b][0];
    pos_block[a][1] = pos_block[b][1] + 1;
    num_block[a1]--;
    num_block[b1]++;

}

void move_over(int a, int b)
{
    int i; /* for loop */
    int temp; /* save the value of variable temporarily */
    int a1, a2, b1, b2; /* save a, b information */

    a1 = pos_block[a][0]; /* original horizontal postion of a block */
    a2 = pos_block[a][1]; /* original height of a block */
    b1 = pos_block[b][0]; /* original horizontal postion of b block */
    b2 = pos_block[b][1]; /* original height of b block */

    for(i=a2+1;i<num_block[a1];i++)
    {
        temp = block[a1][i];
        num_block[temp] = 1;
        pos_block[temp][0] = temp;
        pos_block[temp][1] = 0;
    }
    num_block[a1] -= num_block[a1]-a2-1;

    pos_block[a][0] = pos_block[b][0];
    pos_block[a][1] = num_block[b1];
    num_block[a1]--;
    num_block[b1]++;
}

void pile_onto(int a, int b)
{
    int i; /* for loop */
    int temp; /* save the value of variable temporarily */
    int a1, a2, b1, b2; /* save a, b information */

    a1 = pos_block[a][0]; /* original horizontal postion of a block */
    a2 = pos_block[a][1]; /* original height of a block */
    b1 = pos_block[b][0]; /* original horizontal postion of b block */
    b2 = pos_block[b][1]; /* original height of b block */

    for(i=b2+1;i<num_block[b1];i++)
    {
        temp = block[b1][i];
        num_block[temp] = 1;
        pos_block[temp][0] = temp;
        pos_block[temp][1] = 0;
    }
    num_block[b1] -= num_block[b1]-b2-1;

    for(i=a2;i<num_block[a1];i++)
    {
        temp = block[a1][i];
        pos_block[temp][0] = pos_block[b][0];
        pos_block[temp][1] = pos_block[b][1]+1+(i-a2);
    }
    temp = num_block[a1] - a2;
    num_block[a1] -= temp;
    num_block[b1] += temp;
}

void pile_over(int a, int b)
{
    int i; /* for loop */
    int temp; /* save the value of variable temporarily */
    int a1, a2, b1, b2; /* save a, b information */

    a1 = pos_block[a][0]; /* original horizontal postion of a block */
    a2 = pos_block[a][1]; /* original height of a block */
    b1 = pos_block[b][0]; /* original horizontal postion of b block */
    b2 = pos_block[b][1]; /* original height of b block */

    for(i=a2;i<num_block[a1];i++)
    {
        temp = block[a1][i];
        pos_block[temp][0] = pos_block[b][0];
        pos_block[temp][1] = num_block[b1]+(i-a2);
    }
    temp = num_block[a1] - a2;
    num_block[a1] -= temp;
    num_block[b1] += temp;
}

void adjust(int n)
{
    int i, j; /* for loop */
    int pos, hei; /* horizontal postion and height */
    for(i=0;i<n;i++)
    {
        pos = pos_block[i][0];
        hei = pos_block[i][1];
        block[pos][hei] = i;
        /* printf("(%d,%d,%d)",pos,hei,i); */
    }
    /* printf("\n"); */
}

int main()
{
    int n; /* the number of blocks */
    char commands[15]; /* commands for the robot */
    char command1[5], command2[5]; /* details of the commands */
    int a, b; /* blocks mentioned in commands */
    int i, j; /* for loop */
    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d\n", &n) == 1)
    {
        for(i=0;i<n;i++)
        {
            num_block[i] = 1; /* initialize the number of block each position which is 1 */
            pos_block[i][0] = i; /* initialize where is the i block */
            pos_block[i][1] = 0; /* initialize the height of the block, which is 0 */
        }
        while(scanf("%s", command1) == 1)
        {
            if(strcmp(command1,"quit") == 0)
            {
                break;
            }
            scanf("%d %s %d\n", &a, command2, &b);
            /* printf("(%s,%d,%s,%d)\n",command1,a,command2,b); */
            if(pos_block[a][0] == pos_block[b][0])
            {
                continue;
            }

            if(strcmp(command1, "move") == 0)
            {
                if(strcmp(command2, "onto") == 0)
                {
                    move_onto(a, b);
                }
                else /* command2 == over */
                {
                    move_over(a, b);
                }
            }
            else /* command1 == pile */
            {
                if(strcmp(command2, "onto") == 0)
                {
                    pile_onto(a, b);
                }
                else /* command2 == over */
                {
                    pile_over(a, b);
                }
            }

            adjust(n);
        }
        adjust(n);
        for(i=0;i<n;i++)
        {
            printf("%d:", i);
            for(j=0;j<num_block[i];j++)
            {
                printf(" %d",block[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
