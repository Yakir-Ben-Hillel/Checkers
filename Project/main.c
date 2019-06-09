#include "PrototypesProject.h"
			

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

	// for end cases 1
	/*Board testBoard = {
		{' ', 'B', ' ', 'T', ' ', ' ', ' ', ' '},
		{' ', ' ', 'T', ' ', ' ', ' ', 'T', ' '},
		{' ', 'T', ' ', 'T', ' ', 'T', ' ', ' '},
		{'T', ' ', ' ', ' ', ' ', ' ', 'T', ' '},
		{' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},
		{' ', ' ', 'B', ' ', 'T', ' ', ' ', ' '},
		{' ', 'B', ' ', ' ', ' ', ' ', ' ', 'B'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};*/

	// for end cases 2
	Board testBoard = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'B', ' ', 'T', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ',' ', ' ', 'T', ' ', ' '},
		{'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
		{' ', 'B', ' ', ' ', ' ', 'B', ' ', ' '},
		{' ', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
		{' ', 'B', ' ', ' ', ' ', ' ', ' ', 'B'},
		{' ', ' ', ' ', ' ', ' ', ' ', 'B', ' '},
	};
	printBoard(testBoard);
	printf("\n\n\n");

	checkersPos src1, src2;
	// test1-top-middle board
	src1.row = 'F';
	src1.col = '1';
	// test2- bottom-middleside
		// test2- bottom-middleside
	src2.row = 'H';
	src2.col = '7';


	printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

	SingleSourceMovesTree *movesTree1 = NULL;
	SingleSourceMovesTree *movesTree2 = NULL;
	movesTree1 = FindSingleSourceMoves(startingBoard, &src1);
	movesTree2 = FindSingleSourceMoves(testBoard, &src2);

	printf("src1 coordinate: %c X %c \n , src2 coordinate: %c X %c\n", src1.row, src1.col, src2.row, src2.col);

	printTreeInOrder(movesTree1);
	printTreeInOrder(movesTree2);

	// Function 2 
	SingleSourceMovesList  *lst1, *lst2;
	lst1 = FindSingleSourceOptimalMove(movesTree1);
	lst2 = FindSingleSourceOptimalMove(movesTree2);
	printList(lst1);
	printList(lst2);
	MultipleSingleSourceMovesList *mulLst;
	mulLst = FindAllPossiblePlayerMoves(testBoard, 'B');
	
	
	// Debugging//
	printf("NOW***********************************bufor*******************************************NOW\n");
	printBoard(testBoard);  // Debugging
	StoreBoard(testBoard, "save1.bin");
	LoadBoard("save1.bin", testBoard);
	printBoard(testBoard); // Debugging
	printf("NOW*************************************achor*****************************************NOW\n");
	// Debugging//

	printLoList(mulLst);
	Turn(testBoard, 'B');
	freeTree(movesTree1);
	freeTree(movesTree2);
	freeList(lst1);
	freeList(lst2);
	freeLoList(mulLst);
}
