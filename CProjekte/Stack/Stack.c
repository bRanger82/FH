#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

#define MAX_STACK 100

/* Stack variables */
int stackTop = STACK_EMPTY;   //aktuelle Stack Position
int stack[MAX_STACK];         //Stack Definition


/*
    Element der obersten Stack Position, ohne es aus dem Stack zu entfernen
    Return Werte
        Stack leer: ERROR_STACK
        Stack nicht leer: oberstes Element Stack
*/
int top()
{
    return (!empty()) ? stack[stackTop] : printf("Keine Elemente vorhanden!\n");
}

/*
    Pruefung ob Stack voll ist
    Return Werte
        True wenn Stack voll
        False wenn Stack nicht voll
*/
bool full()
{
    return (stackTop == MAX_STACK) ? true : false;
}

/*
    Pruefung ob Stack leer ist
    Return Werte
        True wenn Stack leer
        False wenn Stack nicht leer
*/
bool empty()
{
    return (stackTop == 0) ? true : false;
}

/*
    Fuegt ein neues Element dem Stack hinzu
    Parameter:
        value ... Wert, dem der Stack hinzugefuegt werden soll
    Return Werte
        ERROR_STACK wenn Stack voll ist
        Das Element wenn erfolgreich
*/
void push(int data)
{
   if(full()) {
      printf("Element mit dem Wert '%d' konnte nicht hinzugefuegt werden, Stack ist voll.\n", data);
   } else
   {
      stack[++stackTop] = data;
   }
}

/*
    Liest das oberste Element aus dem Stack aus und entfernt es aus diesem
    Return Werte:
        ERROR_STACK wenn Stack leer ist
        Das gelesene Element
*/
int pop()
{
   if(empty()) {
      printf("Element konnte nicht gelesen werden, da der Stack leer ist!\n");
      return ERROR_STACK;
   } else
   {
      int data = stack[stackTop--];
      return data;
   }
}

//Gibt die Maxiamle Anzahl des Stack zurueck
int size (void) { return MAX_STACK; }

//Setzt den Stack zurueck ohne den Stack Inhalt zu loeschen
void reset(void) { stackTop = STACK_EMPTY; }

//Gibt die Anzahl der Elemente im Stack zurueck
int length(void) { return stackTop; }

//Setzt den Stack zurueck und loescht auch den Inhalt
void delete(void)
{
    int pos = 0;

    for(pos=length();pos>STACK_EMPTY;--pos)
    {
        printf("Delete item %d with value %d\n", pos, stack[pos]);
        stack[pos] = 0; //Definiert als

    }

    reset();
}


