/*
method :
Last modified : 2014/05/2
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
    int adj[maxNumName][maxNumName]; /* adjacency matrix */
    int check1, check2;
    int result;

    freopen("input.txt", "r", stdin);

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
        adj[i][j] = 1;
    }

    while(scanf("%s %s", name1, name2) == 2)
    {
        result = isChild(nameSet, numName);
        result = isParent(nameSet, numName);
        result = isSibling(nameSet, numName);
        result = isParent(nameSet, numName);
        result = isCousin(nameSet, numName);
    }

    return 0;
}

int isChild(char* nameSet[maxLenName], int numName)
{
    return 0;
}
int isParent(char* nameSet[maxLenName], int numName)
{
    return 0;
}
int isSibling(char* nameSet[maxLenName], int numName)
{
    return 0;
}
int isCousin(char* nameSet[maxLenName], int numName)
{
    return 0;
}
