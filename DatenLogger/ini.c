/**
 * file: ini.c
 *
 * Zweck: Beinhaltet die Methoden und Funktionen um eine INI Datei einzulesen und nach einem Wert zu suchen
 *
 * date: 2017-04-25
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "ini.h"


/*
    Erstellt ein INI_SECTION Struktur Element
    Die Parameter werden fuer das Befuellen der Struktur verwendet
    Rueckgabewert:
        Zeiger auf das neue INI_SECTION Element wenn erfolgreich, sonst NULL
*/
INI_SECTION * createINISection(char * section, void (*action)(void), int interval, SLIST_HEADER * ptuple)
{
    INI_SECTION * iniSection = (INI_SECTION *)malloc(sizeof(INI_SECTION));
    if (NULL == iniSection)
    {
        return NULL;
    }
    char * tmp = ( char *)malloc(sizeof(char) * (strlen(section) - 1));
    if (NULL == tmp)
    {
        return NULL;
    }
    // Die eckigen Klammern des Sektionsnamens entfernen
    memcpy(tmp, section+1, strlen(section)-2);
    tmp[strlen(section)-2] = '\0';

    iniSection->section = tmp;
    iniSection->interval = interval;
    iniSection->ptuple = ptuple;

    return iniSection;
}

/*
    Diese Funktion erstellt eine splittet einen String in einen Key und einen Wert auf
    und gibt diesen dann als INI_TUPLE Struktur zurueck
    Paraemter:
        tulpe_line: INI Element, z.B. Key=Wert
    Rueckgabewert:
        Zeiger auf das neue INI_TUPLE Element wenn erfolgreich, sonst NULL
*/
INI_TUPLE * createKeyValuePair(char * tulpe_line)
{
    char *wert = NULL;
    char *schluessel = NULL;

    // initialisieren und ersten Abschnitt erstellen
    schluessel = strtok(tulpe_line, delim); //Schluessel
    if (NULL == schluessel)
    {
        return NULL;
    }

    wert = strtok(NULL, delim); //Wert
    if (NULL == wert)
    {
        return NULL;
    }

    INI_TUPLE * newKVPair = (INI_TUPLE *)malloc(sizeof(INI_TUPLE));
    if (NULL == newKVPair)
    {
        return NULL;
    }
    char * cKey = (char *)malloc(sizeof(char) * (strlen(schluessel) + 1));
    char * cVal = (char *)malloc(sizeof(char) * (strlen(wert) + 1));
    if (NULL == cKey || NULL == cVal)
    {
        return NULL;
    }
    memcpy(cKey, schluessel, strlen(schluessel) + 1);
    memcpy(cVal, wert, strlen(wert) + 1);
    newKVPair->key = cKey;
    newKVPair->value = cVal;
    return newKVPair;
}

/*
 Entfernt die voran- und hintenangestellte Leerzeichen aus einem String
 Parameter:
  - str: Der String mit Leerzeichen vorne und hinten angestellt
 Rueckgabewert:
    str ohne Leerzeichen
*/
char *trim(char *str)
{
  char *end;

  // Loesche Leerzeichen vorne
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // Nur Leerzeichen?
    return str;

  // Loesche Leerzeichen hinten
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Null-String setzten
  *(end+1) = 0;

  return str;
}


SLIST_HEADER * ini_parse_file(const char * iniFile)
{
    SLIST_HEADER * sListHead = createSList();

    if (NULL == sListHead) // Liste konnte nicht erstellt werden
    {
        return NULL;
    }

    FILE *fp;

    fp = fopen(iniFile, "r");

    if (NULL == fp) // Datei konnte nicht gelesen werden
    {
        return NULL;
    }

    char tmpbuffer[MAX_CSV_LINE_LEN]; // Zwischenbuffer fuer das zeilenweise Einlesen der Datei

    SLIST_HEADER * iniTuples = NULL; // Liste von Schluessel/Wert Paaren
    INI_SECTION * ini_sec = NULL; // Ein Element von Schluessel/Wert Paar

    while(fgets(tmpbuffer, MAX_CSV_LINE_LEN, fp) != NULL)
    {
        char * buffer = trim(tmpbuffer); // Entferne voran- und nachgestellte Leerzeichen

        if (NULL == buffer || buffer[0] == '\n') // Zeile enthaelt keine Zeichen
        {
            continue;
        }

        int posEnd = strlen(buffer);
        if (buffer[0] == '[' && buffer[posEnd-1] == ']') // Zeile enthaelt eine Sektion
        {
            iniTuples = createSList();
            if (NULL == iniTuples)
            {
                return NULL;
            }
            ini_sec = createINISection(buffer, NULL, 5, iniTuples); //NULL und 5 sind erdachte Werte
            if (NULL == ini_sec)
            {
                return NULL;
            }
            insertLast(sListHead, ini_sec);
        } else if (strstr(buffer, delim) != 0) // Zeile enthaelt ein Schluessel/Wert Paar
        {
            INI_TUPLE * ini_tup = createKeyValuePair(buffer);
            if (iniTuples != NULL)
            {
                insertLast(iniTuples, ini_tup);
            }
        } else if (buffer[0] == ';') //Zeile enthaelt ein Kommentar
        {
            // Behandlung fuer Kommentare
        }
    }

    fclose(fp);

    return sListHead;
}

// Suche nach einer Tuple in einer Liste von Elementen
INI_TUPLE * findINITupleKey(SLIST * item, char * key)
{
    if (NULL == item)
    {
        return NULL; // Es gibt kein Element, welches zur Suche passt
    }

    INI_TUPLE * iniTup = (INI_TUPLE *)item->Data;
    if (strcmp(iniTup->key, key) == 0)
    {
        return iniTup; // Element gefunden
    } else
    {
        return findINITupleKey(item->Next, key); // Wert nicht gefunden, suche in naechstem Element
    }

}

// Suche nach einer Sektion in einer Liste von Elementen
INI_SECTION * findINISection(SLIST * item, char * section)
{
    if (NULL == item)
    {
        return NULL; // Es gibt kein Element, welches zur Suche passt
    }

    INI_SECTION * retVal = (INI_SECTION *)item->Data;
    if (NULL == retVal)
    {
        return NULL;
    }

    if (strcmp(retVal->section, section) == 0)
    {
        return retVal; // Element gefunden
    } else
    {
        return findINISection(item->Next, section); // Wert nicht gefunden, suche in naechstem Element
    }

}

/* Durchsucht eine INI-Struktur nach einer Sektion und Schluessl und gibt den zugehoerigen Wert zurueck
   Wenn nichts gefunden wurde wird NULL zurueck gegeben
*/
char * getkey(SLIST_HEADER * root, char * section, char * key)
{
    // root ist NULL oder leer
    if (NULL == root)
    {
        return NULL;
    }
    if (root->Len == 0)
    {
        return NULL;
    }

    // Suche zuerst in Sektion
    INI_SECTION * iniSec = findINISection(root->First, section);
    if (NULL == iniSec)
    {
        return NULL; // die Sektion gibt es nicht in der Datei
    }

    // Suche der gefundenen Sektion nach dem Key
    INI_TUPLE * iniTup = findINITupleKey(iniSec->ptuple->First, key);

    if (NULL == iniTup)
    {
        return NULL; // Key nicht gefunden
    }

    //Es wurde ein Wert gefunden
    return iniTup->value;
}
