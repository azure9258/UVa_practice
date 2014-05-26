/*
method : LCA (n^2)
Last modified : 2014/05/27
*/
#include <stdio.h>
#include <string.h>
#define maxLenName 31
#define maxNumName 300

int isChild();
int isParent();
int isSibling();
int isCousin();

int main()
{
    int i, j, k; /* for loop */
    char name1[maxLenName], name2[maxLenName]; /* input */
    char nameSet[maxNumName][maxLenName];
    int numName = 0;
    int parent[maxNumName], child[maxNumName];
    int check1, check2;
    int result;

    /* freopen("input.txt", "r", stdin); */

    memset(parent, -1, sizeof(parent));

    while(scanf("%s %s", name1, name2) == 2)
    {
        if(!strcmp(name1, "no.child"))
        {
            break;
        }
        check1 = check2 = 0;
        for(i=0;i<numName;i++)
        {
            if(!strcmp(nameSet[i], name1))
            {
                check1 = 1;
                break;
            }
        }
        for(j=0;j<numName;j++)
        {
            if(!strcmp(nameSet[j], name2))
            {
                check2 = 1;
                break;
            }
        }
        if(check1 == 0)
        {
            strcpy(nameSet[numName],name1);
            i = numName;
            numName++;
        }
        if(check2 == 0)
        {
            strcpy(nameSet[numName],name2);
            j = numName;
            numName++;
        }
        parent[i] = j;
        child[j] = i;
    }

    while(scanf("%s %s", name1, name2) == 2)
    {
        /* search index of array of the name */
        for(i=0;i<numName;i++)
        {
            if(!strcmp(nameSet[i], name1))
            {
                break;
            }
        }
        for(j=0;j<numName;j++)
        {
            if(!strcmp(nameSet[j], name2))
            {
                break;
            }
        }

        result = isChild(parent, numName, i, j);
        if(result != 0)
        {
            if(result == 1)
            {
                printf("child\n");
            }
            else
            {
                for(i=2;i<result;i++)
                {
                    printf("great ");
                }
                printf("grand child\n");
            }
            continue;
        }

        result = isParent(parent, numName, i, j);
        if(result != 0)
        {
            if(result == 1)
            {
                printf("parent\n");
            }
            else
            {
                for(i=2;i<result;i++)
                {
                    printf("great ");
                }
                printf("grand parent\n");
            }
            continue;
        }

        result = isSibling(parent, numName, i, j);
        if(result == 1)
        {
            printf("sibling\n");
            continue;
        }

        /* check if cousin relation, and use i, j variable to return m, n-ancestor relationship */
        result = isCousin(parent, numName, &i, &j);
        if(result == 1)
        {
            if(i == j)
            {
                printf("%d cousin\n", i);
            }
            else if(i < j)
            {
                printf("%d cousin removed %d\n", i, j-i);
            }
            else
            {
                printf("%d cousin removed %d\n", j, i-j);
            }
            continue;
        }

        /* None of the above */
        printf("no relation\n");
    }

    return 0;
}

int isChild(int* parent, int numName, int iName1, int iName2)
{
    int i, j;
    int count = 1;

    i = iName1;

    while(1)
    {
        if(parent[i] == -1)
        {
            break;
        }
        if(parent[i] == iName2)
        {
            return count;
        }
        i = parent[i];
        count++;
    }
    return 0;
}
int isParent(int* parent, int numName, int iName1, int iName2)
{
    int i, j;
    int count = 1;

    i = iName2;

    while(1)
    {
        if(parent[i] == -1)
        {
            break;
        }
        if(parent[i] == iName1)
        {
            return count;
        }
        i = parent[i];
        count++;
    }
    return 0;
}
int isSibling(int* parent, int numName, int iName1, int iName2)
{
    if(parent[iName1] == -1 || parent[iName2] == -1)
    {
        return 0;
    }
    if(parent[iName1] == parent[iName2])
    {
        return 1;
    }
    return 0;
}
int isCousin(int* parent, int numName, int* iName1, int* iName2)
{
    int i, j;
    int m = 0, n = 0;
    int check = 0;

    i = *iName1;
    while(1)
    {
        if(parent[i] == -1)
        {
            break;
        }
        j = *iName2;
        n = 0;
        while(1)
        {
            if(parent[j] == -1)
            {
                break;
            }
            if(parent[i] == parent[j])
            {
                check = 1;
                break;
            }
            j = parent[j];
            n++;
        }
        if(check == 1)
        {
            break;
        }
        i = parent[i];
        m++;
    }
    if(check == 0)
    {
        return 0;
    }
    else
    {
        *iName1 = m;
        *iName2 = n;
        return 1;
    }
    return -1;
}
