#include "PrototypesProject.h"
// function1 Prototypes
// return in the options array the nearest possible coordinates for moving and in accordance the place of an eaten soldier if exists
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, int countLevel); // Auxiliary function for building the tree moves
static void initializePlayer(Board board, checkersPos *src, player *currentPlayer);								 // Initializing the player based on the given coordinate
static void initializeBoardOfPlayer(Board board, player pl, Board *boardOfPlayer, checkersPos src, checkersPos *options, checkersPos *captures);
static void allocateTreeNode(SingleSourceMovesTree *baseTree, checkersPos *src);	   // Allocates tree Node
static void allocateOptionsAndCaptures(checkersPos **options, checkersPos **captures); //Allocate options and captures arrays.
static void makeLeaf(SingleSourceMovesTreeNode *leaf, checkersPos *src);			   //Makes a leaf.
static void handleLeaf(SingleSourceMovesTree *baseTree, Board board, player pl, checkersPos *src, checkersPos *options, checkersPos *captures);
static unsigned int updateCountCaptures(checkersPos *captures); //Update the amount of captures.

static void handleTreeOne(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeOne, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned int *countCaptures, int countLevel); //Makes tree one.
static void handleTreeTwo(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeTwo, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned int *countCaptures, int countLevel); //Makes tree two.

//Make a leaf in the tree.

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
	SingleSourceMovesTree *movesTree = NULL;
	player currentPlayer;
	int countLevel = 0;			 // Counts the level in the recursion
	if (!isCellFree(board, src)) // In case the cell is taken
	{
		initializePlayer(board, src, &currentPlayer);
		movesTree = (SingleSourceMovesTree *)malloc(sizeof(SingleSourceMovesTree));
		checkAllocation(movesTree);
		*movesTree = FindSingleSourceMovesAux(board, src, currentPlayer, countLevel + 1);
	}
	return (movesTree); // Returns the tree moves or a NULL in case the cell is free
}
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, int countLevel)
{
	// Initialized due to security reasons
	SingleSourceMovesTree treeOne = {NULL}, treeTwo = {NULL}, baseTree = {NULL};
	checkersPos *options = NULL, *captures = NULL;
	unsigned int countCaptures = 0; // Counts captures
	// Allocating a tree node
	allocateTreeNode(&baseTree, src); // Updates position
	allocateOptionsAndCaptures(&options, &captures);
	//	if (countLevel == 1)
	baseTree.source->total_captures_so_far = 0;

	// Compliment case - Connecting sub - Trees to the base Tree + recursive calls
	if (((src->row == 'H') && (pl == 'T')) || ((src->row == 'A') && (pl == 'B'))) //If reached the end of the board.
	{
		handleLeaf(&baseTree, board, pl, src, options, captures); //Makes and returns the a leaf.
		return baseTree;
	}
	soldierStatus(board, src, pl, options, captures);
	// Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
	countCaptures = updateCountCaptures(captures);			 //update the amount of captures as been on this part of the recursion.
	baseTree.source->total_captures_so_far += countCaptures; // Updates captures so far

	handleTreeOne(&baseTree, &treeOne, board, pl, src, options, captures, &countCaptures, countLevel); //Makes treeOne.
	handleTreeTwo(&baseTree, &treeTwo, board, pl, src, options, captures, &countCaptures, countLevel); //Makes treeTwo.

	// Free the arrays allocated at start
	free(options);
	free(captures);
	return (baseTree);
}

static void handleLeaf(SingleSourceMovesTree *baseTree, Board board, player pl, checkersPos *src, checkersPos *options, checkersPos *captures)
{
	makeLeaf(baseTree->source, src);
	initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
}
static unsigned int updateCountCaptures(checkersPos *captures)
{
	int counter = 0;
	if ((captures[0].col != 0) && (captures[0].row != 0))
		counter++;
	if ((captures[1].col != 0) && (captures[1].row != 0))
		counter++;
	return counter;
}
static void handleTreeOne(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeOne, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned int *countCaptures, int countLevel)
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
		handleBoardChange(board, src, pl, 0, options, captures, countCaptures);				   // Handles change due to next move update in the tree + update captures counter.
		*treeOne = FindSingleSourceMovesAux(board, options, pl, countLevel + 1);
		if (treeOne->source != NULL)
		{
			baseTree->source->total_captures_so_far += treeOne->source->total_captures_so_far; // Update captures
		}
	}
	baseTree->source->next_move[0] = treeOne->source;
}

