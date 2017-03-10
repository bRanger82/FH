#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR 10


int main()
{
    int arr[MAX_ARR];
    int summe = 0;

    for(int num=0;num<MAX_ARR;num++)
    {
        fflush(stdin);
        printf("Bitte geben sie die %d. Zahl ein:\n", num+1);
        if(scanf("%i", &arr[num]) == 1)
            summe += arr[num];
        else
            num--;
    }
    printf("\n"); // Enter fuer bessere Lesbarkeit
    float mittel = ((float)summe / (float)MAX_ARR);

    printf("Mittelwert: %i\n", mittel);

    printf("\n"); // Enter fuer bessere Lesbarkeit

    int klzahl = arr[0];
    for(int num=0;num<MAX_ARR;num++)
    {
        if (klzahl > arr[num])
            klzahl = arr[num];
        if(arr[num] < mittel)
            printf("Zahl unter dem Mittel: %i\n", arr[num]);
    }

    printf("\n"); // Enter fuer bessere Lesbarkeit

    printf("Die kleinste Zahl ist: %i\n", klzahl);

    return 0;
}
