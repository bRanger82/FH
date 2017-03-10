#include <stdio.h>
#include <stdlib.h>

#define LEN 5


//Aufgabe A7.2
int mystrlen(const char * s)
{
    //Variante 1
    int i = 0;
    while(*(s+i++) != '\0');
    return i;

    /*
    //Variante 2
        char *p = s;
        while(*s++);
        return (s-p);
    */
}

//Aufgabe A7.3
char * mystrncpy(char * dest, const char * src, int n)
{
    int len = mystrlen(src);
    if (n > len)
    {
        printf("Fehler: Laenge groesser als String\n");
        return NULL;
    }
    dest = malloc(n * sizeof(char));

    int pos;
    for(pos=0;pos<n;pos++)
        *(dest + pos) = *(src + pos);

    *(dest + n) = '\0';
    return dest;
}


//Aufgabe A7.4
char * mystrncat(char * dest, const char * src, int n)
{
    int len = mystrlen(src);
    if (n > len)
    {
        printf("Fehler: Laenge groesser als String\n");
        return NULL;
    }
    dest = malloc(n * sizeof(char));

    int pos;
    for(pos=0;pos<n;pos++)
        *(dest + pos) = *(src + pos);

    *(dest + n) = '\0';
    return dest;
}

char * mestrndup(const char * s)
{
  char * p = (char *)malloc(strlen(s)+1);
  if (p == NULL) --> malloc konnte keinen Speicher liefern
      return NULL;
  return (mystrcpy(p, s, strlen(s) + 1));
}

int main2()
{
    char * p = mestrndup("Hallo");
    free(p);
}

//Aufgabe A7.5
char * mystrdup(const char * s)
{
    int pos = 0;
    int len = mystrlen(s);

    char * dest = malloc(len * sizeof(char));

    while(*(s + pos) != '\0')
    {
        *(dest + pos) = *(s + pos);
        pos++;
    }

    *(dest + pos) = '\0';

    return dest;
}

void addiere(int wert, int * x, int * y)
{
    *x = wert * 2;
    *y = wert * 4;
}

void getMinMax(int * arr, int len, int * min, int * max)
{
    *min = *arr;
    *max = *arr;
    int pos;
    for(pos=1;pos<len;pos++)
    {
        if (*min > *(arr + pos))
            *min = *(arr + pos);
        else if (*max < *(arr + pos))
            *max = *(arr + pos);
    }
}

int main()
{

    char src [] = "Test Hallo";
    char * dest;
    dest = mystrdup(src);
    printf("mystrdup %s\n", dest);
    free(dest);


    //
    char * dest2;
    dest2 = mystrncpy(dest2, src, 3);
    printf("mystrncpy %s\n", dest2);
    free(dest2);


    int arr[LEN] = {6, 3, 4, 2, 8};
    int min,  max;
    getMinMax(arr, sizeof(arr)/sizeof(int), &min, &max);
    printf("min = %d, max = %d\n", min, max);
    int x, y;
    addiere(5, &x, &y);
    printf("x = %d, y = %d\n", x, y);
    return EXIT_SUCCESS;
}


/*
int main()
{
    int x = 5;
    int *p;
    int **pp;

    p = &x;

    *p = 25;

    pp = &p;

    **pp =125;

    printf("%d\n", x);
    return 0;
}
*/
