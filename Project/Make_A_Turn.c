#include "PrototypesProject.h"

#define BOTTOM_UP 'B'
#define TOP_DOWN 'T'
// Finds the place of the list with best move, returns in the flag whether the move includes a capture or not
static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list, BOOL *hasCaptured);
// Initializing the pointer to the best move list by the place found in the list of moves lists
static unsigned short FindMaxCaptures(MultipleSingleSourceMovesList *mul_list);
static void ManagePlaceArr(int **Place_Arr, int *physical_size, int *logical_size);
static void getBestListByPlace(unsigned short bestPlaceInList, MultipleSingleSourceMovesList *mul_list, SingleSourceMovesList **chosenMoveList);
static void handlePlayersRemoval(Board board, SingleSourceMovesList *chosenMoveList, BOOL hasCaptured, player player); // Handle process of updating the board
static void movePlayer(Board board, player player, checkersPos *lastPos, checkersPos *currentPos);					   // Moves the player to the next position
static void removeEnemy(Board board, checkersPos *lastPos, checkersPos *currentPos);								   // Removes enemy players that has been captured
static BOOL checkEdges(Board board);																				   // Checks whether one of the players has reached the other side of the board (the last row / first row of the enemy)
static BOOL NoPlayers(Board board);																					   // Checks whether one of the players has no more players on board

void Turn(Board board, player player)
{
	BOOL hasCaptured = FALSE;
	unsigned short bestPlaceInList;
	MultipleSingleSourceMovesList *mul_list = NULL;
	SingleSourceMovesList *chosenMoveList = NULL;
	// Checks a case one of the players has already reached the his last row (first row of the enemy)
	// or one of players ran out of players on board
	if (checkEdges(board) || NoPlayers(board))
		return;

	mul_list = FindAllPossiblePlayerMoves(board, player);			// Builds a list of best moves
	bestPlaceInList = findPlaceofBestTurn(mul_list, &hasCaptured);  // Finds the place in list of lists where the best move is found
	getBestListByPlace(bestPlaceInList, mul_list, &chosenMoveList); // Intializing the pointer to the chosen list move
	// Handle players removal of the board
	handlePlayersRemoval(board, chosenMoveList, hasCaptured, player); // Updates the board
	freeLoList(mul_list);
}

