#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

void UPNCalculator();
void runStackTest(void);

int main()
{
    UPNCalculator();
    return EXIT_SUCCESS;
}

bool strCom(char arr1[], char arr)
{

}

void UPNCalculator()
{
    while(1)
    {
        char arr[100];

        if (scanf("%s" , &arr) != 1)
            continue;

        if (arr[0] = '=')
            break;
        else if (arr[0] == '+')
            push(pop() + pop());
        else if (arr[0] == '-')
            push(pop() + pop());
    }
    int eingabe = 0;
    char ch = ' ';
    while((ch=fgetc(stdin)) != '=')
    {
        switch(ch)
        {
            case ' ': break;
            case '+': push(pop() + pop()); break;
            case '*': push(pop() * pop()); break;
            case '/': push(pop() / pop()); break;
            case '-': push(pop() - pop()); break;
            case '0': push(0); break;
            case '1': push(1); break;
            case '2': push(2); break;
            case '3': push(3); break;
            case '4': push(4); break;
            case '5': push(5); break;
            case '6': push(6); break;
            case '7': push(7); break;
            case '8': push(8); break;
            case '9': push(9); break;
            default: break;
        }
    }

    printf("Ergebnis %d\n", pop());
    reset();

}

void runStackTest(void)
{
    printf("%d\n", pop());
    printf("size() = %d\n", size());
    push(3);
    printf("length() = %d\n", length());
    push(5);

    printf("length() = %d\n", length());

    printf("pop() = %d\n", pop());
    reset();
    printf("length after reset() = %d\n", length());

    push(1);
    push(2);

    push(3);
    push(4);
    push(5);

    printf("length() after fill data = %d\n", length());

    printf("top() = %d\n", top());
    printf("pop() = %d\n", pop());
    printf("pop() = %d\n", pop());

    delete();
    printf("length() after delete = %d\n", length());

}
