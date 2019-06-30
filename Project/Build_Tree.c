#include "PrototypesProject.h"
// function1 Prototypes
// return in the options array the nearest possible coordinates for moving and in accordance the place of an eaten soldier if exists
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, unsigned short captureAmount, BOOL has_moved,BOOL has_eaten); // Auxiliary function for building the tree moves
static void handleTreeOne(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeOne, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures, BOOL has_moved, BOOL has_eaten); //Makes tree one.
static void handleTreeTwo(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeTwo, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures, BOOL has_moved, BOOL has_eaten); //Makes tree two.

//Make a leaf in the tree.

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
	SingleSourceMovesTree *movesTree = NULL;
	player currentPlayer;
	if (!isCellFree(board, src)) // In case the cell is taken
	{
		initializePlayer(board, src, &currentPlayer);
		movesTree = (SingleSourceMovesTree *)malloc(sizeof(SingleSourceMovesTree));
		checkAllocation(movesTree);
		*movesTree = FindSingleSourceMovesAux(board, src, currentPlayer, 0, FALSE,FALSE);
	}
	return (movesTree); // Returns the tree moves or a NULL in case the cell is free
}
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, unsigned short captureAmount, BOOL has_moved, BOOL has_eaten)
{
	// Initialized due to security reasons
	SingleSourceMovesTree treeOne = {NULL}, treeTwo = {NULL}, baseTree = {NULL};
	checkersPos *options = NULL, *captures = NULL;
	// Allocating a tree node
	allocateTreeNode(&baseTree, src); // Updates position
	allocateOptionsAndCaptures(&options, &captures);
	//	if (countLevel == 1)
	baseTree.source->total_captures_so_far = captureAmount;

	// Compliment case - Connecting sub - Trees to the base Tree + recursive calls
	if (((src->row == 'H') && (pl == 'T')) || ((src->row == 'A') && (pl == 'B'))) //If reached the end of the board.
	{
		handleLeaf(&baseTree, board, pl, src, options, captures); //Makes and returns the a leaf.
		return baseTree;
	}
	soldierStatus(board, src, pl, options, captures);
	// Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
	handleTreeOne(&baseTree, &treeOne, board, pl, src, options, captures, baseTree.source->total_captures_so_far, has_moved, has_eaten); //Makes treeOne.
	handleTreeTwo(&baseTree, &treeTwo, board, pl, src, options, captures, baseTree.source->total_captures_so_far, has_moved, has_eaten); //Makes treeTwo.

	// Free the arrays allocated at start
	free(options);
	free(captures);
	return (baseTree);
}

static void handleTreeOne(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeOne, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures, BOOL has_moved, BOOL has_eaten)
{
	// handle sub tree one
	if (has_moved) //The player has moved in the previos step.
	{
		if (has_eaten == FALSE) //He moved in the previos step,but did not capture.
		{
			treeOne->source = NULL;
			initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
		}
		else //He did moved before, and he captured before.
		{
			if ((captures[0].col != 0) && (captures[0].row != 0)) //He did capture before,and there is capture now.
			{
				// Initializing board the current root
				initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
				handleBoardChange(board, src, pl, 0, options, captures, &countCaptures);			   // Handles change due to next move update in the tree + update captures counter.
				*treeOne = FindSingleSourceMovesAux(board, options, pl, countCaptures, TRUE, TRUE);
			}
			else //He did capture before,but not now.
			{
				treeOne->source = NULL;
			}
		}
	}
	else // It's the player first ever step.
	{
		if (((options[0].col == 0) && (options[0].row == 0)) && ((captures[0].col == 0) && (captures[0].row == 0)))
		{ //The player is blocked, he can move anywhere.
			treeOne->source = NULL;
			initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
		}
		else
		{																						   //He can move.
			initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root.
			handleBoardChange(board, src, pl, 0, options, captures, &countCaptures);			   // Handles change due to next move update in the tree + update captures counter.
			if ((captures[0].col != 0) && (captures[0].row != 0))								   //There is a capture.
				*treeOne = FindSingleSourceMovesAux(board, options, pl, countCaptures, TRUE, TRUE);
			else //There is no capture.
				*treeOne = FindSingleSourceMovesAux(board, options, pl, countCaptures, TRUE, FALSE);
		}
	}
	baseTree->source->next_move[0] = treeOne->source;
}

static void handleTreeTwo(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeTwo, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures, BOOL has_moved, BOOL has_eaten)
{
	// handle sub tree two
	if (has_moved) //Moved before.
	{
		if (has_eaten == FALSE) //There was no capture before.
		{
			treeTwo->source = NULL;
			if ((options[0].col != 0) && (options[0].row != 0))
			{
				board[options[0].row - 'A'][options[0].col - '0' - 1] = ' ';
				initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
			}
		}
		else //He did capture before.
		{
			if ((captures[1].col != 0) && (captures[1].row != 0)) //He did capture before,and there is capture now.
			{
				// Initializing board the current root
				initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
				handleBoardChange(board, src, pl, 1, options, captures, &countCaptures);			   // Handles change due to next move update in the tree + update captures counter.
				*treeTwo = FindSingleSourceMovesAux(board, options + 1, pl, countCaptures, TRUE, TRUE);
			}
			else //He did capture before,but not now.
			{
				treeTwo->source = NULL;
				if ((options[0].col != 0) && (options[0].row != 0))
				{
					board[options[0].row - 'A'][options[0].col - '0' - 1] = ' ';
					initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
				}
			}
		}
	}
	else //It's the player first step.
	{
		if (((options[1].col == 0) && (options[1].row == 0)) && ((captures[1].col == 0) && (captures[1].row == 0)))
		{ //He is blocked.
			treeTwo->source = NULL;
			if ((options[0].col != 0) && (options[0].row != 0))
			{
				board[options[0].row - 'A'][options[0].col - '0' - 1] = ' ';
				initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
			}
		}
		else
		{
			// Initializing board the current root
			initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
			handleBoardChange(board, src, pl, 1, options, captures, &countCaptures);			   // Handles change due to next move update in the tree + update captures counter.
			if ((captures[1].col != 0) && (captures[1].row != 0))								   //There is a capture in this step.
				*treeTwo = FindSingleSourceMovesAux(board, options + 1, pl, countCaptures, TRUE, TRUE);
			else //There is no capture in this step.
				*treeTwo = FindSingleSourceMovesAux(board, options + 1, pl, countCaptures, TRUE, FALSE);
		}
	}
	baseTree->source->next_move[1] = treeTwo->source;
	initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); //Getting back to the initial board.
}
