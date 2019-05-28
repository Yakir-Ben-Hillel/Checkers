#include "PrototypesProject.h"
void PrintOpener()
{
    printf("\n\n:'$$$$$$::'$$::::'$$:'$$$$$$$$::'$$$$$$::'$$:::'$$:'$$$$$$$$:'$$$$$$$$:::'$$$$$$::\n");
    printf("'$$... $$: $$:::: $$: $$.....::'$$... $$: $$::'$$:: $$.....:: $$.... $$:'$$... $$:\n");
    printf("$$:::..:: $$:::: $$: $$::::::: $$:::..:: $$:'$$::: $$::::::: $$:::: $$: $$:::..::\n");
    printf("$$::::::: $$$$$$$$$: $$$$$$::: $$::::::: $$$$$:::: $$$$$$::: $$$$$$$$::. $$$$$$::\n");
    printf("$$::::::: $$.... $$: $$...:::: $$::::::: $$. $$::: $$...:::: $$.. $$::::..... $$:\n");
    printf("$$::: $$: $$:::: $$: $$::::::: $$::: $$: $$:. $$:: $$::::::: $$::. $$::'$$::: $$:\n");
    printf(".$$$$$$:: $$:::: $$: $$$$$$$$:. $$$$$$:: $$::. $$: $$$$$$$$: $$:::. $$:. $$$$$$::\n");
    printf(":......:::..:::::..::........:::......:::..::::..::........::..:::::..:::......:::\n\n\n\n");
}
void printBoard(Board board) // debugging purpose only
{
    printf("\n\n");
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            printf("%c||", board[i][j]);
        }
        printf("\n");
    }
}
void printTreeInOrder(SingleSourceMovesTree *movesTree)
{
    if (movesTree == NULL)
        return;
    else
    {
        printTreeBoardInOrderAux(movesTree->source);
        printf("\nThe original Board:");
        printBoard(movesTree->source->board);
        printf("The tree Sources are:\n");
        printTreeSourcesInOrderAux(movesTree->source);
        printf("\nThe amount of Captures in the tree is: %hu\n", movesTree->source->total_captures_so_far);
        printf("\n");
    }
}
void printTreeBoardInOrderAux(SingleSourceMovesTreeNode *source)
{
    if (source == NULL)
        return;
    else
    {
        printTreeBoardInOrderAux(source->next_move[0]);
        printBoard(source->board);
        printTreeBoardInOrderAux(source->next_move[1]);
    }
}
void printTreeSourcesInOrderAux(SingleSourceMovesTreeNode *source)
{
    if (source == NULL)
        return;
    else
    {
        printTreeSourcesInOrderAux(source->next_move[0]);
        printf("%c%c ", source->pos->row, source->pos->col);
        printTreeSourcesInOrderAux(source->next_move[1]);
    }
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