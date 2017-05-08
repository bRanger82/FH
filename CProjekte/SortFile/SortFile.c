#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void selectionSortArray(int numbers [], int length, bool sortAsc);
void printArrayOnStdOut(int numbers [], int length);

char *basename(char *path)
{
    char *s = strrchr(path, '\\');
    if (!s)
        return strdup(path);
    else
        return strdup(s + 1);
}

void printHelp(char *path)
{
    printf("Das Programm erzeugt eine Datei mit Zufallszahlen.\n");
    printf("Aufruf: %s [-h] [-a | -d]\n", basename(path));
    printf("Bedeutung der Parameter:\n");
    printf("\t-d Sortiert die Zahlen in absteigender Reihenfolge und gibt diese auf stdout aus\n");
    printf("\t-a Sortiert die Zahlen in aufsteigender Reihenfolge und gibt diese auf stdout aus\n");
    printf("\t-h Gibt diese Hilfe aus\n");
}

int main()
{
    for(i=0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-H") == 0)
        {
            printHelp(argv[0]);
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-N") == 0)
        {
            if (argc > i)
                if (atoi(argv[i+1]) > 0)
                    countNumbers = atoi(argv[i+1]);
                else
                    errorEingabe = true;
            else
                errorEingabe = true;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-R") == 0)
        {
            if (argc > i)
                if (atoi(argv[i+1]) > 0)
                    numberRange = atoi(argv[i+1]);
                else
                    errorEingabe = true;
            else
                errorEingabe = true;
        }

        if (errorEingabe)
        {
            printf("Eingabefehler!\nBitte ueberpruefen Sie die Angabe der Parameter.\n");
            printHelp(argv[0]);
            return EXIT_FAILURE;
        }
    }
    return 0;
}


/*
    Sortiert einen Array entweder aufsteigend (sortAsc = true) oder absteigend (sortAsc = false)
*/
void selectionSortArray(int numbers [], int length, bool sortAsc)
{
    int i, o, notSortedIndex;
    int AnzahlDurchlaeufe = 0;

    for(o=0;o<(length-1);o++)
    {
        notSortedIndex = o;
        for(i=o+1;i<length;i++)
        {
            if (sortAsc ? (numbers[notSortedIndex] > numbers[i]) : (numbers[notSortedIndex] < numbers[i]))
            {
                notSortedIndex = i;
            }
        }
        if (notSortedIndex != o)
        {
            int help = numbers[notSortedIndex];
            numbers[notSortedIndex] = numbers[o];
            numbers[o] = help;
        }
    }
}

// Ausgabe jedes Elements im Array numbers auf stdout
void printArrayOnStdOut(int numbers [], int length)
{
    int pos;

    for (pos=0;pos<length;pos++)
        printf("%d\t", numbers[pos]);

    printf("\n");
}
