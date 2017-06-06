/**
 * file: main.c
 *
 * Zweck: Beinhaltet das Hauptprogramm fuer das Auslesen und das Suchen in einer INI Datei
 *
 * date: 2017-06-02
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung 5.2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "ini.h"


void testGefunden(SLIST_HEADER *, char *, char *);      // Testprozedur, fur einen Wert der gefunden wird


bool fileExists(char * filename)
{
    return ( access( filename, F_OK ) != -1 );
}

bool isINIFilename(char * filename)
{
    if (NULL == filename)
    {
        return false;
    }

    int len = strlen(filename);
    if (len < 4)
    {
        return false;
    }

    char * allowExt = ".ini";

    return (strcmpi(filename+(len-4), allowExt) == 0);
}



int main(int argc, char * argv[])
{

    if (argc < 2)
    {
        printf("Fehler: es wurde kein Dateinamen angegeben!\n");
        return EXIT_FAILURE;
    }

    char * filename = NULL;
    char * searchPhrase = NULL;
    char * section = NULL;

    int pos;

    for (pos=1;pos<(argc-1);pos++)
    {
        if (strcmp("-f", argv[pos]) == 0)
        {
            filename = argv[pos+1];
        } else if (strcmp("-k", argv[pos]) == 0)
        {
            searchPhrase = argv[pos+1];
        } else if (strcmp("-s", argv[pos]) == 0)
        {
            section = argv[pos+1];
        }
    }

    if (NULL == filename || NULL == searchPhrase || NULL == section)
    {
        printf("Fehler: Parameter wurden nicht angegeben!\n");
        return EXIT_FAILURE;
    }

    //char * filename = argc[1]; //"datenlogger.ini";
    if (!fileExists(filename) || !isINIFilename(filename))
    {
        printf("Fehler: die Datei %s kann nicht gelesen werden.\n", filename);
        return EXIT_FAILURE;
    }

    SLIST_HEADER * head = ini_parse_file(filename);
    if (NULL == head) // Es gab einen Fehler beim Lesen der Datei bzw. beim Erstellen der Struktur
    {
        printf("Fehler beim Einlesen der Datei %s!\n", filename);
        return EXIT_FAILURE;
    }

    // ---- Start Testablauf ---
    printf("Die Datei %s wurde erfolgreich eingelesen!\n", filename);
    puts("");
    puts("Testlauf testGefunden:");
    testGefunden(head, searchPhrase, section);
    puts("");
    // ---- ENDE Testablauf ---
    deleteList(head);
    return EXIT_SUCCESS;
}

// Testprozedur, fur einen Wert der gefunden wird
void testGefunden(SLIST_HEADER * head, char * suchNachKeyWert, char * section)
{

    char * tmp = getkey(head, section, suchNachKeyWert); // Suche den Schluessel in folgender Sektion
    if (NULL != tmp)
    {
        //Wert gefunden
        printf("\tDer Wert zu dem Key '%s' ist: %s\n", suchNachKeyWert, tmp);
    } else
    {
        printf("\tDer Key '%s' wurde nicht gefunden!\n", suchNachKeyWert);
    }
}
