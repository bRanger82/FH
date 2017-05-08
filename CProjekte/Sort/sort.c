#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int findMin(int *, int);
void sortiereEins();
void sortiereZwei();

int numbers [MAX];

int main()
{


    int i = 0;
    //srand() //Zufallsgenerator neu setzen

    for (i=0;i<MAX;i++)
        numbers[i] = rand() % MAX + 1; //Zufallszahl zwischen 1 und MAX

    int *anf, *end;
    anf = &numbers[0];
    end = &numbers[MAX-1];
    printf("%p ~ %p = %d\n", anf, end, end-anf);
    return 0;

    printf("UN-SORTIERT\n");
    for (i=0;i<MAX;i++)
        printf("%d\t", numbers[i]);

    //sortiereEins();
    sortiereZwei();

    printf("\n\nSORTIERT\n");
    for (i=0;i<MAX;i++)
        printf("%d\t", numbers[i]);

    return EXIT_SUCCESS;
}

void sortiereEins()
{
    int i = 0;
    int x = 0;

    for (i=0;i<MAX;i++)
        for(x=i;x<MAX;x++)
        {
            if (numbers[i] > numbers[x])
            {
                int help = numbers[i];
                numbers[i] = numbers[x];
                numbers[x] = help;
            }
        }
}

void sortiereZwei()
{
    int i, j;
    for (i = 0;i<MAX;++i)
    {
        int min = numbers[i];
        int minpos = i;
        for(j=i;j<MAX;++j)
        {
            if(numbers[j] < min)
            {
                min = numbers[j];
                minpos = j;
            }
        }
        int help = numbers[i];
        numbers[i] = numbers[minpos];
        numbers[minpos] = help;

    }
}

int findMin(int * arr, int startPos)
{
    int i = 0;
    int ret = 0;
    for(i=startPos;i<MAX;i++)
        if (arr[i] < ret)
            ret = i;

    return ret;
}

