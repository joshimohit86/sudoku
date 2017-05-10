#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int maxRows;
void printSudoku (int **sudoku);

bool isUniqueInRow (int **input1, int row, int numberToBeUsed)
{
    int sud_i = 0;
    for (sud_i = 0; sud_i < maxRows; sud_i++)
        if (numberToBeUsed == input1[row][sud_i])
            return false;
    return true;
}

bool isUniqueInColumn (int **input1, int column, int numberToBeUsed)
{
    int sud_i = 0;
    for (sud_i = 0; sud_i < maxRows; sud_i++)
    {
        //printf ("\nsudoku[%d][%d]: %d, numberToBeUsed: %d\n\n", sud_i, column, input1[sud_i][column],  numberToBeUsed);
        if (numberToBeUsed == input1[sud_i][column])
            return false;
    }
    return true;
}

int getRowNumbersInBox (int numberOfRows);

void getBoxMinMax(int row, int column, int *rowMin, int *rowMax, int *columnMin, int *columnMax)
{
    int maxRowsInBox = getRowNumbersInBox (maxRows);
    *rowMin = row - (row % maxRowsInBox);
    *columnMin = column - (column % maxRowsInBox);
    *rowMax = *rowMin + (row % maxRowsInBox);
    *columnMax = *columnMin + (column % maxRowsInBox);
}

bool isUniqueInBox (int **input1, int row, int column, int numberToBeUsed)
{
    int rowMin = 0,
        rowMax = 0,
        columnMin = 0,
        columnMax = 0;

    int sud_i = 0,
        sud_j = 0;

    static int count = 0;
    getBoxMinMax (row, column, &rowMin, &rowMax, &columnMin, &columnMax);
    int index = 0;
    for (index = 0; index < maxRows; index++)
    {
        sud_i = rowMin + index/getRowNumbersInBox (maxRows);
        sud_j = columnMin + index%getRowNumbersInBox (maxRows);
        if (numberToBeUsed == input1[sud_i][sud_j])
            return false;
    }
    return true;
}

bool canWriteNumber (int **input1, int rowId, int columnId, int numberToBeUsed)
{
    if (!isUniqueInRow (input1, rowId, numberToBeUsed))
        return false;
    else if (!isUniqueInColumn (input1, columnId, numberToBeUsed))
        return false;
    else if (!isUniqueInBox (input1, rowId, columnId, numberToBeUsed))
        return false;
    return true;
}

bool fillSudoku (int **input1, int rowId, int columnId)
{
}

bool checkSudokuForEmpty (int **input1, int *rowId, int *columnId)
{
    int sud_i = 0,
        sud_j = 0;
    for (sud_i = 0; sud_i < maxRows; sud_i++)
        for (sud_j = 0; sud_j < maxRows; sud_j++)
            if (0 == input1[sud_i][sud_j])
            {
                *rowId = sud_i;
                *columnId = sud_j;
                return true;
            }
    return false;
}

bool solveSudoku (int input1_size_rows, int input1_size_cols, int **input1)
{
    int rowId = 0;
    int columnId = 0;
    if (!checkSudokuForEmpty (input1, &rowId, &columnId))
        return true;

    /* check with each number if that can be filled */
    int numberToBeUsed = 0;
    for (numberToBeUsed = 1; numberToBeUsed <= maxRows; numberToBeUsed++)
    {
        if (canWriteNumber(input1, rowId, columnId, numberToBeUsed))
        {
            input1[rowId][columnId] = numberToBeUsed;
            if (solveSudoku (input1_size_rows, input1_size_cols, input1))
            {
                return true;
            }
        }
        input1[rowId][columnId] = 0;
    }
    return false;

}

bool isPerfectSquare (int number)
{
    switch (number)
    {
        case 4:
        case 9:
        case 16:
        case 25:
        case 36:
        case 49:
        case 64:
        case 81:
        case 100:
        case 121:
        case 144:
        case 169:
        case 196:
        case 225:
        case 256:
        case 289:
        case 324:
        case 361:
        case 400:
            {
                return true;
            }
        default:
            {
                printf ("%d not a perfect square\n", number);
                return false;
            }
    }
}


void printSudoku (int **sudoku)
{
    int sud_i = 0,
        sud_j = 0;
    for (sud_i = 0; sud_i < maxRows; sud_i++)
    {
        for (sud_j = 0; sud_j < maxRows; sud_j++)
            printf ("%d ", sudoku[sud_i][sud_j]);
        printf ("\n");
    }
}

int getRowNumbersInBox (int numberOfRows)
{
    switch (numberOfRows)
    {
        case 4:
                return 2;
        case 9:
                return 3;
        case 16:
                return 4;
        case 25:
                return 5;
        case 36:
                return 6;
        case 49:
                return 7;
        case 64:
                return 8;
        case 81:
                return 9;
        case 100:
                return 10;
        case 121:
                return 11;
        case 144:
                return 12;
        case 169:
                return 13;
        case 196:
                return 14;
        case 225:
                return 15;
        case 256:
                return 16;
        case 289:
                return 17;
        case 324:
                return 18;
        case 361:
                return 19;
        case 400:
                return 20;
        default:
                return 0;
    }
}

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapRight (int **sudoku, int rowStart, int columnStart, int count)
{
    int i = 0,
        j = 0;
    for (i = rowStart; i < rowStart + count; i++)
        for (j = columnStart; j < columnStart + count; j++)
            swap( &sudoku[i][j], &sudoku[i][j+count]);
}

