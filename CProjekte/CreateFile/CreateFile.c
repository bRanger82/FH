#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

const int defaultCountNumbers = 100;
const int defaultNumberRange = 100;

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
    printf("Aufruf: %s [-h] [-r <zahl>] [-n <zahl>]\n", basename(path));
    printf("Bedeutung der Parameter:\n");
    printf("\t-n [Anzahl der Zahlen] (Muss groesser 0 sein, Standard: 100), Beispiel: -r 50 (50 Zahlen werden geschrieben)\n");
    printf("\t-r [Zahlenbereich] (Muss groesser 0 sein, Standard: 100), Beispiel: -n 200 (Zahlen von 0 bis 200)\n");
    printf("\t-h Gibt diese Hilfe aus\n");
}

int main(int argc, char *argv[], char ** envp) {
    int i;
    int countNumbers = defaultCountNumbers;
    int numberRange = defaultNumberRange;
    bool errorEingabe = false;

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

    FILE *fp;

    fp = fopen("zahlen.bin", "w");

    if(fp == NULL)
    {
        printf("Fehler: Datei konnte nicht geoeffnet werden.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));

    for(i=1; i<=countNumbers; i++)
    {
        int randNum = rand() % numberRange;
        //fprintf(fp, "%i\n", randNum);
        fwrite(&randNum, sizeof(int), 1, fp);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