static void handleTreeTwo(SingleSourceMovesTree *baseTree, SingleSourceMovesTree *treeTwo, Board board, player pl, checkersPos *src,
						  checkersPos *options, checkersPos *captures, unsigned int *countCaptures, int countLevel)
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
		handleBoardChange(board, src, pl, 1, options, captures, countCaptures);				   // Handles change due to next move update in the tree + update captures counter.
		*treeTwo = FindSingleSourceMovesAux(board, options + 1, pl, countLevel + 1);
		if (treeTwo->source != NULL)
		{
			baseTree->source->total_captures_so_far += treeTwo->source->total_captures_so_far; // Update captures.
		}
	}
	baseTree->source->next_move[1] = treeTwo->source;
	initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); //Getting back to the initial board.
}

static void initializePlayer(Board board, checkersPos *src, player *currentPlayer)
{
	*(currentPlayer) = board[src->row - 'A'][src->col - '0' - 1]; // Initializing the player found in the given coordinate
}
static void makeLeaf(SingleSourceMovesTreeNode *leaf, checkersPos *src)
{
	leaf->pos->col = src->col;
	leaf->pos->row = src->row;
	leaf->next_move[0] = leaf->next_move[1] = NULL; //It's a leaf.
}

static void allocateOptionsAndCaptures(checkersPos **options, checkersPos **captures)
{
	*options = (checkersPos *)calloc(2, sizeof(checkersPos));
	checkAllocation(options);
	*captures = (checkersPos *)calloc(2, sizeof(checkersPos));
	checkAllocation(captures);
}
static void allocateTreeNode(SingleSourceMovesTree *baseTree, checkersPos *src)
{
	baseTree->source = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(baseTree->source);									// Checking whether the memory allocation succeeded or not
	baseTree->source->pos = (checkersPos *)malloc(sizeof(checkersPos)); // Allocating pointer to 'position' struct (checkersPos)
	checkAllocation(baseTree->source->pos);
	baseTree->source->pos->col = src->col; // Updating the position of the current node
	baseTree->source->pos->row = src->row; // Updating the position of the current node
}
static void initializeBoardOfPlayer(Board board, player pl, Board *boardOfPlayer, checkersPos src, checkersPos *options, checkersPos *captures)
{
	player enemy;
	if (pl == 'B')
		enemy = 'T';
	else
	{
		enemy = 'B';
	}
	if (options[0].col != 0 && options[0].row != 0)
		board[(int)options[0].row - 'A'][(int)options[0].col - '0' - 1] = ' ';
	if (options[1].col != 0 && options[1].row != 0)
		board[(int)options[1].row - 'A'][(int)options[1].col - '0' - 1] = ' ';
	if (captures[0].row != 0 && captures[0].col != 0)
		board[(int)captures[0].row - 'A'][(int)captures[0].col - '0' - 1] = enemy;
	if (captures[1].row != 0 && captures[1].col != 0)
		board[(int)captures[1].row - 'A'][(int)captures[1].col - '0' - 1] = enemy;
	board[(int)src.row - 'A'][(int)src.col - '0' - 1] = pl;

	int i = 0, j = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			(*boardOfPlayer)[i][j] = board[i][j];
		}
	}
}
void checkAllocation(void *address)
{
	if (!address)
	{
		fprintf(stderr, "Memory Allocation Error!\n");
		exit(ALLOCATION_ERROR);
	}
}
void fillOptions(checkersPos *soldier, checkersPos *options, int direction)
{																	  // Remember to initialize options array and captures array with '0' in each cell of the arrays
	if (options[0].col == 0 && options[0].row == 0 && direction == 0) // first cell is empty
	{
		options[0].col = soldier->col;
		options[0].row = soldier->row;
	}
	else if (options[1].col == 0 && options[1].row == 0 && direction == 1) // second cell is empty
	{
		options[1].col = soldier->col;
		options[1].row = soldier->row;
	}
	return; // in case both cells are taken
}
void fillCaptures(checkersPos *soldier, checkersPos *captures, int direction)
{																		// Remember to initialize options array and captures array with '0' in each cell of the arrays
	if (captures[0].col == 0 && captures[0].row == 0 && direction == 0) // first cell is empty
	{
		captures[0].col = soldier->col;
		captures[0].row = soldier->row;
	}
	else if (captures[1].col == 0 && captures[1].row == 0 && direction == 1) // second cell is empty
	{
		captures[1].col = soldier->col;
		captures[1].row = soldier->row;
	}
	return; // in case both cells are taken
}
