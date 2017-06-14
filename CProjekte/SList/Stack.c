#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"
#include "SList.h"

SLIST_HEADER * stackHead = NULL;

/*
    Element der obersten Stack Position, ohne es aus dem Stack zu entfernen
    Return Werte
        Stack leer: ERROR_STACK
        Stack nicht leer: oberstes Element Stack
*/
void * top()
{
    if (0 == stackHead->Len)
        return NULL; //TODO
    SLIST * element = stackHead->Last;
    return element->Data;
}


/*
    Pruefung ob Stack leer ist
    Return Werte
        True wenn Stack leer
        False wenn Stack nicht leer
*/
bool empty()
{
    return (0 == stackHead->Len) ? true : false; // TODO
}

/*
    Fuegt ein neues Element dem Stack hinzu
    Parameter:
        value ... Wert, dem der Stack hinzugefuegt werden soll
    Return Werte
        ERROR_STACK wenn Stack voll ist
        Das Element wenn erfolgreich
*/
void * push(void * data)
{
    if (NULL == stackHead) //stack bereits erstellt?
        stackHead = createSList();
    if (NULL == stackHead) //konnte stack erfolgreich angelegt werden?
        return NULL;
    return insertLast(stackHead, data);
}

/*
    Liest das oberste Element aus dem Stack aus und entfernt es aus diesem
    Return Werte:
        ERROR_STACK wenn Stack leer ist
        Das gelesene Element
*/
void * pop()
{
   if (0 == stackHead->Len)
        return NULL; //TODO

    return deleteLast(stackHead);
}


//Gibt die Anzahl der Elemente im Stack zurueck
int length(void)
{
    return stackHead->Len; //TODO
}

//Setzt den Stack zurueck und loescht auch den Inhalt
void delete(void)
{
    if (0 == stackHead->Len)
        return;

    SLIST * element = stackHead->Last;
    while (NULL != element)
    {
        deleteLast(stackHead);
    }
}


