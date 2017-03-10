#include <stdio.h>
#include <stdlib.h>

#define SSIZE 5

void push(int e);
int top();
int pop();
int astack[SSIZE];
int next = 0;

int main()
{
    int eingabe = 0;

    while(eingabe != -1)
    {
        printf("push? ");
        fflush(stdin);
        scanf("%d", &eingabe);
        if (eingabe != -1)
            push(eingabe);
    }
    return EXIT_SUCCESS;
}

void push(int e)
{
    if(next > SSIZE-1)
        puts("Stack Full!!!");
    else
        astack[next++] = e;
}

int pop()
{
    if (count < 1)
        puts("Stack Empty!!!");
    else
        return astack[--next];
}

