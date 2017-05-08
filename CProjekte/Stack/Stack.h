#include <stdbool.h>

#define ERROR_STACK -1      // Fehlercode bei Fehlerfall Stack
#define STACK_EMPTY 0

/* Prototypes fuer Stack */
void push(int data);    //fuege element hinzu
int pop(void);          //lese element und entferne es aus dem Stack
int top(void);          //lese oberstes element ohne es zu entfernen
bool empty(void);       //prueft, ob der stack leer ist
int size (void);        //Maximale laenge des Stacks
int length(void);       //Anzahl der Elemente im Stack
void reset(void);       //Zuruecksetzen des Stack ohne den Inhalt zu loeschen
void delete(void);      //Zuruecksetzen des Stack und Inhalt wird loeschen
bool full(void);        //prueft, ob der stack voll ist

