#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void selectionSortArray(int numbers [], int length, bool sortAsc); //SelectionSort Methode
void printArrayOnStdOut(int numbers [], int length); // Ausgabe jedes Elements im Array numbers auf stdout

#define MAX_ARR 6

int arrTest[MAX_ARR] = {41, 4, 15, 8, 14, 25};   // Test Array 1
//int arrTest[MAX_ARR] = {8, 8, 8, 8, 8, 8};       // Test Array 2
//int arrTest[MAX_ARR] = {9, 8, 7, 6, 5, 4};       // Test Array 3


int main()
{
    printf("Vor dem Sortieren:\n");
    printArrayOnStdOut(arrTest, MAX_ARR);

    selectionSortArray(arrTest, MAX_ARR, true);

    printf("Nach dem Sortieren:\n");
    printArrayOnStdOut(arrTest, MAX_ARR);

    return EXIT_SUCCESS;

}

// Ausgabe jedes Elements im Array numbers auf stdout
void printArrayOnStdOut(int numbers [], int length)
{
    int pos;

    for (pos=0;pos<length;pos++)
        printf("\tPosition %d ist %d\n", pos+1, arrTest[pos]);

    printf("\n");
}

/*
    Sortiert einen Array entweder aufsteigend (sortAsc = true) oder absteigend (sortAsc = false)
*/
void selectionSortArray(int numbers [], int length, bool sortAsc)
{
    int i, o, notSortedIndex; //inner, outer, unsorted-index front
    int AnzahlDurchlaeufe = 0;

    //printf("\n\nSTART Sortieralgo\n\n");

    for(o=0;o<(length-1);o++)
    {
        printf("Durchlauf (outer): %d\n", ++AnzahlDurchlaeufe);
        notSortedIndex = o;
        for(i=o+1;i<length;i++)
        {
            //printf("\tVergleiche Zahl %d mit %d\n", numbers[notSortedIndex], numbers[i]);
            if (sortAsc ? (numbers[notSortedIndex] > numbers[i]) : (numbers[notSortedIndex] < numbers[i]))
            {
                notSortedIndex = i;
                //printf("\t\tSetze notSortedIndex-Position auf den Wert %d\n", notSortedIndex);
            }
        }
        if (notSortedIndex != o)
        {
            //printf("Ersetze %d mit %d\n", numbers[notSortedIndex], numbers[o]);
            int help = numbers[notSortedIndex];
            numbers[notSortedIndex] = numbers[o];
            numbers[o] = help;
        }
        printArrayOnStdOut(arrTest, MAX_ARR);
    }
    //printf("\nENDE Sortieralgo, *** Anzahl Durchlaeufe: %d ***\n\n", AnzahlDurchlaeufe);
    //printf("Landau hat den Wert: %d\n", Landau);
}
