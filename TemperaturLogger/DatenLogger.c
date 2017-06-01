/**
 * file: main.c
 *
 * Zweck: Beinhaltet die Methoden und Funktionen um eine Wetter-Webabfrage zu starten und die Temperatur Werte in eine Datei zu loggen
 *
 * date: 2017-06-01
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung 5.1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_CSV_LINE_LEN 1024
#define delimiter ";"

// Pruefung, ob eine Datei existiert return true, sonst return false
bool fileExists(char * fname)
{
    if( access( fname, F_OK ) != -1 )
    {
        return true;
    } else
    {
        return false;
    }
}

// gibt das aktuelle Datum + Uhrzeit zurueck
char * getCurrentDateTime(void)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char * output = malloc(sizeof(char) * 18);
    if (NULL == output)
    {
        return NULL;
    }
    sprintf(output, "[%02d.%02d.%04d %02d:%02d:%02d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return output;
}

/*
    Wurde eine Webseite mit Wetter-Daten im CSV Format mittels wget auf das lokale Dateisystem heruntergeladen
    liest diese Funktion die Datei ein, sucht nach einem Ort und gibt die Temperatur zurueck
    Parameter:
        filename: der Dateiname zu der Datei mit den Wetter-Daten
        Ort: der Ort, nach dem in der Datei gesucht werden soll
        Temp (Ref): Hier wird die Temperatur zurueck gegeben, wenn sie gefunden wurde
    Rueckgabewert:
        EXIT_FAILURE (stdlib) bei einem Fehler
        EXIT_SUCCESS (stdlib) wenn Erfolgreich
*/
int DatenEinlesen(const char * filename, const char * Ort, double * Temp)
{
    printf("Suche nach %s\n", Ort);

    FILE *fp;

    fp = fopen(filename, "r");

    if (NULL == fp)
    {
        printf("Fehler: File konnte nicht geoeffnet werden!\n");
        return EXIT_FAILURE;
    }

    char buffer[MAX_CSV_LINE_LEN];
    int posTempC = 0;
    char *ptr;
    while(fgets(buffer, MAX_CSV_LINE_LEN, fp) != NULL)
    {
        if (0 == posTempC)
        {
            ptr = strtok(buffer, delimiter);

            //Suche nach der Spalte mit dem Temperatur Wert
            while(ptr != NULL)
            {
                posTempC++;
                if (strstr(ptr, "T") != 0 && strstr(ptr, "C") != 0)
                    break;
                // naechsten Abschnitt erstellen
                ptr = strtok(NULL, delimiter);
            }
        }

        if (strstr(buffer, Ort) != 0)
        {

            int pos = 0;
            // initialisieren und ersten Abschnitt erstellen
            ptr = strtok(buffer, delimiter);

            while(ptr != NULL)
            {
                pos++;
                if (posTempC == pos)
                {
                    // Komma durch Punkt ersetzten atof kann nur mit Punkt umgehen
                    int posKomma;
                    for (posKomma=0;posKomma<strlen(ptr);posKomma++)
                    {
                        if (',' == ptr[posKomma])
                            ptr[posKomma] = '.';
                    }
                    *Temp = atof(ptr);
                    break;
                }
                // naechsten Abschnitt erstellen
                ptr = strtok(NULL, delimiter);
            }
        }
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

/*
    Schreibt das aktuelle Datum+Uhrzeit, den Ort und die Tempertur in eine Logdatei
    Parameter:
     - Logdatei, in die geschrieben werden soll
     - Ort: Standort zu der Temperatur
     - temp: Temperatur-Messwert
    Rueckgabewert:
        EXIT_FAILURE (stdlib) bei einem Fehler
        EXIT_SUCCESS (stdlib) wenn Erfolgreich
*/
int schreibeLog(const char * pfad, const char * Ort, double temp)
{
    FILE * fp = fopen(pfad, "a");
    if (NULL == fp)
    {
        return EXIT_FAILURE;
    }
    char * currTime = getCurrentDateTime();
    if (NULL == currTime)
    {
        fprintf(fp, "<ERROR>\t%s\t%lf\n", Ort, temp);
    } else
    {
        fprintf(fp, "%s\t%s\t%lf\n", currTime, Ort, temp);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

/*
    Laedt eine Webseite auf in ein Verzeichnis herunter
    Parameter:
     - outFile: die Ausgabedatei
     - URL: der Weblink zu der Webressource, welche heruntergeladen werden soll
*/
void downloadURL(char * outFile, char * URL)
{
    char cmdLine[1024] = "wget --output-document=";
    strcat(cmdLine, outFile);
    strcat(cmdLine, " ");
    strcat(cmdLine, URL);
    system(cmdLine);
    printf("%s\n", cmdLine );
}

int main()
{
    // Werte ggf. anpassen!
    char * tmpFileName = "./temperaturen.csv";
    char * outLogFileName = "./tawes1h.log";
    char * URL = "http://www.zamg.ac.at/ogd";
    double temp;
    char * ort = "Salzburg";

    printf("DataLogger\n");

    // Wetter-Daten im CSV Format herunterladen
    downloadURL(tmpFileName, URL);


    if (DatenEinlesen(tmpFileName, ort, &temp) < 0)
    {
        return EXIT_FAILURE;
    }

    if (schreibeLog(outLogFileName, ort, temp) < 0)
    {
        return EXIT_FAILURE;
    }

    //printf("Temperatur: %lf Grad Celsius\n", temp);

    return EXIT_SUCCESS;
}

