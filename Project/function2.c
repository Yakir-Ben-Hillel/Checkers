
#include "PrototypesProject.h"
static void FindSingleSourceOptimalMoveAux(SingleSourceMovesTreeNode *source, SingleSourceMovesList *OptimalMoveList, unsigned short count);

SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *movesTree)
{ // Initialized due to security reasons
	SingleSourceMovesList *OptimalMoveList= NULL; // Defined as pointer to avoid return of a local variable
	makeEmptyList(OptimalMoveList); // Making an empty list
	unsigned short countCap = 0;	// Count Captures of returned list

	if (movesTree->source == NULL) // Empty tree case - design by contract- not suppose to happen
	{
		return NULL;
	}
	else
	{
		FindSingleSourceOptimalMoveAux(movesTree->source, OptimalMoveList, countCap); // Finds the single source optimal moves
	}
	return(OptimalMoveList); // Returns the List represents the single source optimal moves
}
static void FindSingleSourceOptimalMoveAux(SingleSourceMovesTreeNode *source, SingleSourceMovesList *OptimalMoveList, unsigned short count)
{
	unsigned short countLeft = 0, countRight = 0; // Counts captures of move
	SingleSourceMovesList *leftList = NULL, *rightList = NULL;
	makeEmptyList(leftList);
	makeEmptyList(rightList); // Making empty lists for the sub trees

	if ((source->next_move[0] == NULL) && (source->next_move[1] == NULL)) // A leaf - a single move tree- it is the optimal
	{
		if (isEmptyList(OptimalMoveList)) // The list is empty
		{
			insertNodeToHead(OptimalMoveList, createNode(source->pos, OptimalMoveList->head)); // Updating List from start
			OptimalMoveList->head->captures = source->total_captures_so_far;				   // Updating captures of the new node
		}
		else if (source->total_captures_so_far > OptimalMoveList->head->captures) // The number of captures from the current position given by the tree moves is bigger than the existed
		{																		  // Updating the node in the list
			OptimalMoveList->head->position->row = source->pos->row;
			OptimalMoveList->head->position->col = source->pos->col;
		}
	}
	else
	{
		//	 Recursive calls
		if (source->next_move[0] != NULL) // Avoiding unnecessary recursive calls
			FindSingleSourceOptimalMoveAux(source->next_move[0], leftList, countLeft);
		if (source->next_move[1] != NULL) // Avoiding unnecessary recursive calls
			FindSingleSourceOptimalMoveAux(source->next_move[1], rightList, countRight);

		// Check which move is better from the 'returned' options of sub tree right and sub tree right
		if (countLeft > countRight) // Left move is better
		{
			insertNodeToHead(leftList, createNode(source->pos, leftList->head)); // Connecting the source of the main tree to the left list
			leftList->head->captures = source->total_captures_so_far;			 // Updating captures of the new node
		}
		else // Right move is better
		{
			insertNodeToHead(rightList, createNode(source->pos, rightList->head)); // Connecting the source of the main tree to the right list
			rightList->head->captures = source->total_captures_so_far;			   // Updating captures of the new node
		}
		count = countLeft + countRight + source->total_captures_so_far; // Updating the counter
	}
}