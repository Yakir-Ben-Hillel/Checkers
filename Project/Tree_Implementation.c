#include "PrototypesProject.h"
void allocateOptionsAndCaptures(checkersPos **options, checkersPos **captures)
{
	*options = (checkersPos *)calloc(2, sizeof(checkersPos));
	checkAllocation(options);
	*captures = (checkersPos *)calloc(2, sizeof(checkersPos));
	checkAllocation(captures);
}
void allocateTreeNode(SingleSourceMovesTree *baseTree, checkersPos *src)
{
	baseTree->source = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(baseTree->source);									// Checking whether the memory allocation succeeded or not
	baseTree->source->pos = (checkersPos *)malloc(sizeof(checkersPos)); // Allocating pointer to 'position' struct (checkersPos)
	checkAllocation(baseTree->source->pos);
	baseTree->source->pos->col = src->col; // Updating the position of the current node
	baseTree->source->pos->row = src->row; // Updating the position of the current node
}
void initializeBoardOfPlayer(Board board, player pl, Board *boardOfPlayer, checkersPos src, checkersPos *options, checkersPos *captures)
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
void initializePlayer(Board board, checkersPos *src, player *currentPlayer)
{
	*(currentPlayer) = board[src->row - 'A'][src->col - '0' - 1]; // Initializing the player found in the given coordinate
}
void makeLeaf(SingleSourceMovesTreeNode *leaf, checkersPos *src)
{
	leaf->pos->col = src->col;
	leaf->pos->row = src->row;
	leaf->next_move[0] = leaf->next_move[1] = NULL; //It's a leaf.
}
void handleLeaf(SingleSourceMovesTree *baseTree, Board board, player pl, checkersPos *src, checkersPos *options, checkersPos *captures)
{
	makeLeaf(baseTree->source, src);
	initializeBoardOfPlayer(board, pl, &baseTree->source->board, *src, options, captures); // Initializing board the current root
}