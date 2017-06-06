/**
 * file: SList.c
 *
 * Zweck: Beinhaltet Programmcode fuer die Verwendung einer Liste
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
#include "Liste.h"

/**
 * Lokale OPERATIONEN, die privat gehalten werden.
 *------------------------------------------------*/

static SLIST * makeSListNodeLast (void * userData)
{
   SLIST * newPtr;    /* Zeiger auf zugewiesenen Speicher */

   if ((newPtr=(SLIST *) malloc(sizeof(SLIST))) != NULL)
   {
      newPtr->Data = userData;
      newPtr->Next = NULL;
   }
   return (newPtr);
}

/**
*  Globale Operationen
**/

void freeSLIST(SLIST * lst)
{
    if (NULL == lst)
    {
        return;
    }
    SLIST * nextItem = lst->Next;
    free(lst);
    freeSLIST(nextItem);
}

void deleteList(SLIST_HEADER * head)
{
    if (NULL == head)
    {
        return;
    }
    freeSLIST(head->First);
    free(head);
}

// Erstelle einen Header fuer eine Liste
SLIST_HEADER * createSList(void)
{
    SLIST_HEADER * p = (SLIST_HEADER *) malloc(sizeof(SLIST_HEADER));
    if (NULL == p) // Problem bei Speicher-Allokierung
    {
        return p;
    }

    // Standardwerte setzen
    p->Len = 0;
    p->First = NULL;
    p->Last = NULL;

    return p;
}

/* -- Am Ende der Liste ein Element eintragen
    Parameter:
    - aList: Liste, an der das Element angehaengt werden soll
    - userData: Zeiger auf Daten, die in die Liste angefuegt werden sollen
    Rueckgabewerte:
    - Zeiger auf das neue Element wenn erfolgreich, sonst NULL
*/
SLIST * insertLast(SLIST_HEADER* aList, void* userData)
{
    SLIST * newPtr = NULL;

    if (NULL == aList)
    {
        return NULL; // nicht initialisiert
    }

    //neuen Eintrag erstellen
    newPtr = makeSListNodeLast(userData);
    if (NULL == newPtr)
    {
        return NULL;
    }


    if (aList->Len == 0)
    {
        aList->Last = newPtr;
        aList->First = newPtr;
    } else
    {
        aList->Last->Next = newPtr;
        aList->Last = newPtr;
    }

    aList->Len++;

    return (newPtr);
}





