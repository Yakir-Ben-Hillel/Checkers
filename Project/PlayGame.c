#include "PrototypesProject.h"
// PlayGame function:
// The function is getting a board and a player to play with
// The function will operate both sides of players starting with the given player
// The function prints the given board (in the format that we've been asked to)
// Each turn the function will print the name of the player
// Prints the player who's playing
static player InitializeAndPrintPlayer(player player);
// Locates the player that has been moved and updates the last position and the current position of the player that made the last move
// Indicates whether the game is over - updates the flag notices if the game is over
void findChangeInBoard(Board lastBoard, Board currBoard, BOOL *isDone,
					   checkersPos *lastPos, checkersPos *currPos, player starting_player);
// Compares the index to the last index based on the direction of scanning the board
static BOOL compLastInd(int index, int lastIndex, player player);
// Updates the indexes for scanning the board for changes in the direction of the given player
static void updateIndexes(int *startingInnerInd, int *startingOuterInd, int *LastInd, player player, BOOL *isFirst);

// Promotes the index by initializing the variable that replace the promotion process
//  of the indexes in each iteration - this by the given player (direction of scanning the board)
static void promoteInd(player player, int *promoteInd, int index);

//Prints a given text File.
void PlayGame(Board board, player starting_player)
{
	Board tempBoard;
	int i = 0;
	BOOL isDone = FALSE;
	checkersPos lastPos = {0}, currPos = {0};
	player player = starting_player, nextPlayer; // Initializing the player variable to be the starting player, a variable
	srand(time(NULL));//Seed for rand().
	for (i = 0; i < 8; i++)
		memcpy(&tempBoard[i], &board[i], sizeof(board[i])); // Filling a temp board for comparison
	printf("Let the game begin!\n");

	// Printing the given board
	printf("Starting Board:\n");
	printBoard(board); // for storing temporarily the next player for later on, initializing the player variable

	while (!isDone)
	{
		Turn(board, player);													  // Making a turn of a player
		findChangeInBoard(tempBoard, board, &isDone, &lastPos, &currPos, player); // Updates board, initializing temp board and positions, and initializing flag in case game is over
		if (!isDone)
		{
			nextPlayer = InitializeAndPrintPlayer(player);
			printf("%c%d->%c%d\n", lastPos.row, lastPos.col, currPos.row, currPos.col);
			printBoard(tempBoard);
			player = nextPlayer; // Initializing the player variable to be the next player
		}
		else
		{
			DeclareWinner(player);
		}
	}
}

void findChangeInBoard(Board lastBoard, Board currBoard, BOOL *isDone,
					   checkersPos *lastPos, checkersPos *currPos, player player)
{
	int i, j, startingInnerInd, startingOuterInd, LastInd;
	int promoteInnerInd, promoteOuterInd, countChanges = 0;
	BOOL isFirst = TRUE;	   // Flag notices whether there's a need to set the outer index
	BOOL updateIsDone = FALSE; // Flag notices the update is done (ended after updating the new position of player

	updateIndexes(&startingInnerInd, &startingOuterInd, &LastInd, player, &isFirst); // Updates indexes based on the player's playing direction
	// Scanning board upwards in case of BOTTOM_UP player Or downwards in case of TOP_DOWN player
	for (i = startingOuterInd; compLastInd(i, LastInd, player) && (!updateIsDone); i = promoteOuterInd) // "Generic" for both sides of board scanning
	{
		// in case of bottom to up indexes >=0 && <=7
		for (j = startingInnerInd; compLastInd(j, LastInd, player) && (!updateIsDone); j = promoteInnerInd) // "Generic" for both sides of board scanning
		{
			if (lastBoard[i][j] != currBoard[i][j])
			{
				countChanges++;
				if ((countChanges == 1) && (lastBoard[i][j] == player) && (currBoard[i][j] == ' ')) // For Readiness - last position of the given player
				{
					lastPos->row = (char)(i + 'A'); // Updating the row of the last position
					lastPos->col = j + 1;			// // Updating the column of the last position
				}
				else if ((countChanges > 1) && (currBoard[i][j] == player)) // New position of the player
				{
					currPos->row = (char)(i + 'A'); // Updating the row of the last position
					currPos->col = j + 1;			// // Updating the column of the last position
					updateIsDone = TRUE;
				}
				lastBoard[i][j] = currBoard[i][j]; // Updating the last board
			}
			promoteInd(player, &promoteInnerInd, j); // Promoting the index of the inner loop
		}
		updateIndexes(&startingInnerInd, &startingOuterInd, &LastInd, player, &isFirst);
		promoteInd(player, &promoteOuterInd, i); // Promoting the index of the outer loop
	}
	if (countChanges == 0) // In case no changes in board
	{
		*isDone = TRUE;
	}
}
static BOOL compLastInd(int index, int LastIndex, player player)
{
	if ((player == 'T') && (index <= LastIndex)) // Scanning downwards the board
		return TRUE;
	else if ((player == 'B') && (index >= LastIndex)) // For readiness,  scanning upwards of the board
		return TRUE;
	else // In any other case
		return FALSE;
}
static void promoteInd(player player, int *promoteInd, int index)
{
	if (player == 'T') // TOP_DOWN player, scanning table downwards
	{
		if (index < 8)
			(*promoteInd) = index + 1;
	}
	else // BOTTOM_UP player, scanning table upwards
	{
		if (index >= 0)
			(*promoteInd) = index - 1;
	}
}
static void updateIndexes(int *startingInnerInd, int *startingOuterInd, int *LastInd, player player, BOOL *isFirst)
{
	if (player == 'T') // Top to Bottom indexes
	{
		if (*isFirst)
			*startingOuterInd = 0;
		*startingInnerInd = 0;
		*LastInd = 8 - 1;
	}
	else // Bottom to Top indexes
	{
		if (*isFirst)
			*startingOuterInd = 8 - 1;
		*startingInnerInd = 8 - 1;
		*LastInd = 0;
	}
	*isFirst = FALSE; // Updated after the first time the function is being called
}
static player InitializeAndPrintPlayer(player player)
{
	if (player == 'T') // Top player is the starting player
	{
		printf("player TOP turn\n");
		return ('B'); // Returning the next player
	}
	else // The bottom player is starting
	{
		printf("player BOTTOM turn\n");
		return ('T'); // Returning the next player
	}
	printf("\n");
}
