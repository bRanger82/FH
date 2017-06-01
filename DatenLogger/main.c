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
#include "ini.h"

void testGefundenOK(SLIST_HEADER * head);      // Testprozedur, fur einen Wert der gefunden wird
void testGefundenNICHTOK(SLIST_HEADER * head); // Testprozedur, fur einen Wert der _nicht_ gefunden wird

int main()
{
    char * filename = "datenlogger.ini";

    SLIST_HEADER * head = ini_parse_file(filename);
    if (NULL == head) // Es gab einen Fehler beim Lesen der Datei bzw. beim Erstellen der Struktur
    {
        printf("Fehler beim Einlesen der Datei %s!\n", filename);
        return EXIT_FAILURE;
    }

    // ---- Start Testablauf ---
    printf("Die Datei %s wurde erfolgreich eingelesen!\n", filename);
    puts("");
    puts("Testlauf testGefundenOK:");
    testGefundenOK(head);
    puts("Testlauf testGefundenNICHTOK:");
    testGefundenNICHTOK(head);
    puts("");
    // ---- ENDE Testablauf ---

    return EXIT_SUCCESS;
}

// Testprozedur, fur einen Wert der gefunden wird
void testGefundenOK(SLIST_HEADER * head)
{
    char * suchNachKeyWert = "pidfile"; // Suche nach dem Schluessen

    char * tmp = getkey(head, "datenlogger", suchNachKeyWert); // Suche den Schluessel in folgender Sektion
    if (NULL != tmp)
    {
        //Wert gefunden
        printf("\tDer Wert zu dem Key '%s' ist: %s\n", suchNachKeyWert, tmp);
    } else
    {
        printf("\tDer Key '%s' wurde nicht gefunden!\n", suchNachKeyWert);
    }
}

// Testprozedur, fur einen Wert der _nicht_ gefunden wird
void testGefundenNICHTOK(SLIST_HEADER * head)
{
    char * suchNachKeyWert = "pidfxile"; // Suche nach dem Schluessen (der nicht existiert)

    char * tmp = getkey(head, "datenlogger", suchNachKeyWert); // Suche den Schluessel in folgender Sektion
    if (NULL != tmp)
    {
        printf("\tDer Wert zu dem Key '%s' ist: %s\n", suchNachKeyWert, tmp);
    } else
    {
        printf("\tDer Key '%s' wurde nicht gefunden!\n", suchNachKeyWert);
    }
}
