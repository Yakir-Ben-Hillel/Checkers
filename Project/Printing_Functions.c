#include "PrototypesProject.h"
#define NUM_OF_CHAR_BORDER 9 // Number of couples of '+-' for constructing the border
#define EXIT_BY_WILL 500
static void printBorderRow();				   // Prints the border of a row after each row
static void printLineOfColumns();			   // Prints the row of numbers indicates the number of a column
static void printColumnOfLetters(char Letter); // Sending The letter of the row
static BOOL startGame(Board board);
static void printTreeSourcesInOrderAux(SingleSourceMovesTreeNode *source);
static void Copyrights();

void PrintOpener()
{
	printf("**************************************************************************************\n");
	printf("** $$$$$$   $$     $$  $$$$$$$$   $$$$$$   $$  $$$   $$$$$$$$  $$$$$$$$    $$$$$$$  **\n");
	printf("**$$        $$     $$  $$        $$        $$  $$    $$        $$     $$   $$       **\n");
	printf("**$$        $$$$$$$$$  $$$$$$$$  $$        $$$$$     $$$$$$    $$$$$$$$    $$$$$$$  **\n");
	printf("**$$        $$     $$  $$        $$        $$  $$    $$        $$   $$           $$ **\n");
	printf("**$$        $$     $$  $$        $$        $$   $$   $$        $$    $$          $$ **\n");
	printf("** $$$$$$   $$     $$  $$$$$$$$   $$$$$$   $$    $$  $$$$$$$$  $$     $$   $$$$$$$  **\n");
	printf("************************************************************************************** \n\n\n\n");
}
void printBoard(Board board) // debugging purpose only
{
	printf("\n\n");
	int i = 0, j = 0;

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
				printColumnOfLetters((char)('A' + i)); // Sending The letter of the row
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
		if (i == 0)
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
void Menu(Board board)
{
	PrintOpener();
	PrintFile("MainMenu.txt");
	BOOL isPlaying = FALSE;
	char option = 0;
	while (!isPlaying)
	{
		printf("Please insert the number of your wanted option: ");
		scanf(" %c", &option);
		switch (option)
		{
		case '1':
			isPlaying = startGame(board);
			break;
		case '2':
			PrintFile("help.txt");
			break;
		case '3':
			Copyrights();
			break;
		case '4':
			printBoard(board);
			break;
		case '5':
			RunTests();
			break;
		case '6':
			printf("\n\nHave a great day :)\n");
			exit(EXIT_BY_WILL);
		default:
			printf("This is not a valid option\n");
			printf("choose help for instructions\n");
			break;
		}
	}
}
void PrintFile(char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	checkFileOperation(fp);
	while (!feof(fp))
	{
		char c = fgetc(fp);
		if (c != EOF) //Avoid printing EOF.
			printf("%c", c);
	}
	fclose(fp);
}
void DeclareWinner(player player)
{
	if (player == 'B') //The player who is now his turn, but he just lost.
	{
		printf("The Winner is T!\n");
	}
	else
	{
		printf("The Winner is B!\n");
	}
}
static BOOL startGame(Board board)
{
	player pl;
	printf("Please choose a starting player (insert R for a random pick): ");
	getchar(); //Avoid autofill with '\n'.
	pl = getchar();
	if ((pl != 'T') && (pl != 'B') && (pl != 'R') && (pl != 't') && (pl != 'b') && (pl != 'r'))
	{
		printf("This is not a valid player\n");
		printf("if help is needed please write help\n");
		return FALSE;
	}
	else
	{
		PlayGame(board, pl);
		return TRUE;
	}
}
static void Copyrights()
{
	printf("The Game as been made by: \n");
	printf("Maayan Hadar and David Yakir Ben Hillel.\n");
}

void printTreeInOrder(SingleSourceMovesTree *movesTree)
{
	if (movesTree == NULL)
		return;
	else
	{
		printf("Printing the tree sources in order:\n");
		printTreeSourcesInOrderAux(movesTree->source);
		printf("\n");
	}
}
static void printTreeSourcesInOrderAux(SingleSourceMovesTreeNode *source)
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
void printList(SingleSourceMovesList *lst)
{
	if (lst != NULL)
	{
		SingleSourceMovesListCell *current = lst->head;
		printf("Printing the best Moves List.\n");
		while (current != NULL)
		{
			printf("Amount of Captures in this position is:%hu %c%c\n ", current->captures, current->position->row, current->position->col); // Printing the coordinates of the current position
			current = current->next;																										 // Updating the "pointer" to cell in the list
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