#include "PrototypesProject.h"
void RunTests()
{
	Board testBoard = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'B', ' ', 'T', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', 'T', ' ', ' '},
		{'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
		{' ', 'B', ' ', ' ', ' ', 'B', ' ', ' '},
		{' ', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
		{' ', 'B', ' ', ' ', ' ', ' ', ' ', 'B'},
		{' ', ' ', ' ', ' ', ' ', ' ', 'B', ' '},
	};
	printf("\nThe tests are running on a test board\n");
	printf("In order to view other senerios please feel free to edit the test board\n\n");
	printf("All checks are in Databases_checker.c file\n");
	printf("The test board is:\n");
	printBoard(testBoard);
	printf("\n");
	checkersPos src;
	// test1-top-middle board
	// test2- bottom-middleside
	// test2- bottom-middleside
	src.row = 'H';
	src.col = '7';
	printf("Build a source Tree and List on a specific coordinate\n");
	printf("in order to change the source please feel free to edit the source.\n");
	printf("src coordinate: %c X %c\n", src.row, src.col);
	SingleSourceMovesTree *movesTree = NULL;
	movesTree = FindSingleSourceMoves(testBoard, &src);
	printTreeInOrder(movesTree);
	// Function 2
	SingleSourceMovesList *lst;
	lst = FindSingleSourceOptimalMove(movesTree);
	printList(lst);
	MultipleSingleSourceMovesList *mulLst;
	player type = 'B';
	printf("Printing List of lists for player %c:\n\n", type);
	mulLst = FindAllPossiblePlayerMoves(testBoard, type);
	printLoList(mulLst);

	StoreBoard(testBoard, "save1.bin");
	printf("Loading the board from a binary file.");
	LoadBoard("save1.bin", testBoard);

	freeTree(movesTree);
	freeList(lst);
	freeLoList(mulLst);
}