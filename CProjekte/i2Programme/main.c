#include <stdio.h>
#include <stdlib.h>

int main()
{

    printf("Dieses Programm rechnet eine Zahl in Hex, Bin und Roman um!\n");
    printf("Bitte geben Sie eine Zahl ein:\n");

    int zahl = 0;

    if (scanf("%d", &zahl) != 1)
    {
        printf("Eingabe ist keine Zahl, Programm wird beendet!\n");
        return -1;
    }

    printf("Eingegebene Zahl: %lf \n", zahl);
    printf("Zahl als Hexadezimal: %x \n", zahl);

    return 0;
}

long int2bin(int zahl)
{

}
