#include "PrototypesProject.h"

void PrintOpener();
void fillStartingBoard(Board *board);
void printBoard(Board board);
void printTreeInOrder(SingleSourceMovesTree *movesTree1);
void printTreeInOrderAux(SingleSourceMovesTreeNode *source);

int main()
{
    // Opener- Checkers game
    //PrintOpener();

    // Fill board
    Board startingBoard={
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

    // for end cases
    printf("\n\n\n\n\n");
    printf("Test Board\n");
    Board testBoard = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', 'T', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'B', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    printBoard(testBoard);

    checkersPos src1, src2;
    // test1-top-middle board
    src1.row = 'B';
    src1.col = '3';
    // test2- bottom-middleside
    src2.row = '1';
    src2.col = '2';

    printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

    SingleSourceMovesTree *movesTree1 = FindSingleSourceMoves(startingBoard, &src1);
    SingleSourceMovesTree *movesTree2 = FindSingleSourceMoves(testBoard, &src1);

    void printTreeInOrder(SingleSourceMovesTree * movesTree);
    void printTreeInOrderAux(SingleSourceMovesTreeNode * source);

    printTreeInOrder(movesTree1);
    printTreeInOrder(movesTree2);
    return 0;
}

void printBoard(Board board) // debugging purpose only
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        printf("---------------------------------\n");
        for (j = 0; j < 8; j++)
        {
            if(j==0)
            printf("| %c |",board[i][j]);
            else
            printf(" %c |", board[i][j]);
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

void PrintOpener()
{
    printf(":'######::'##::::'##:'########::'######::'##:::'##:'########:'########:::'######::\n");
    printf("'##... ##: ##:::: ##: ##.....::'##... ##: ##::'##:: ##.....:: ##.... ##:'##... ##:\n");
    printf("##:::..:: ##:::: ##: ##::::::: ##:::..:: ##:'##::: ##::::::: ##:::: ##: ##:::..::\n");
    printf("##::::::: #########: ######::: ##::::::: #####:::: ######::: ########::. ######::\n");
    printf(" ##::::::: ##.... ##: ##...:::: ##::::::: ##. ##::: ##...:::: ##.. ##::::..... ##:\n");
    printf("##::: ##: ##:::: ##: ##::::::: ##::: ##: ##:. ##:: ##::::::: ##::. ##::'##::: ##:\n");
    printf(". ######:: ##:::: ##: ########:. ######:: ##::. ##: ########: ##:::. ##:. ######::\n");
    printf(":......:::..:::::..::........:::......:::..::::..::........::..:::::..:::......:::\n");
}
