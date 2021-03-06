#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "SList.h"

SLIST_HEADER * queueHead = NULL;

// Hinzufuegen eines neuen Eintrags
void * put(void * data)
{
    if (NULL == queueHead) // queue initialisiert?
        queueHead = createSList();

    if (NULL == queueHead)  //konnte queue erfolgreich angelegt werden?
        return NULL;

    insertLast(queueHead, data);
}

// Holen eines Eintrags aus dem FIFO Speicher und entfernt es
void * get(void)
{
    return NULL; //TODO
}

// Abfragen des letztes hinzugefuegtem Element ohne es zu entfernen
void * last(void)
{
    return NULL; //TODO
}

// Abfragen des naechsten Elements ohne es zu entfernen
void * next(void)
{
    return NULL; //TODO
}

// Abfragen, ob FIFO Speicher leer ist
bool Qempty(void)
{
    return (queueHead->Len == 0) ? true : false;
}

// Abfragen, wieviele Eintrage im FIFO Speicher abgelegt sind
int Qlength(void)
{
    return queueHead->Len;
}

// Loeschen des gesamten FIFO Speichers
void Qdelete(void)
{
    return;
}
