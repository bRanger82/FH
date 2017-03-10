/**
 * file: TwentyOne.c
 *
 * date: 2016­11­17
 * progtimeest.: 60 min
 * progtimereal: 150 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE1­ILV/B 2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define PLAYER_ONE 1 //Spieler 1 wird definiert
#define PLAYER_TWO 2 //Spieler 2 wird definiert
#define MAX_HUMAN_PLAYERS 2 //Maximale Anzahl menschliche Spieler
#define VALID_VALUE_MIN 1 //Mindest-Wert Pruefung fuer Spielereingabe
#define VALID_VALUE_MAX 3 //Maximal-Wert Pruefung fuer Spielereingabe

#define DIFFICULTY_EASY 1 // CPU Spieler Schwierigkeitsgrad Einfach
#define DIFFICULTY_HARD 2 // CPU Spieler Schwierigkeitsgrad Schwierig

#define NUM_MATCH 21 //Anzahl 'Streichhoelzer'

void startGame(int num, int numberHumanPlayers, int difficultyLevel); //startet das Spiel und verwendet den Parameter als Startzahl
int calcNewValue(int currentNum, int decreaseVal); //Berechnet den neuen Spielstand
int nextPlayer(int currentPlayer); //liefert den naechsten Spieler zurueck (fuer den Fall, dass man mehr Spieler implementieren moechte)
int readInputValue(); //liest den auf der Console eingegebenen Wert des Spielers und wertet diesen aus
bool isValidValue(int value); //prueft, ob ein Wert zwischen VALID_VALUE_MIN und VALID_VALUE_MAX liegt (TRUE) oder ausserhalb ist (FALSE)
void showWinnerInfo(int currPlayer); //zeigt die Gewinnermeldung an (fuer den Spieler, der als Parameter angegeben wurde)
int getCPUNextStep(int gameval, int difficulty); //Berechnet den naechsten Schritt des Computer Spuelers
int getConsoleInput(); //Liest die Benutzereingabe ein
int randNum(int limit); //liefert eine Zufallszahl (in Verwendung fuer den CPU Spieler, um einen 'dynamisches' Spieler zu simulieren)
int getNumberPlayers(); //Abfrage Programmstart: wieviele Menschliche Spieler?
int getDifficulty(); //Abfrage Schwierigkeitsgrad Computer Spieler
void showWinnerCPU(); //Wenn schon der Computer gewinnt, dann sollte dieser auch eine eigene Prozedur zum Anzeiger des Gewinners bekommen ;)
void printInfoOnConsole(); //Programm-Start Info dem Benutzer ausgeben

int main()
{
    printInfoOnConsole();
    srand(time(NULL)); //Zufallszahlgenerator initialisieren
    int numberHumanPlayers = getNumberPlayers(); //Anzahl der Spieler festlegen
    int difficultySet = DIFFICULTY_EASY; //default Wert
    if (numberHumanPlayers == 1) //wenn nur ein menschlicher Spieler dann spiele gegen den Computer. In diesem Fall, frage nach der Schwierigkeit
        difficultySet = getDifficulty();

    //starte Spiel mit 21 Streichhoelzer
    startGame(NUM_MATCH, numberHumanPlayers, difficultySet); //starte Spiel

    return EXIT_SUCCESS;
}

void printInfoOnConsole()
{
    printf("Willkommen zu dem Spiel Streichhoelzer runter zaehlen!\n");
    printf("Sie koennen als Spieler gegen Spieler oder gegen Computer spielen!\n");
    printf("Sie koennen das Spiel jederzeit mit STRG+C abbrechen.\n\n");
}

//Abfrage Benutzer und Auswertung der Eingabe auf der Konsole - liefert die Anzahl der menschlichen Spieler zurueck
int getNumberPlayers()
{
    int numPlayers = 0;
    printf("Bitte geben Sie die Anzahl der menschlichen Spieler an (maximal %d)\n", MAX_HUMAN_PLAYERS);
    printf(" Eingabe '1': Spieler gegen den Computer\n");
    printf(" Eingabe '2': Spieler = Spieler gegen Spieler\n");
    while(true)
    {
        numPlayers = getConsoleInput();
        if (numPlayers <1 || numPlayers > MAX_HUMAN_PLAYERS)
        {
            printf("Eingabefehler: die Anzahl der menschlichen Spieler muss zwischen 1 und %d liegen!\n", MAX_HUMAN_PLAYERS);
            printf("Bitte die Eingabe korrigieren:\n");
            continue;
        }
        break;
    }

    return numPlayers;
}


//Abfrage Benutzer und Auswertung der Eingabe auf der Konsole - liefert den gewaehlten Schwierigkeitsgrad fuer den Computerspieler zurueck
int getDifficulty()
{
    int difficulty = 0;
    printf("Bitte geben Sie den Schwierigkeitsgrad (Computer) an.\n");
    printf(" Eingabe '%d': Einfach\n Eingabe '%d': Schwierig\n", DIFFICULTY_EASY, DIFFICULTY_HARD);
    while(true)
    {
        difficulty = getConsoleInput();
        if (difficulty != DIFFICULTY_EASY && difficulty != DIFFICULTY_HARD)
        {
            printf("Eingabefehler: es wurde ein falscher Wert fuer die Schwierigkeit angegeben!\n");
            printf("Bitte die Eingabe korrigieren:\n");
            continue;
        }
        break;
    }

    return difficulty;
}

//Methode welche den Spielablauf implementiert
void startGame(int num, int numberHumanPlayers, int difficultyLevel)
{
    if (num <= 1)
    {
        printf("Die Anzahl der Streichhoelzer muess groesser als 1 sein!\n");
        return;
    }


    int gameVal = num; //Es wird mit gameVal weitergearbeitet, da der Spielstand sich mit dem Spielverlauf aendert
    int currPlayer = nextPlayer(0); //definiere Standardspieler
    bool cpuStepDone = false;

    printf("Das Spiel startet mit menschliche Spieler %d\n", numberHumanPlayers);
    if (numberHumanPlayers == 1)
    {
        printf("Sie spielen gegen den Computer (repraesentiert durch Spieler 2)!\n");
        printf(" *** Viel Glueck, Sie koennten es brauchen ... ;) *** \n");
        switch(difficultyLevel)
        {
            case DIFFICULTY_EASY: printf("Der Schwierigkeitsgrad ist einfach\n"); break;
            case DIFFICULTY_HARD: printf("Der Schwierigkeitsgrad ist schwierig\n"); break;
            default: printf("Der Schwierigkeitsgrad ist nicht definiert!\n Abbruch des Programms!\n"); return; break;
        }
    }

    printf("\n\n"); //fuer eine bessere Uebersicht

    while(true)
    {
        //lese und berechne neuen Spielstand
        int newGameVal = 0;

        if (numberHumanPlayers == 1 && currPlayer != PLAYER_ONE)
        {
            printf("Die neue Zahl lautet: %d, es ist der Computer-Spieler dran.\n", gameVal);
            newGameVal = calcNewValue(gameVal, getCPUNextStep(gameVal, difficultyLevel));;
            cpuStepDone = true;
        }
        else
        {
            printf("Die neue Zahl lautet: %d, es ist der %d. Spieler dran.\n", gameVal, currPlayer);
            newGameVal = calcNewValue(gameVal, readInputValue());
            cpuStepDone = false;
        }


        //wenn der Spielstand kleiner 0 erreicht ist (bspw. bei Spielstand 1 und Eingabe von 3) soll eine Meldung angezeigt und der Spielzug wiederholt werden
        if (newGameVal < 0)
        {
            printf("Das Ergebnis darf nicht kleiner als 0 (Zero) sein!\n");
            continue;
        }
        gameVal = newGameVal;

        //wenn der neue Spielstand 0 ist, hat der aktuelle Spieler gewonnen
        if (gameVal == 0)
            break;

        //naechsten Spieler setzen
        currPlayer = nextPlayer(currPlayer);
    }

    //Gewinner Information auf der Konsole anzeigen
    if (gameVal == 0)
    {
        if (cpuStepDone)
            showWinnerCPU();
        else
            showWinnerInfo(currPlayer);
    }


}

// Berechnet den naechsten Spielzug des Computerspielers, in Anhaengigkeit vom derzeitigen Spielstand und des eingestellten Schwierigkeitsgrades
int getCPUNextStep(int gameval, int difficulty)
{
    if(gameval > 7)
    {
        return randNum(VALID_VALUE_MAX);
    } else if (difficulty == DIFFICULTY_EASY)
    {
        switch (gameval)
        {
            case 7: case 6: case 5: case 4: case 3: return randNum(3); break;
            case 2: return randNum(2); break;
            case 1: return 1; break;
            default: return 1;
        }
    } else if (difficulty == DIFFICULTY_HARD)
    {
        switch(gameval)
        {
            case 7: case 3: return 3; break; //7 - 3 = 4, naechster Schritt: man muss min. 1 angegeben, dann bleiben min. 3 -> Computer gewinnt
            case 6: case 2: return 2; break; //6 - 2 = 4, naechster Schritt: man muss min. 1 angegeben, dann bleiben min. 3 -> Computer gewinnt
            case 5: case 1: return 1; break; //5 - 1 = 4, naechster Schritt: man muss min. 1 angegeben, dann bleiben min. 3 -> Computer gewinnt
            case 4: return 1; break; //Gluecklicher Spieler, denn er Gewinnt
            default: return 1; break;
        }
    }

    return 1; //sollte nie aufgerufen werden, wenn doch wird der kleinst moegliche wert zurueck gegegeben
}

/*
    Funktion liefert eine Zufallszahl zurueck
    Parameter:
        limit: Grenze fuer oberen Wertebereich
    Rueckgabewert:
        Zufallszahl zwischen 1 und den mit limit definiertem Wert
*/
int randNum(int limit)
{
    return (rand() % limit +1);
}

