#include "PrototypesProject.h"
#define NUM_OF_CHAR_BORDER 9 // Number of couples of '+-' for constructing the border

static void printBorderRow(); // Prints the border of a row after each row 
static void printLineOfColumns(); // Prints the row of numbers indicates the number of a column
static void printColumnOfLetters(char Letter); // Sending The letter of the row


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
	int i=0, j=0;
	
	for (i = 0; i < 8; i++)
	{
		printBorderRow(); // Prints the border between the rows of the table
		if (i == 0 && j == 0)
		{
			printLineOfColumns();
			printBorderRow();
		}
		for (j = 0; j < 8; j++)
		{
			if (j == 0)
				printColumnOfLetters( (char) ('A' + i) ); // Sending The letter of the row
			printf("|%c", board[i][j]);
		}
		printf("|\n");
	}
	printBorderRow(); // Prints the corder of the bottom of the table
	printf("\n\n");
}
static void printColumnOfLetters(char Letter)
{
	printf("|%c", Letter);
}
static void printLineOfColumns()
{
	int i = 0; 
	
	for (i = 0; i < NUM_OF_CHAR_BORDER; i++)
	{
		if (i == 0 )
			printf("+ ");
		else
			printf("|%d", i); // Printing the number of column
	}
	printf("|\n");
}
static void printBorderRow() // Prints the border of a row after each row 
{
	int i = 0;

	for (i = 0; i < NUM_OF_CHAR_BORDER; i++)
		printf("+-");
	printf("+\n"); // Printing the end of the border and its last character
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
		printf("Amount of Captures in this position is:%hu %c%c\n ", source->total_captures_so_far, source->pos->row, source->pos->col);
		printTreeSourcesInOrderAux(source->next_move[1]);
	}
}
void printList(SingleSourceMovesList *lst)
{
	if (lst != NULL)
	{
		SingleSourceMovesListCell *current = lst->head;
		printf("Printing the best Moves List.\n");
		while (current != NULL)
		{
			printf("Amount of Captures in this position is:%hu %c%c\n ", current->captures, current->position->row, current->position->col); // Printing the coordinates of the current position
			current = current->next;                                                                                                         // Updating the "pointer" to cell in the list
		}
		printf("\n\n");
	}
}

void printLoList(MultipleSingleSourceMovesList *Lol) // Prints the list of single source move
{
	MultipleSourceMovesListCell *currentListP = Lol->head;

	while (currentListP != NULL)
	{
		printList(currentListP->Single_Source_moves_list);
		printf("\n");
		currentListP = currentListP->next;
	}
}

void fillStartingBoard(Board *board)
{ //Prints the starting Board.
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
