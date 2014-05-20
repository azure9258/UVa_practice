/*
method : find regular pattern, and use recursive
Last modified : 2014/05/20
*/
#include <stdio.h>

char alphabet[8]; /* order of a, b, d, e, f, g, h, i */
int num_alpha; /* numbers of alphabet array */

/* run recursive */
void run_sort(int, int);

/* print out the indent of each line of code */
void print_indent(int);

/* print out the line of readln(a,b,...) */
void print_readln();

/* exchange the value of alphabet[n1] and alphabet[n2] */
void swap(int, int);

int main()
{
    int i, j, k; /* for loop */
    int N, num;

    /* freopen("input.txt", "r", stdin); */

    scanf("%d", &N);
    for(i=0;i<N;i++)
    {
        scanf("%d", &num);

        printf("program sort(input,output);\nvar\n");
        for(j=0;j<num-1;j++)
        {
            printf("%c,",'a'+j);
        }
        printf("%c : integer;\nbegin\n  readln(", 'a'+num-1);
        for(j=0;j<num-1;j++)
        {
            printf("%c,", 'a'+j);
        }
        printf("%c);\n", 'a'+num-1);

        alphabet[0] = 'a';
        num_alpha = 1;

        run_sort('b', 'a'+num);

        printf("end.\n");

        if(i<N-1)
        {
            printf("\n");
        }
    }

    return 0;
}

void run_sort(int next, int bound)
{
    int i, j, k; /* for loop */
    if(next == bound)
    {
        print_indent(next - 'a');
        print_readln();
        return;
    }
    alphabet[num_alpha++] = next;

    print_indent(next - 'a');
    printf("if %c < %c then\n", alphabet[num_alpha-2], alphabet[num_alpha-1]);

    run_sort(next+1, bound);

    for(i=num_alpha-1;i>0;i--)
    {
        swap(i, i-1);
        print_indent(next - 'a');
        if(i==1)
        {
            printf("else\n");
        }
        else
        {
            printf("else if %c < %c then\n", alphabet[i-2], alphabet[i-1]);
        }
        run_sort(next+1, bound);
    }

    for(i=1;i<num_alpha;i++)
    {
        alphabet[i-1] = alphabet[i];
    }
    num_alpha--;

}

void print_indent(int num)
{
    int i; /* for loop */

    for(i=0;i<num;i++)
    {
        printf("  ");
    }
}
void print_readln()
{
    int i; /* for loop */

    printf("writeln(");
    for(i=0;i<num_alpha-1;i++)
    {
        printf("%c,", alphabet[i]);
    }
    printf("%c)\n", alphabet[num_alpha-1]);
}

void swap(int a, int b)
{
    int temp;
    temp = alphabet[a];
    alphabet[a] = alphabet[b];
    alphabet[b] = temp;
}
