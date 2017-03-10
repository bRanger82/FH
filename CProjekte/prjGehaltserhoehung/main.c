#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Bitte geben Sie Ihr derzeitiges Gehalt ein\n");
    float gehalt = 0;
    int retVal = scanf("%f", &gehalt);
    if (gehalt < 1000)
    printf("Ihr neues Gehalt betraegt %.2f", gehalt*0.85);

    puts("Goodbye!");
    return 0;
}
