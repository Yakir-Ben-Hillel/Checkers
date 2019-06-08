#include "PrototypesProject.h"
// function1 Prototypes
// return in the options array the nearest possible coordinates for moving and in accordance the place of an eaten soldier if exists
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, unsigned short captureAmount); // Auxiliary function for building the tree moves
static void handleTreeOne(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeOne, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures); //Makes tree one.
static void handleTreeTwo(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeTwo, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures); //Makes tree two.

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
		*movesTree = FindSingleSourceMovesAux(board, src, currentPlayer, 0);
	}
	return (movesTree); // Returns the tree moves or a NULL in case the cell is free
}
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, unsigned short captureAmount)
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
	handleTreeOne(&baseTree, &treeOne, board, pl, src, options, captures, baseTree.source->total_captures_so_far); //Makes treeOne.
	handleTreeTwo(&baseTree, &treeTwo, board, pl, src, options, captures, baseTree.source->total_captures_so_far); //Makes treeTwo.

	// Free the arrays allocated at start
	free(options);
	free(captures);
	return (baseTree);
}

static void handleTreeOne(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeOne, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures)
{
	// handle sub tree one
	if ((options[0].col == 0) && (options[0].row == 0)) //If there is no left sub tree to merge into the base tree.
	{
		treeOne->source = NULL;
		initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
	}
	else
	{
		initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root.
		handleBoardChange(board, src, pl, 0, options, captures, &countCaptures);			   // Handles change due to next move update in the tree + update captures counter.
		*treeOne = FindSingleSourceMovesAux(board, options, pl, countCaptures);
		if (treeOne->source != NULL)
		{
			//treeOne->source->total_captures_so_far += baseTree->source->total_captures_so_far; // Update captures
		}
	}
	baseTree->source->next_move[0] = treeOne->source;
}

static void handleTreeTwo(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeTwo, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned short countCaptures)
{
	// handle sub tree two
	if ((options[1].col == 0) && (options[1].row == 0)) //if there is no right sub tree to merge into the base tree.
	{
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
		*treeTwo = FindSingleSourceMovesAux(board, options + 1, pl, countCaptures);
		if (treeTwo->source != NULL)
		{
			//treeTwo->source->total_captures_so_far += baseTree->source->total_captures_so_far; // Update captures.
		}
	}
	baseTree->source->next_move[1] = treeTwo->source;
	initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); //Getting back to the initial board.
}

