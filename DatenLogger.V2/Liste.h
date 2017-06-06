/**
 * file: Liste.h
 *
 * Zweck: Beinhaltet die Prototypen fuer die Verwendung der Liste
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

 // Struktur, Definition Aufbau Element in der Liste
struct SList
{
    void * Data;
    struct SList *Next;
    struct SList *Prev;
}; typedef struct SList SLIST;

 // Struktur, Definition Aufbau Header der Liste
struct SList_Header
{
    int Len;
    SLIST *First, *Last;
}; typedef struct SList_Header SLIST_HEADER;

extern SLIST_HEADER *createSList(void); // Liste erstellen
extern SLIST *insertLast(SLIST_HEADER*, void*); // Ein Element einer Liste hinzufuegen
void freeSLIST(SLIST * lst); // SLIST Element Serie aus dem Speicher freigeben
void deleteList(SLIST_HEADER * head); //
