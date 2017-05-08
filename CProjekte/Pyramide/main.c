#include <stdio.h>
#include <stdlib.h>

int main()
{
    int eingabe = 0 ;
    printf("Bitte eine Zahl eingeben (von 1-20):\n");
    if (scanf("%d", &eingabe) != 1)
    {
        printf("Fehler: Eingabe ist keine Zahl!\n");
        return EXIT_FAILURE;
    }
    if (eingabe < 1 || eingabe > 20)
    {
        printf("Fehler: Eingabe muss zwischen 1 und 20 liegen!\n");
        return EXIT_FAILURE;
    }
    printf("Ausgabe:\n\n");
    for(int row=1;row<=eingabe;row++)
    {
        for(int col=1;col<=row;col++)
        {
            printf("%d", row);
        }
        printf("\n");
    }

    printf("\n");
    return EXIT_SUCCESS;
}
