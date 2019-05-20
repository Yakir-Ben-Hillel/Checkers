#include "PrototypesProject.h"

void PrintOpener();
void fillStartingBoard(Board *board);
int main()
{
    // Opener- Checkers game
    PrintOpener();
    // Fill board
    Board startingBoard = {
        {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
        {'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
        {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
        {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
        {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
    };

    printf("Starting Board\n");
    printBoard(startingBoard);
    printf("\n\n\n");

    // for end cases
    Board testBoard = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', 'T', ' ', ' ', ' ', ' ', ' '},
        {' ', 'B', ' ','B', ' ', 'T', ' ', ' '},
        {'T', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'B', ' ', 'T', ' ', ' '},
        {'B', ' ', 'T', ' ', 'B', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B'},
        {' ', ' ', 'T', ' ', ' ', ' ', ' ', ' '},
    };
    printBoard(testBoard);
    printf("\n\n\n");

    checkersPos src1, src2;
    // test1-top-middle board
    src1.row = 'F';
    src1.col = '1';
    // test2- bottom-middleside
    src2.row = 'E';
    src2.col = '6';

    printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

    SingleSourceMovesTree *movesTree1 = NULL;
    SingleSourceMovesTree *movesTree2 = NULL;
    movesTree1 = FindSingleSourceMoves(startingBoard, src1);
    movesTree2 = FindSingleSourceMoves(testBoard, src2);

    printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

    printTreeInOrder(movesTree1);
    printTreeInOrder(movesTree2);
    return 0;
}


void fillStartingBoard(Board *board)
{
    int i = 0, j = 0;

    // Filling top -A TO C
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (((i % 2 == 0) && (j % 2 == 1)) || ((i % 2 == 1) && (j % 2 == 0)))
                (*board)[i][j] = 'T'; // Top player
            else
                (*board)[i][j] = ' ';
        }
    }
    // Filling middle- 2 empty rows - D , E
    for (i = 3; i < 5; i++)
        for (j = 0; j < 8; j++)
            (*board)[i][j] = ' ';
    // Filling bottom - F TO H
    for (i = 5; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (((i % 2 == 0) && (j % 2 == 1)) || ((i % 2 == 1) && (j % 2 == 0)))
                (*board)[i][j] = 'B'; // Bottom player
            else
                (*board)[i][j] = ' ';
        }
    }
}
void PrintOpener()
{
    printf(":'$$$$$$::'$$::::'$$:'$$$$$$$$::'$$$$$$::'$$:::'$$:'$$$$$$$$:'$$$$$$$$:::'$$$$$$::\n");
    printf("'$$... $$: $$:::: $$: $$.....::'$$... $$: $$::'$$:: $$.....:: $$.... $$:'$$... $$:\n");
    printf("$$:::..:: $$:::: $$: $$::::::: $$:::..:: $$:'$$::: $$::::::: $$:::: $$: $$:::..::\n");
    printf("$$::::::: $$$$$$$$$: $$$$$$::: $$::::::: $$$$$:::: $$$$$$::: $$$$$$$$::. $$$$$$::\n");
    printf("$$::::::: $$.... $$: $$...:::: $$::::::: $$. $$::: $$...:::: $$.. $$::::..... $$:\n");
    printf("$$::: $$: $$:::: $$: $$::::::: $$::: $$: $$:. $$:: $$::::::: $$::. $$::'$$::: $$:\n");
    printf(". $$$$$$:: $$:::: $$: $$$$$$$$:. $$$$$$:: $$::. $$: $$$$$$$$: $$:::. $$:. $$$$$$::\n");
    printf(":......:::..:::::..::........:::......:::..::::..::........::..:::::..:::......:::\n");
    printf("\n\n\n");
}
