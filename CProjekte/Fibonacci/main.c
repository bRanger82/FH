#include <stdio.h>
#include <stdlib.h>

int getUserInput();
int Fibonacci(int n);

int main()
{
    int inp = getUserInput();
    if (inp <0)
        return inp;

    for (int a=0;a<=inp;a++)
    {
        printf("%d ", Fibonacci(a));
    }
    printf("\n");
    return EXIT_SUCCESS;
}

int getUserInput()
{
    int usrInputCnt = 0;

    printf("Bitte Anzahl fuer die Zahlenfolge eingeben (1-500):\n");
    if (scanf("%i", &usrInputCnt) != 1)
    {
        printf("Fehlerhafte Eingabe!\n");
        return -1;
    }
    if (usrInputCnt <=0 || usrInputCnt >500)
    {
        printf("Fehlerhafte Eingabe! Zahl muss zwischen 1 und 500 liegen!\n");
        return -1;
    }
    return usrInputCnt;
}

int Fibonacci(int n)
{
    if (n == 0 || n == 1)
        return n;

    return (Fibonacci(n-1)+Fibonacci(n-2));
}
