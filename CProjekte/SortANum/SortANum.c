#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *basename(char *path)
{
    char *s = strrchr(path, '\\');
    if (!s)
        return strdup(path);
    else
        return strdup(s + 1);
}

void selectionSortArray(int numbers [], int length, bool sortAsc);
void printArrayOnStdOut(int numbers [], int length);

int getLastChar(char * text, char chrSearch)
{
    int last = -1;
    int pos = -1;
    while(text[pos++] != '\0')
    {
        if (text[pos] == chrSearch)
            last = pos;
    }
    return last;
}

int main(int argc, char * argv[])
{
    int * values = malloc(sizeof(int) * argc - 1);
    if (NULL == values)
    {
        printf("Fehler: Speicher konnte nicht allokiert werden!\n");
        return EXIT_FAILURE;
    }
    if (argc == 1)
    {
        printf("Aufruf:\t%s N1 [N2 N3 ...]\n", basename(argv[0]));
        printf("       \tSortiert vorzeichenlose 32bit-Integer.\n", basename(argv[0]));
        return EXIT_SUCCESS;
    } else if (argc > 1)
    {
        for(int pos=1;pos<argc;pos++)
        {
            *(values+pos-1) = atoi(argv[pos]);
        }
        selectionSortArray(values, argc-1, true);
        printArrayOnStdOut(values, argc-1);
    }
    return EXIT_SUCCESS;
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