static BOOL checkEdges(Board board)
{
	int top = 0, bottom = 8 - 1, col = 0;
	BOOL isGameOver = FALSE; // Assumes the game is not over unless finding an enemy player in one of the edges

	for (col = 0; (col < 8) && (!isGameOver); col++) // Scanning the last row and first row to locate case of enemy's player in each
	{												 //*************** 2 Cases ****************//
		// A BOTTOM_UP player in the first row case
		// A TOP_DOWN player in the last row case
		if ((board[top][col] == BOTTOM_UP) || (board[bottom][col] == TOP_DOWN))
			isGameOver = TRUE;
	}
	return (isGameOver);
}
static BOOL NoPlayers(Board board)
{
	int top = 0, Col = 0;
	int bottom = 8 - 1;
	BOOL TopFound = FALSE, BottomFound = FALSE;
	for (top = 0, bottom = 8 - 1; (top <= bottom) && (!TopFound) && (!BottomFound); top++, bottom--)
	{
		for (Col = 0; (Col < 8) && (!TopFound) && (!BottomFound); Col++)
		{
			if (board[top][Col] == 'T')
				TopFound = TRUE;
			if (board[bottom][Col] == 'B')
				BottomFound = TRUE;
		}
	}
	return (TopFound && BottomFound); // Return False in case one of the players has no players on the board
}
static void handlePlayersRemoval(Board board, SingleSourceMovesList *chosenMoveList, BOOL hasCaptured, player player)
{
	SingleSourceMovesListCell *current = chosenMoveList->head;
	checkersPos *lastPos = current->position; // Set up as the current for a start
	int diffCol = 0, diffRow = 0;			  // The difference between positions- their distance is bigger than 1 - meaning a capture has been done

	while (current != NULL)
	{
		lastPos = current->position;
		if (current->next != NULL) // Excluding the initializing process of the current in case its the last move
		{
			current = current->next; // Promoting the pointer to next node- next position
			movePlayer(board, player, lastPos, current->position);
		}
		else
			current = current->next; // Promoting the pointer to end the loop

		if ((hasCaptured) && (current != NULL)) // Removal process
		{										// Difference between columns and rows - one position compared to other
			diffCol = abs((int)lastPos->col - (int)current->position->col);
			diffRow = abs((int)lastPos->row - (int)current->position->row);
			if (diffCol > 1 && diffRow > 1)
				removeEnemy(board, lastPos, current->position);
		}
	}
}
static void movePlayer(Board board, player player, checkersPos *lastPos, checkersPos *currentPos)
{
	int row = lastPos->row - 'A';
	int col = lastPos->col - '0' - 1;
	board[row][col] = ' '; // Removing the player from the last Position
	// Updating the indexes to the current position in the board
	row = currentPos->row - 'A';
	col = currentPos->col - '0' - 1;
	board[row][col] = player; // Moving the player to the current position
}
static void removeEnemy(Board board, checkersPos *lastPos, checkersPos *currentPos)
{
	checkersPos capture;
	capture.row = ((lastPos->row) + (currentPos->row)) / 2; //Captured row position.
	capture.col = ((lastPos->col) + (currentPos->col)) / 2; //captured col position.
	int capturetRow = (int)capture.row - 'A';
	int captureCol = (int)capture.col - '0' - 1;
	// Removing the captured enemy from board
	board[capturetRow][captureCol] = ' ';
}
static void getBestListByPlace(unsigned short bestPlaceInList, MultipleSingleSourceMovesList *mul_list, SingleSourceMovesList **chosenMoveList)
{
	MultipleSourceMovesListCell *currentLol = mul_list->head; // Updating the pointer to the head if the list of lists
	unsigned short indPlace = 1;

	while (indPlace < bestPlaceInList)
	{
		currentLol = currentLol->next; // Promoting the pointer to the next node (next list in the list of moves lists)
		indPlace++;
	}
	*chosenMoveList = currentLol->Single_Source_moves_list; // Updating the pointer to the chosen moves list
}
static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list, BOOL *hasCaptured)
{
	MultipleSourceMovesListCell *ptr;
	ptr = mul_list->head; // Pointer to first inner list of the list of best Moves lists
	unsigned short max = FindMaxCaptures(mul_list);
	unsigned short place = 1, counter = 1;
	unsigned short currect_captures;
	SingleSourceMovesListCell *nextPosition;
	int *placeArrMax;
	int place_Arr_Logical_Size = 0, place_Arr_Physical_Size = 1;

	placeArrMax = (int *)malloc(1 * sizeof(int));
	checkAllocation(placeArrMax);

	// keeps the next position in case
	while (ptr != NULL)
	{
		currect_captures = ptr->Single_Source_moves_list->tail->captures;
		nextPosition = ptr->Single_Source_moves_list->head->next; // Updating the pointer to the next position cell
		if (currect_captures == max && nextPosition)
		{
			ManagePlaceArr(&placeArrMax, &place_Arr_Physical_Size, &place_Arr_Logical_Size);
			placeArrMax[place_Arr_Logical_Size] = counter;
			place_Arr_Logical_Size++;
		}
		ptr = ptr->next;
		counter++;
	}
	if (max != 0) // Captures has been done by the chosen move
		*hasCaptured = TRUE;
	int index = rand() % place_Arr_Logical_Size;
	place = placeArrMax[index];
	free(placeArrMax);
	return place;
}

static void ManagePlaceArr(int **Place_Arr, int *physical_size, int *logical_size)
{
	if (*physical_size == *logical_size)
	{
		*physical_size = *(physical_size)*2 + 1;
		*Place_Arr = (int *)realloc(*Place_Arr, (*physical_size) * sizeof(int));
		checkAllocation(*Place_Arr);
	}
}
static unsigned short FindMaxCaptures(MultipleSingleSourceMovesList *mul_list)
{
	MultipleSourceMovesListCell *ptr = mul_list->head;
	unsigned short max = 0;
	unsigned short current_captures;
	while (ptr)
	{
		current_captures = ptr->Single_Source_moves_list->tail->captures;
		if (current_captures > max)
			max = current_captures;
		ptr = ptr->next;
	}
	return max;
}