#include "PrototypesProject.h"
// function1 Prototypes
// return in the options array the nearest possible coordinates for moving and in accordance the place of an eaten soldier if exists
static SingleSourceMovesTreeNode *FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, int countLevel, unsigned int countCaptures, int direction); // Auxiliary function for building the tree moves
static void initializePlayer(Board board, checkersPos *src, player *currentPlayer);																  // Initializing the player based on the given coordinate
static void initializeBoardOfPlayer(Board board, Board *boardOfPlayer);																			  // Initializing the board of a given coordinate
//static void allocateTreeNode(SingleSourceMovesTree *baseTree, checkersPos *src);														 // Allocates tree Node
static SingleSourceMovesTreeNode *allocateTreeNode(SingleSourceMovesTreeNode *baseTreeRoot, checkersPos *src); // Allocates tree Node
static void allocateOptionsAndCaptures(checkersPos **options, checkersPos **captures);						   //Allocate options and captures arrays.
static void makeLeaf(SingleSourceMovesTreeNode *leaf, checkersPos *src);									   //Make a leaf in the tree.


SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
	SingleSourceMovesTree *movesTree = NULL;
	player currentPlayer;
	unsigned int countCaptures = 0;
	int countLevel = 0, direction = 0;
	// Counts the level in the recursion
	if (!isCellFree(board, src)) // In case the cell is taken
	{
		initializePlayer(board, src, &currentPlayer);
		movesTree->source = FindSingleSourceMovesAux(board, src, currentPlayer, countLevel + 1, countCaptures, direction);
	}
	return (movesTree); // Returns the tree moves or a NULL in case the cell is free
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
static SingleSourceMovesTreeNode *FindSingleSourceMovesAux(Board board, checkersPos *src, player pl, int countLevel, unsigned int countCaptures, int direction)
{
	// Initialized due to security reasons
	SingleSourceMovesTreeNode *treeOneRoot = NULL, *treeTwoRoot = NULL, *baseTreeRoot = NULL;
	checkersPos *options = NULL, *captures = NULL;
	//unsigned int countCaptures = 0; // Counts captures
	// Allocating a tree node
	baseTreeRoot = allocateTreeNode(baseTreeRoot, src); //(&baseTree, src); // Updates position
	allocateOptionsAndCaptures(&options, &captures);
	if (countLevel == 1)
		baseTreeRoot->total_captures_so_far = 0;
	soldierStatus(board, src, pl, options, captures); // Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
	//baseTree.source->total_captures_so_far = 0;
	if (((src->row == 'H') && (pl == 'T')) || ((src->row == 'A') && (pl == 'B'))) //If reached the end of the board.
	{
		makeLeaf(baseTreeRoot, src); //(baseTree.source, src);
		return baseTreeRoot;
	}
	// handle sub tree one
	else if ((options[0].col == 0) && (options[0].row == 0)) //If there is no left sub tree to merge into the base tree
	{
		//treeOne.source = NULL;
		treeOneRoot = NULL;
		initializeBoardOfPlayer(board, &baseTreeRoot->board); // (board, &baseTree.source->board); // Initializing board the current root
	}
	// handle sub tree two
	else if ((options[1].col == 0) && (options[1].row == 0)) //if there is no right sub tree to merge into the base tree
	{
		treeTwoRoot = NULL;									  //treeTwo.source = NULL;
		initializeBoardOfPlayer(board, &baseTreeRoot->board); //(board, &baseTree.source->board); // Initializing board the current root
	}
	else
	{

		//soldierStatus(board, src, pl, options, captures); // Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
		
		//baseTree.source->total_captures_so_far += countCaptures; // Updates captures so far
		baseTreeRoot->total_captures_so_far += countCaptures; // Updates captures so far
															  //Connecting sub - Trees to the base Tree + recursive calls
		if (direction==0)
		{
		initializeBoardOfPlayer(board, &baseTreeRoot->board);					 //(board, &baseTree.source->board);				 // Initializing board the current root
		handleBoardChange(board, src, pl, direction , options, captures, &countCaptures); //Does the required step.
		printBoard(board);
		//Prints the board after the step.
		//printBoard(baseTree.source->board);
		printBoard(baseTreeRoot->board);
		}
		
		//tree = FindSingleSourceMovesAux(board, options, pl, countLevel + 1);
		direction = 0;
		treeOneRoot = FindSingleSourceMovesAux(board, options, pl, countLevel + 1, countCaptures, direction);
		//baseTree.source->total_captures_so_far += treeOne.source->total_captures_so_far; // Update captures
		baseTreeRoot->total_captures_so_far = countCaptures;

		baseTreeRoot->next_move[0] = treeOneRoot; //baseTree.source->next_move[0] = treeOne.source;
		if (direction==1)
		{
		initializeBoardOfPlayer(board, &baseTreeRoot->board); //(board, &baseTree.source->board);
		// Initializing board the current root
		handleBoardChange(board, src, pl, 1, options, captures, &countCaptures); // Handles change due to next move update in the tree + update captures counter
		printBoard(board);
		printBoard(baseTreeRoot->board);
		//printBoard(baseTree.source->board);
		}
		direction=1;
		treeTwoRoot = FindSingleSourceMovesAux(board, options + 1, pl, countLevel + 1, countCaptures, direction); //treeTwo = FindSingleSourceMovesAux(board, options + 1, pl, countLevel + 1);
		baseTreeRoot->total_captures_so_far = countCaptures;
		//baseTree.source->total_captures_so_far += treeTwo.source->total_captures_so_far; // Update captures
	}
	baseTreeRoot->next_move[1] = treeTwoRoot;
	//baseTree.source->next_move[1] = treeTwo.source;

	// Free the arrays allocated at start
	free(options);
	free(captures);
	return (baseTreeRoot); //return (baseTree);
}
static void allocateOptionsAndCaptures(checkersPos **options, checkersPos **captures)
{
	*options = (checkersPos *)calloc(2, sizeof(checkersPos));
	checkAllocation(options);
	*captures = (checkersPos *)calloc(2, sizeof(checkersPos));
	checkAllocation(captures);
}
// SingleSourceMovesTreeNode  instead of void
static SingleSourceMovesTreeNode *allocateTreeNode(SingleSourceMovesTreeNode *baseTreeRoot, checkersPos *src) //(SingleSourceMovesTree *baseTree, checkersPos *src)
{
	baseTreeRoot = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(baseTreeRoot);									// Checking whether the memory allocation succeeded or not
	baseTreeRoot->pos = (checkersPos *)malloc(sizeof(checkersPos)); // Allocating pointer to 'position' struct (checkersPos)
	checkAllocation(baseTreeRoot->pos);
	baseTreeRoot->pos->col = src->col; // Updating the position of the current node
	baseTreeRoot->pos->row = src->row; // Updating the position of the
	// addition
	return (baseTreeRoot);
	// baseTree->source = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
	// checkAllocation(baseTree->source);									// Checking whether the memory allocation succeeded or not
	// baseTree->source->pos = (checkersPos *)malloc(sizeof(checkersPos)); // Allocating pointer to 'position' struct (checkersPos)
	// checkAllocation(baseTree->source->pos);
	// baseTree->source->pos->col = src->col; // Updating the position of the current node
	// baseTree->source->pos->row = src->row; // Updating the position of the current node
}
static void initializeBoardOfPlayer(Board board, Board *boardOfPlayer)
{
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
{													// Remember to initialize options array and captures array with '0' in each cell of the arrays
	if (options[0].col == 0 && options[0].row == 0) // first cell is empty
	{
		options[0].col = soldier->col;
		options[0].row = soldier->row;
	}
	else if (options[1].col == 0 && options[1].row == 0) // second cell is empty
	{
		options[1].col = soldier->col;
		options[1].row = soldier->row;
	}
	return; // in case both cells are taken
}
void fillCaptures(checkersPos *soldier, checkersPos *captures, int direction)
{													  // Remember to initialize options array and captures array with '0' in each cell of the arrays
	if (captures[0].col == 0 && captures[0].row == 0) // first cell is empty
	{
		captures[0].col = soldier->col;
		captures[0].row = soldier->row;
	}
	else if (captures[1].col == 0 && captures[1].row == 0) // second cell is empty
	{
		captures[1].col = captures->col;
		captures[1].row = captures->row;
	}
	return; // in case both cells are taken
}
void printBoard(Board board) // debugging purpose only
{
	printf("\n\n");
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			printf("%c||", board[i][j]);
		}
		printf("\n");
	}
}
void printTreeInOrder(SingleSourceMovesTree *movesTree)
{
	if (movesTree == NULL)
		return;
	else
	{
		printTreeInOrderAux(movesTree->source);
		printf("\n");
	}
}
void printTreeInOrderAux(SingleSourceMovesTreeNode *source)
{
	if (source == NULL)
		return;
	else
	{
		printTreeInOrderAux(source->next_move[0]);
		printf("%c%c ", source->pos->row, source->pos->col);
		printTreeInOrderAux(source->next_move[1]);
	}
}

