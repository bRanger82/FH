#include <stdio.h>
#include <stdlib.h>

#define SIZE_X 3
#define SIZE_Y 3

int main()
{
    int matrix[SIZE_X][SIZE_Y] = {{1, 3, -4}, {1, 1, -2}, {-1, -2, 5}};
    int x = 0;
    int y = 0;

    for (x=0;x<SIZE_X;x++)
    {
        printf("(");
        for (y=0;y<SIZE_Y;y++)
        {
            printf("%6d ", matrix[x][y]);
        }
        printf(") \n");
    }
    return 0;
}
