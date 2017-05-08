#include <stdio.h>
#include <stdlib.h>

int x =1;
int y =2;

int funktion1(int x)
{
    static int y = 5;
    y = y + x;
    return (y);
}

int funktion2(int x)
{
    y=y+x;
    x=y;
    return(y);
}
int main()
{
    int x,y;

    x=y=1;

    printf("%d\n", funktion1(x));
    printf("%d\n", funktion2(x));

    printf("%d\n", funktion1(y));
    printf("%d\n", funktion2(y));

    printf("%d\n", x);
    printf("%d\n", y);

    return EXIT_SUCCESS;
}
