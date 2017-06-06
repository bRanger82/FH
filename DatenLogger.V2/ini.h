/**
 * file: ini.h
 *
 * Zweck: Beinhaltet die Prototypen fuer das Auslesen der INI Datei ini.c
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
#include <stdbool.h>
#include "Liste.h"

#define MAX_CSV_LINE_LEN 1024  // maximale Anzahl Zeichen pro Zeile der INI Datei
#define delim "="              // Trennzeichen zwischen Schluessel und Wert

// Struktur fuer das Ablegen der Schluessel/Wert Paare
typedef struct ini_tuple
{
    char * key;     // Schluessel
    char * value;   // Wert
} INI_TUPLE;

// Struktur fuer das Ablegen der Sektionen der INI Datei
typedef struct ini_section
{
    char * section;         // Section [IN]
    void (*action)(void);   // Action, Interface-Routine
    int interval;           // Action, Interval
    SLIST_HEADER * ptuple;  //Liste aller key=value
} INI_SECTION;


INI_SECTION * createINISection(char *, void (*action)(void), int, SLIST_HEADER *); // Erstellt eine INI_SECTION Struktur mit den Parameter-Werten
INI_TUPLE * createKeyValuePair(char *); // Erstellt eine INI_TUPLE Struktur anhand des String, das uebergeben wird
char *trim(char *); //Loescht Leerzeichen, welche sich vor und nach einem String
SLIST_HEADER * ini_parse_file(const char *); // Liest eine INI Datei ein und erstellt eine Struktur aus dieser
INI_TUPLE * findINITupleKey(SLIST * item, char *); // Sucht in einer Liste von INI_TUPLE einen Wert zu einem Key
INI_SECTION * findINISection(SLIST *, char *); // Sucht in einer Liste von INI_SECTION nach einer Sektion
char * getkey(SLIST_HEADER *, char *, char *); // Durchsucht eine eingelesene INI Datei nach einem Key und gibt den zugehoerigen Wert zurueck

