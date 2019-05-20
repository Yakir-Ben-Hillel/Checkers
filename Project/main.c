#include "PrototypesProject.h"

void PrintOpener();
void fillStartingBoard(Board *board);
static void printBoard(Board board);
void printTreeInOrder  (SingleSourceMovesTree* movesTree);
static void printTreeInOrderAux(SingleSourceMovesTreeNode* source );
 
int main()
{
    // Opener- Checkers game
    PrintOpener();
    // Fill board
    Board startingBoard1={
    {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
    {'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
    {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
    {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
    {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
};
    Board startingBoard2={
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
    printBoard(startingBoard1);
    printf("\n\n\n");

    // for end cases
    Board testBoard={
                    {' ',' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ','T',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' ',' '},
                    {'B',' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                                    };
    printBoard(testBoard);
    printf("\n\n\n");

checkersPos src1={0}, src2={0}; 
// test1-top-middle board
src1.row = 'F'; src1.col = '1';
// test2- bottom-middleside
src2.row = 'B'; src2.col = '3';

printf ("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

SingleSourceMovesTree *movesTree1;
SingleSourceMovesTree *movesTree2;
movesTree1= FindSingleSourceMoves(startingBoard1, &src1);
movesTree2= FindSingleSourceMoves(startingBoard2, &src2);

    printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

printTreeInOrder (movesTree1);
printTreeInOrder (movesTree2);

    printTreeInOrder(movesTree1);
    printTreeInOrder(movesTree2);
    return 0;
}

void printBoard(Board board) // debugging purpose only
{
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
        printTreeInOrderAux(movesTree->source);
}
void printTreeInOrderAux(SingleSourceMovesTreeNode *source)
{
    if (source == NULL)
        return;
    else
    {
        printTreeInOrderAux(source->next_move[0]);
        printBoard(source->board);
        printTreeInOrderAux(source->next_move[1]);
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
            if( ((i % 2 == 0) && (j % 2 == 1)) || ((i % 2 == 1) && (j % 2 == 0)) )
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
            if( ((i % 2 == 0) && (j % 2 == 1)) || ((i % 2 == 1) && (j % 2 == 0)) )
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
    printf(" $$::::::: $$.... $$: $$...:::: $$::::::: $$. $$::: $$...:::: $$.. $$::::..... $$:\n");
    printf("$$::: $$: $$:::: $$: $$::::::: $$::: $$: $$:. $$:: $$::::::: $$::. $$::'$$::: $$:\n");
    printf(". $$$$$$:: $$:::: $$: $$$$$$$$:. $$$$$$:: $$::. $$: $$$$$$$$: $$:::. $$:. $$$$$$::\n");
    printf(":......:::..:::::..::........:::......:::..::::..::........::..:::::..:::......:::\n");
    printf("\n\n\n");
}
