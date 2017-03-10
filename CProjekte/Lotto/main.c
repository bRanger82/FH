#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define RMAX 45
#define ANZL 6

int randNum(int limit);
bool checkIfAlreadyExist(long *arr, int zahl);

int main()
{

    int zahl;
    long cnt[RMAX] ={0};
    long lottoz[ANZL] = {0};
    unsigned long long llg;

    srand(time(NULL));
    for (int lop=0;lop<ANZL;lop++)
    {
        int nextZahl = randNum(RMAX);
        if (!checkIfAlreadyExist(lottoz, nextZahl))
            lottoz[lop] = randNum(RMAX);
        else
            lop--;
    }

    printf("Folgende Zahlen wurden gezogen:\n");
    for (int lop=0;lop<ANZL;lop++)
    {
        printf("%02Li x %li \n", lop+1, lottoz[lop]);
    }

    return 0;
}

int randNum(int limit)
{
    return (rand() % limit-1)+1;
}

bool checkIfAlreadyExist(long *arr, int zahl)
{
    int size = sizeof(arr) / sizeof(arr[0]);
    for(int cnt=0;cnt<=size;cnt++)
    {
        printf("Pruefe Zahl %d \n", arr[cnt]);
        if (arr[cnt] == zahl)
            return true;
    }
    return false;
}