bool isValidRow (int **sudoku, int row)
{
    bool validFlag[maxRows];
    int element = 0;
    memset (validFlag, 0, maxRows*sizeof(bool));
    int i = 0;
    for (i = 0; i < maxRows; i++)
    {
        element = sudoku[row][i];
        if (validFlag[element - 1])
            return false;
        validFlag[element - 1] = true;
    }
    return true;
}

void swapDown (int **sudoku, int rowStart, int columnStart, int count)
{
    int i = 0,
        j = 0;
    for (i = rowStart; i < rowStart + count; i++)
        for (j = columnStart; j < columnStart + count; j++)
            swap( &sudoku[i][j], &sudoku[i+count][j]);
}

bool isValidColumn (int **sudoku, int column)
{
    bool validFlag[maxRows];
    memset (validFlag, 0, maxRows*sizeof(bool));
    int element = 0;
    int i = 0;
    for (i = 0; i < maxRows; i++)
    {
        element = sudoku[column][i];
        if (validFlag[element])
            return false;
        validFlag[element] = true;
    }
    return true;
}

bool swapBoxes (int **sudoku)
{
    int rowMin, rowMax, columnMin, columnMax;
    int totalBoxes = maxRows;
    int numberOfBoxesRowwise = getRowNumbersInBox(maxRows);
    int numberOfBoxesColumnwise = numberOfBoxesRowwise;
    bool validFlag = true;
    int startingRow = 0,
        startingColumn = 0;
    int i = 0,
        j = 0;
    for (i = 0; i < numberOfBoxesRowwise; i++)
    {
        for (j = 0; j < numberOfBoxesColumnwise; j++)
        {
            // Swap with right box
            if ((j+1)*numberOfBoxesRowwise < maxRows)
                swapRight (sudoku, i*numberOfBoxesRowwise, j*numberOfBoxesColumnwise, numberOfBoxesRowwise);
            // Check Uniqueness in columns
            int k = 0;
            for (k = i*numberOfBoxesRowwise; k < (i+1)*numberOfBoxesRowwise; k++)
                if (!isValidRow (sudoku, k))
                    validFlag = false;
            if ((j+1)*numberOfBoxesRowwise < maxRows)
                swapRight (sudoku, i*numberOfBoxesRowwise, j*numberOfBoxesColumnwise, numberOfBoxesRowwise);
            if (validFlag)
                return validFlag;
            // Swap with box below
            if ((j+1)*numberOfBoxesColumnwise < maxRows)
                swapDown (sudoku, j*numberOfBoxesColumnwise, i*numberOfBoxesRowwise, numberOfBoxesRowwise);
            // Check for uniqueness in rows
            for (k = j*numberOfBoxesColumnwise; k < (j+1)*numberOfBoxesColumnwise; k++)
                if (!isValidColumn (sudoku, k))
                    validFlag = false;
            if ((j+1)*numberOfBoxesColumnwise < maxRows)
                swapDown (sudoku, j*numberOfBoxesColumnwise, i*numberOfBoxesRowwise, numberOfBoxesRowwise);
            if (validFlag)
                return validFlag;
        }
    }
    return false;
}

bool checkMagicSudoku (int **sudoku)
{
    if (swapBoxes (sudoku))
        return true;
    return false;
}

bool validateElements(int input1_size_rows, int input1_size_cols, int** input1)
{
    int i = 0,
        j = 0;
    for (i = 0; i < input1_size_rows; i++)
        for (j = 0; j < input1_size_cols; j++)
            if (input1[i][j] < 0 || input1[i][j] > input1_size_rows)
                return false;
    return true;
}

int SolveMagicSquare(int input1_size_rows, int input1_size_cols, int** input1)
{
    /* Iterate through the sudoku to check if any invalid character is present */
    if (!validateElements (input1_size_rows, input1_size_cols, input1))
        return 0;
    /* Check rows == columns and for perfect square */
    if ((input1_size_rows == input1_size_cols) && (isPerfectSquare(input1_size_rows)))
    {
        maxRows = input1_size_rows;
        if (solveSudoku (input1_size_rows, input1_size_cols, input1))
        {
            //printSudoku (input1);
            if (checkMagicSudoku (input1))
                return 1;
        }
    }
    return 0;
}

int main() {
    int output = 0;
    int ip1_rows = 0;
    int ip1_cols = 0;
    scanf("%d", &ip1_rows);
    scanf("%d", &ip1_cols);

    int** ip1 = (int**)malloc(ip1_rows*sizeof(int*));
    int ip1_init_i=0;
    for(ip1_init_i=0 ; ip1_init_i<ip1_rows ; ++ip1_init_i)
    {
        ip1[ip1_init_i] = (int*)malloc(ip1_cols*(sizeof(int)));
    }

    int ip1_i, ip1_j;
    for(ip1_i = 0; ip1_i < ip1_rows; ip1_i++) {
        for(ip1_j = 0; ip1_j < ip1_cols; ip1_j++) {
            int ip1_item;
            scanf("%d", &ip1_item);

            ip1[ip1_i][ip1_j] = ip1_item;
        }
    }
    //printSudoku (ip1);
    output = SolveMagicSquare(ip1_rows, ip1_cols,ip1);
    printf ("Filled sudoku is->\n");
	printSudoku (ip1);
    if (output)
		printf("Sudoku is magic sudoku i.e., having a box which can be swapped with adjecent box and the complete matrix is again a valid sudoku\n", output);
    else
		printf("Sudoku is not magic sudoku i.e., not having a box which can be swapped with adjecent box and the complete matrix is again a valid sudoku\n", output);
    return 0;
}