//Zeige Gewinnerinfo auf der Konsole an
void showWinnerInfo(int currPlayer)
{
    printf("\n");
    printf("\n");
    printf("Herzlichen Glueckwunsch!\n");
    printf("Der %d. Spieler hat gewonnen!\n", currPlayer);
    printf("Dem anderen Spieler wuensche ich viel Glueck beim naechsten Versuch ;)\n");
    printf("\n");
    printf("\n");
}

//Zeige Gewinnerinfo auf der Konsole an
void showWinnerCPU()
{
    printf("\n");
    printf("\n");
    printf("Der Computer hat dieses Spiel gewonnen!\n");
    printf("Dieser Algorithmus wuenscht Ihnen viel Glueck beim naechsten Versuch ;)\n");
    printf("\n");
    printf("\n");
}

//Lese Benutzereingabe und pruefe ob die Eingabe eine Zahl ist
int getConsoleInput()
{
    int readValue = 0;
    fflush(stdin);
    if (scanf("%d", &readValue) != 1) //Keine Zahl wurde eingegeben
    {
        printf("Fehler! Der eingegebene Wert ist keine Zahl!\n");
        return -1;
    }
    return readValue;
}

// Lese und pruefe Eingabewert und gebe den Wert zurueck
int readInputValue(int currentValue)
{
    int readValue = 0;
    while(true)
    {
        printf("Bitte Zahl eingeben (1-3): \n");
        readValue = getConsoleInput();
        if (readValue == -1) //Keine Zahl wurde eingegeben
        {
            printf("Fehler! Der eingegebene Wert ist keine Zahl!\n");
            continue;
        }
        if (!isValidValue(readValue)) //Zahl befindet sich nicht im erlaubtem Zahlenbereich
        {
            printf("Fehler: die eingegeben Zahl muss zwischen 1 und 3 liegen!\n");
            continue;
        }
        break; //eingegebener Wert ist OK
    }
    return readValue;
}

// Prueft, ob bei der Eingabe MIN und MAX eingehalten wurde (return TRUE) oder nicht (return FALSE)
bool isValidValue(int value)
{
    return (value >= VALID_VALUE_MIN && value <= VALID_VALUE_MAX);
}

// Berechnet den neuen Spielstand
int calcNewValue(int currentNum, int decreaseVal)
{
    return (currentNum-decreaseVal);
}

// Zeigt auf den naechsten Spieler. Kann mit bis zu x-Spielern erweitert werden
int nextPlayer(int currentPlayer)
{
    switch (currentPlayer)
    {
        case PLAYER_ONE: return PLAYER_TWO; break;
        case PLAYER_TWO: return PLAYER_ONE; break;
        default: return PLAYER_ONE; break;
    }
}
