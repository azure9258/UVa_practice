/*
method : n1=(N+1)^k, n2=N^k, find out N and k first (n1:initial height, n2:working cat)
Last modified : 2014/05/11
*/

#include <stdio.h>

/* return x^n */
int powxn(int x, int n)
{
    int i;
    int count = x;
    for(i=1;i<n;i++)
    {
        count = count * x;
    }
    return count;
}

int main()
{
    int n1, n2; /* input */
    int i, j; /* for loop */
    unsigned int left, middle, right; /* used to binary search */
    double left_value, middle_value, right_value;
    double check1, check2; /* check1 = log(n1)/log(n2) */
    int N, k; /* N is mentioned in question, k is the number of cats appeared from the hat */
    unsigned int free_cat, height; /* result */
    unsigned int temp;
    int temp1, temp2, done;

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d %d", &n1, &n2) == 2)
    {
        if(!n1 && !n2)
        {
            break;
        }
        if(n2==1)
        {
            N = 1;
            k = 0;
            temp = n1;
            while(temp != 1)
            {
                k++;
                temp /= 2;
            }
        }
        else if(n1==1)
        {
            N = 0;
            k = 0;
        }
        else if(n1 == n2+1)
        {
            N = n2;
            k = 1;
        }
        else
        {
            /****** method 1 ******/
            /* not work, because of log or precision or other unknown reason */
            /*
            left = 1;
            right = 2147483647;
            middle = (left+right) / 2;
            check1 = log(n1)/log(n2);

            while(left<=right)
            {
                middle = (left+right) / 2;
                check2 = log(middle+1)/log(middle);
                if(fabs(check2-check1) < 0.0000000000001)
                {
                    break;
                }
                if(check1 > check2)
                {
                    right = middle - 1;
                }
                else
                {
                    left = middle + 1;
                }
            }
            N = middle;
            k = (int) round(log(n1)/log(N+1));
            */

            /****** method 2 ******/

            done = 0;
            for(i=2;;i++)
            {
                temp1 = n1;
                temp2 = n2;
                for(j=1;;j++)
                {
                    if((temp1%(i+1))!=0 || (temp2%i)!=0 )
                    {
                        break;
                    }
                    else
                    {
                        temp1 /= (i+1);
                        temp2 /= i;
                        if(temp1 == 1 && temp2 == 1)
                        {
                            done = 1;
                            break;
                        }
                    }
                }
                if(done)
                {
                    break;
                }
            }
            N = i;
            k = j;

        }
        free_cat = 1;
        height = n1;
        temp = 1;
        for(i=1;i<=k;i++)
        {
            temp *= N;
            free_cat += temp;

            n1 = n1 / (N+1);
            height += temp * n1;
        }
        free_cat -= n2;

        printf("%u %u\n", free_cat, height);
    }

    return 0;
}
