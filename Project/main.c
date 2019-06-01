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
        {' ', 'B', ' ', 'T', ' ', ' ', ' ', ' '},
        {' ', ' ', 'T', ' ', ' ', ' ', 'T', ' '},
        {' ', 'T', ' ', 'T', ' ', 'T', ' ', ' '},
        {'T', ' ', ' ', ' ', ' ', ' ', 'T', ' '},
        {' ', 'T', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', 'T', ' ', 'T', ' ', ' ', ' '},
        {' ', 'B', ' ', ' ', ' ', ' ', ' ', 'B'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    printBoard(testBoard);
    printf("\n\n\n");

    checkersPos src1, src2;
    // test1-top-middle board
    src1.row = 'F';
    src1.col = '1';
    // test2- bottom-middleside
    src2.row = 'G';
    src2.col = '2';

    printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

    SingleSourceMovesTree *movesTree1 = NULL;
    SingleSourceMovesTree *movesTree2 = NULL;
    SingleSourceMovesList *bestmoves2 = NULL;
    movesTree1 = FindSingleSourceMoves(startingBoard, &src1);
    movesTree2 = FindSingleSourceMoves(testBoard, &src2);
    bestmoves2=FindSingleSourceOptimalMove(movesTree2);

    printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

    printTreeInOrder(movesTree1);
    printTreeInOrder(movesTree2);
    system("pause"); // Need to be deleted
    return 0;
}
