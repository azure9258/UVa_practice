/*
method : stack
Last modified : 2014/05/22
*/
#include <stdio.h>
#define N1 5000
#define N2 1000

int main()
{
    int i, j, k; /* for loop */
    int n; /* input */
    int level; /* current level */
    char input_c; /* input */
    char expression[N1]; /* save the char into array */
    int expression_d[N2]; /* save the integer part into this array */
    int num_expression, num_expression_d; /* the number of array */
    int num; /* temporarily save the value of integer */
    int pre_num; /* check if previous char is num */
    int stack[N2];
    int num_stack;
    int check; /* check yes or no */
    int sum;
    int minus; /* check if number is negative */

    /* freopen("input.txt", "r", stdin); */

    while(scanf("%d", &n) == 1)
    {
        /* parse the S-expression into array */
        scanf("%c", &input_c); /* filter space char*/
        scanf("%c", &input_c);
        level = 1;
        expression[0] = '(';
        num_expression = 1;
        num_expression_d = 0;
        pre_num = 0;
        minus = 0;

        while(level != 0)
        {
            scanf("%c", &input_c);
            if(pre_num == 1)
            {
                if(input_c >= 48 && input_c <=57)
                {
                    num = num * 10 + (input_c - 48);
                    continue;
                }
                else
                {
                    if(minus == 1)
                    {
                        num = num * (-1);
                    }
                    expression_d[num_expression_d++] = num;
                    pre_num = 0;
                    minus = 0;
                }
            }

            if(input_c == ' ' || input_c == '\n')
            {
                continue;
            }
            if(input_c == '(')
            {
                level++;
                expression[num_expression++] = '(';
            }
            else if(input_c == ')')
            {
                level--;
                expression[num_expression++] = ')';
            }
            else if(input_c == '-') /* if number is negative */
            {
                minus = 1;
            }
            else
            {
                pre_num = 1;
                num = input_c - 48; /* transform from char to int */
                expression[num_expression++] = 'd'; /* d means that location is a number */
            }
        }

        /* start to calculate all the sums of the paths */
        num_stack = 0; /* stack is empty */
        level = 1;
        i = 1; /* index of expression array */
        j = 0; /* index of expression_d array */
        check = 0; /* check if the result is yes */
        while(level != 0)
        {
            if(expression[i] == '(')
            {
                if(expression[i+1] == ')')
                {
                    if(expression[i+2] == '(' && expression[i+3] == ')') /* reach leaf, count the sums of the path */
                    {
                        sum = 0;
                        for(k=0;k<num_stack;k++)
                        {
                            sum += stack[k];
                        }

                        if(sum == n)
                        {
                            check = 1;
                            break;
                        }
                        else
                        {
                            i += 4;
                            continue;
                        }
                    }
                    else
                    {
                        i += 2;
                        continue;
                    }
                }
                level++;
            }
            else if(expression[i] == ')')
            {
                level--;
                num_stack--;
            }
            else /* number */
            {
                stack[num_stack++] = expression_d[j++];
            }
            i++;
        }

        if(check == 1)
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
    return 0;
}
