#include "PrototypesProject.h"
static void updateTableNoCapture(Board board, checkersPos *src, checkersPos *options, player pl, int direction);
static void captureFromoptionZero(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures, unsigned short *countCaptures);
static void captureFromoptionOne(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures, unsigned short *countCaptures);
// Update the board based on possible near moves and captions
// capture between the given captures, if exist
// Return true in case there's a match between a capture and a move

void handleBoardChange(Board board, checkersPos *src, player pl, int direction, checkersPos *options, checkersPos *captures, unsigned short *countCaptures)
{
	int Ind = direction; // Index for the array of captures, Initialized in case there's a matched capture

	if ((isThereACapture(captures, &Ind)))
	{
		if ((direction == 0) && (Ind == 0))
		{
			captureFromoptionZero(board, src, pl, options, captures, countCaptures);
		}
		else if ((direction == 1) && (Ind == 1))
		{
			captureFromoptionOne(board, src, pl, options, captures, countCaptures);
		}
		else
		{
			updateTableNoCapture(board, src, options, pl, direction);
		}
	}
	else // No capture - updating the table by moving the player and deleting its last location
	{
		updateTableNoCapture(board, src, options, pl, direction);
	}
}

BOOL isThereACapture(checkersPos *captures, int *ind)
{
	// Check for the first potential capture
	// Checks wether one of the captions matches the move option
	if ((captures[0].col != 0) && (captures[0].row != 0) && *ind == 0)
	{			  // In case its a valid coordinate
		*ind = 0; // Updating the index of the capture
		return TRUE;
	}
	// Check for the second potential capture
	if ((captures[1].col != 0) && (captures[1].row != 0) && *ind == 1)
	{
		*ind = 1; // Updating the index of the capture
		return TRUE;
	}
	// In any other case
	return FALSE;
}

static void captureFromoptionZero(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures, unsigned short *countCaptures)
{ //Checks  if there is a capture in option[0].
	if (((abs((options[0].row) - (captures[0].row))) == 1) && ((abs((options[0].col) - (captures[0].col))) == 1))
	{
		board[src->row - 'A'][src->col - '0' - 1] = ' ';			   // Removing the player from its last position
		board[options[0].row - 'A'][options[0].col - '0' - 1] = pl;	// Moving the player to the place given in options array
		board[captures[0].row - 'A'][captures[0].col - '0' - 1] = ' '; // Removing the captured player from board
		(*countCaptures)++;
	}
	else if (((abs((options[0].row) - (captures[1].row))) == 1) && ((abs((options[0].col) - (captures[1].col))) == 1))

	{
		board[src->row - 'A'][src->col - '0' - 1] = ' ';			   // Removing the player from its last position
		board[options[0].row - 'A'][options[0].col - '0' - 1] = pl;	// Moving the player to the place given in options array
		board[captures[1].row - 'A'][captures[1].col - '0' - 1] = ' '; // Removing the captured player from board
		(*countCaptures)++;
	}
}
static void captureFromoptionOne(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures, unsigned short *countCaptures)
{ //Checks if there is a capture in option[1].
	if (((abs((options[1].row) - (captures[0].row))) == 1) && ((abs((options[1].col) - (captures[0].col))) == 1))
	{
		board[src->row - 'A'][src->col - '0' - 1] = ' ';			   // Removing the player from its last position
		board[options[1].row - 'A'][options[1].col - '0' - 1] = pl;	// Moving the player to the place given in options array
		board[captures[0].row - 'A'][captures[0].col - '0' - 1] = ' '; // Removing the captured player from board
		(*countCaptures)++;
	}
	else if (((abs((options[1].row) - (captures[1].row))) == 1) && ((abs((options[1].col) - (captures[1].col))) == 1))
	{
		board[src->row - 'A'][src->col - '0' - 1] = ' ';			   // Removing the player from its last position
		board[options[1].row - 'A'][options[1].col - '0' - 1] = pl;	// Moving the player to the place given in options array
		board[captures[1].row - 'A'][captures[1].col - '0' - 1] = ' '; // Removing the captured player from board
		(*countCaptures)++;
	}
}
static void updateTableNoCapture(Board board, checkersPos *src, checkersPos *options, player pl, int direction)
{ //Update the table when there is no capture.
	if (direction == 0)
	{ //if the step is in option[0].
		if ((options[0].col != 0) && (options[0].row != 0))
		{
			board[src->row - 'A'][src->col - '0' - 1] = ' '; // Removing the player from its last position
			board[options[0].row - 'A'][options[0].col - '0' - 1] = pl;
		}
	}
	else
	{ //if the step is in option[1].
		if ((options[1].col != 0) && (options[1].row != 0))
		{
			if (board[options[0].row - 'A'][options[0].col - '0' - 1] == pl)
			{ //This option becomes available only after the recursion
				// as already entered and returned from option zero.
				// a player as been added to the place in option zero,
				// and in order to go into the option one without the player who as been added
				// in option zero, there is a need to remove it before continueing
				//this proccess does not affect the option tree at all.
				board[options[0].row - 'A'][options[0].col - '0' - 1] = ' ';
			}
			board[src->row - 'A'][src->col - '0' - 1] = ' '; // Removing the player from its last position
			board[options[1].row - 'A'][options[1].col - '0' - 1] = pl;
		}
	}
}
