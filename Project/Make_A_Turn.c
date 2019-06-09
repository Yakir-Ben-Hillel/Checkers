#include "PrototypesProject.h"
// Finds the place of the list with best move, returns in the flag whether the move includes a capture or not
static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list, BOOL * hasCaptured);
// Initializing the pointer to the best move list by the place found in the list of moves lists 
static void getBestListByPlace(unsigned short bestPlaceInList, MultipleSingleSourceMovesList* mul_list, SingleSourceMovesList** chosenMoveList);
static void handlePlayersRemoval(Board board, SingleSourceMovesList* chosenMoveList, BOOL hasCaptured, player player); // Handle process of updating the board 
static void movePlayer(Board board, player player, checkersPos* lastPos,checkersPos* currentPos); // Moves the player to the next position
static void removeEnemy(Board board, player player, checkersPos* lastPos, checkersPos* currentPos); // Removes enemy players that has been captured 

void Turn(Board board, player player)
{
	BOOL hasCaptured = FALSE;
	unsigned short bestPlaceInList;
	MultipleSingleSourceMovesList *mul_list = NULL;
	SingleSourceMovesList *chosenMoveList = NULL;
	mul_list = FindAllPossiblePlayerMoves(board, player); // Builds a list of best moves 
	bestPlaceInList = findPlaceofBestTurn(mul_list, &hasCaptured); // Finds the place in list of lists where the best move is found 
	getBestListByPlace(bestPlaceInList, mul_list, &chosenMoveList); // Intializing the pointer to the chosen list move
	// Handle players removal of the board
	handlePlayersRemoval(board, chosenMoveList, hasCaptured, player); // Updates the board
}
static void handlePlayersRemoval(Board board, SingleSourceMovesList* chosenMoveList, BOOL hasCaptured, player player)
{
	SingleSourceMovesListCell * current = chosenMoveList->head;
	checkersPos* startPos = current->position; // Pointer to the starting position
	checkersPos* lastPos = current->position; // Set up as the current for a start
	int diffCol = 0, diffRow=0; // The difference between positions- their distance is bigger than 1 - meaning a capture has been done
	
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

		if ( (hasCaptured) && (current!= NULL)) // Removal process
		{	// Difference between columns and rows - one position compared to other
			diffCol = abs((int)lastPos->col - (int)current->position->col);
			diffRow = abs((int)lastPos->row - (int)current->position->row);
			if (diffCol > 1 && diffRow > 1)
				removeEnemy(board, player, lastPos, current->position);
		}
	}
}
static void movePlayer(Board board, player player, checkersPos* lastPos, checkersPos* currentPos)
{
	int row = lastPos->row - 'A';
	int col = lastPos->col - '0' - 1;
	board[row][col] = ' '; // Removing the player from the last Position
	// Updating the indexes to the current position in the board
	row = currentPos->row - 'A';
	col = currentPos->col - '0' - 1;
	board[row][col] = player; // Moving the player to the current position
}
static void removeEnemy(Board board, player player, checkersPos* lastPos, checkersPos* currentPos)
{
	checkersPos capture; 
	capture.row = ((lastPos->row) + (currentPos->row)) / 2;//Captured row position.
	capture.col = ((lastPos->col) + (currentPos->col)) / 2;//captured col position.
	int capturetRow =(int)capture.row - 'A', lastCol = lastPos->col - '0' - 1;
	int captureCol= (int)capture.col - '0' - 1;
	// Removing the captured enemy from board
	board[capturetRow][captureCol] = ' ';
}
static void getBestListByPlace(unsigned short bestPlaceInList, MultipleSingleSourceMovesList* mul_list, SingleSourceMovesList** chosenMoveList)
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
	unsigned short max = 0;
	unsigned short place = 1, counter=1;
	ptr = mul_list->head; // Pointer to first inner list of the list of best Moves lists
	while (ptr != NULL)
	{
		if (ptr->Single_Source_moves_list->tail->captures > max)
		{
			max = ptr->Single_Source_moves_list->tail->captures; // Updating the max value of captures
			place = counter;
		}
		ptr = ptr->next;
		counter++;
	}
	if (max != 0) // Captures has been done by the chosen move
		*hasCaptured = TRUE;
	return place;
}

static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list);
void Turn(Board board, player player)
{
    unsigned short bestPlaceInList;
    MultipleSingleSourceMovesList *mul_list;
    mul_list = FindAllPossiblePlayerMoves(board, player);
    bestPlaceInList=findPlaceofBestTurn(mul_list);
}


static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list)
{
    MultipleSourceMovesListCell *ptr;
    unsigned short max = 0;
    unsigned short counter = 0;
    ptr = mul_list->head;
    while (ptr != NULL)
    {
        if (ptr->Single_Source_moves_list->tail->captures > max)
        {
            max = ptr->Single_Source_moves_list->tail->captures;
        }
        ptr=ptr->next;
        counter++;
    }
    return counter;
}
//Just Started to write it down.
