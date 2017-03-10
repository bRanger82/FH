#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int verdopple(int);
int mystrlen(char str []);
void test();
int myStrCopy(char dest[], char source []);
int myStrCat(char dest[], char source []);

int main()
{
    char str[] = "Hallo";
    printf("Laenge %d\n", mystrlen(str));

    printf("%d\n", verdopple(2));
    printf("Hello world!\n");
    return 0;
}

int verdopple(int z)
{
    return z*z;
}

int mystrlen(char str [])
{
    int i = 0;
    while(str[i] != '\0')
        i++;
    return i;
}


void test()
{
    char src[MAX] = "Hallo";
    char des[MAX];
}


int myStrCopy(char dest[], char source [])
{
    int i = 0;
    for (i = 0; i <= mystrlen(source); i++)
        dest[i] = source[i];
    return i;
}

int myStrCat(char dest[], char source [])
{
    int i = 0;
    int offset = mystrlen(dest);
    for (i = 0; i <= mystrlen(source); i++)
        dest[offset+i] = source[i];
    return i;
}
