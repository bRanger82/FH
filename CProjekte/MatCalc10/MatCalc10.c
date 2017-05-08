#include <stdio.h>
#include <stdlib.h>


#define MAX_DIM_X 10
#define MAX_DIM_Y 10

/*
Eingabeformat:
<1><2><3>
<2><3><5>
*/

int readInput(int matrix[MAX_DIM_X][MAX_DIM_Y]);
void printMatrix(int matrix1[MAX_DIM_X][MAX_DIM_Y], int matrix2[MAX_DIM_X][MAX_DIM_Y], char op, int XMax, int YMax);
char readOperator();

int dimXMax = 0;
int dimYMax = 0;
int matrix1[MAX_DIM_X][MAX_DIM_Y] = {0};// = {{1, 3, -4}, {1, 1, -2}, {-1, -2, 5}};
int matrix2[MAX_DIM_X][MAX_DIM_Y] = {0};

int main()
{
    if (readInput(matrix1) == EXIT_FAILURE)
        return EXIT_FAILURE;

    char op = readOperator();
    if (op != '+' && op != '*')
    {
        printf("Eingabefehler: Operator nicht definiert!\n");
        return EXIT_FAILURE;
    }

    if (readInput(matrix2) == EXIT_FAILURE)
        return EXIT_FAILURE;

    printMatrix(matrix1, matrix2, op, dimXMax, dimYMax);

    return EXIT_SUCCESS;
}

char readOperator()
{
    char op;

    if (scanf("\n<%c>", &op) != 1)
    {
        printf("Eingabefehler: Operator nicht definiert!\n");
        return EXIT_FAILURE;
    }
    return op;
}

int readInput(int matrix[MAX_DIM_X][MAX_DIM_Y])
{
    int dimX = 0;
    int dimY = 0;

    if (scanf("\n<%d> <%d>", &dimX, &dimY) != 2)
    {
        printf("Eingabefehler Array 1 Definition!\n");
        return EXIT_FAILURE;
    }

    if (dimX > dimXMax)
        dimXMax = dimX;

    if(dimY > dimYMax)
        dimYMax = dimY;

    if (dimX < 1 || dimX > MAX_DIM_X || dimY < 1 || dimY > MAX_DIM_Y)
    {
        printf("Fehler: Dimensionen (min: 1x1, max: %dx%d) nicht eingehalten!\n", MAX_DIM_X, MAX_DIM_Y);
        return EXIT_FAILURE;
    }

    int x = 0;
    int y = 0;
    for (x=0;x<dimX;x++)
    {
        for (y=0;y<dimY;y++)
        {
            if (scanf("%d", &matrix[x][y]) != 1)
            {
                printf("Eingabefehler Array!\n");
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

void printMatrix(int matrix1[MAX_DIM_X][MAX_DIM_Y], int matrix2[MAX_DIM_X][MAX_DIM_Y], char op, int XMax, int YMax)
{
    int x = 0;
    int y = 0;
    int matrixRes[MAX_DIM_X][MAX_DIM_Y] = {0};

    //printf("\n\n Ergebnis: \n");
    for (x=0;x<XMax;x++)
    {
        printf("(");
        for (y=0;y<YMax;y++)
        {
            if (op == '+')
                matrixRes[x][y] = matrix1[x][y] + matrix2[x][y];
            else if (op == '*')
            {
                matrixRes[x][y] = matrix1[x][y] * matrix2[x][y];
            }
            printf("%6d%s", matrixRes[x][y], (y==YMax-1) ? "": ",");
        }
        printf(")\n");
    }
}


