
#include "PrototypesProject.h"
static void FindSingleSourceOptimalMoveAux(SingleSourceMovesTreeNode *source, SingleSourceMovesList **OptimalMoveList);
static void insertBestMove(SingleSourceMovesList **OptimalMoveList, SingleSourceMovesList **leftList, SingleSourceMovesList **rightList,
						   SingleSourceMovesTreeNode *source);

SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *movesTree)
{
	SingleSourceMovesList *OptimalMoveList = makeEmpty_List(); // Defined as pointer to avoid return of a local variable.
	// Making an empty list.
	// Count Captures of returned list.
	if (movesTree == NULL) // Empty tree case - design by contract- not suppose to happen.
	{
		return NULL;
	}
	else
	{
		FindSingleSourceOptimalMoveAux(movesTree->source, &OptimalMoveList);		// Finds the single source optimal moves.
		OptimalMoveList->head->captures = movesTree->source->total_captures_so_far; //Updating head captures.
	}
	return (OptimalMoveList); // Returns the List represents the single source optimal moves
}
static void FindSingleSourceOptimalMoveAux(SingleSourceMovesTreeNode *source, SingleSourceMovesList **OptimalMoveList)
{
	SingleSourceMovesList *leftList = makeEmpty_List(), *rightList = makeEmpty_List();
	SingleSourceMovesListCell *node;

	// Making empty lists for the sub trees.

	if ((source->next_move[0] == NULL) && (source->next_move[1] == NULL)) // A leaf - a single move tree- it is the optimal.
	{																	  //Inserting the new Leaf into the list.
		node = createNode(source->pos, (*OptimalMoveList)->head);
		(*OptimalMoveList)->head = (*OptimalMoveList)->tail = node;
		(*OptimalMoveList)->head->captures = source->total_captures_so_far; // Updating captures of the new node.
	}
	else
	{
		//	 Recursive calls
		if (source->next_move[0] != NULL)
		{
			FindSingleSourceOptimalMoveAux(source->next_move[0], &leftList);
			leftList->head->captures = source->next_move[0]->total_captures_so_far; // Updating captures of the new node
		}
		if (source->next_move[1] != NULL)
		{
			FindSingleSourceOptimalMoveAux(source->next_move[1], &rightList);
			rightList->head->captures = source->next_move[1]->total_captures_so_far; // Updating captures of the new node.
		}
		insertBestMove(OptimalMoveList, &leftList, &rightList, source);
		// Check which move is better from the 'returned' options of sub tree right and sub tree right.
	}
}

static void insertBestMove(SingleSourceMovesList **OptimalMoveList, SingleSourceMovesList **leftList, SingleSourceMovesList **rightList,
						   SingleSourceMovesTreeNode *source)
{									 //Check which moves are valid and insert the best move possible.
	SingleSourceMovesListCell *node; // Initialized due to security reasons.

	if ((*leftList)->head == NULL) //There is no left list.
	{							   //There is no left List.
		node = createNode(source->pos, (*rightList)->head);
		(*rightList)->head = node;
		insertListToHead(OptimalMoveList, *rightList); // Updating List from start
	}
	else if ((*rightList)->head == NULL) //There is no right list.
	{									 //There is no right List.
		node = createNode(source->pos, ((*leftList)->head));
		(*leftList)->head = node;
		insertListToHead(OptimalMoveList, (*leftList)); // Updating List from start
	}
	else if ((*leftList)->tail->captures == (*rightList)->tail->captures)
	{						 //Left list amount of captures is equal to the right one.
		if (rand() % 2 == 0) //Gamble who to choose, left or right.
		{					 //When 0 zero is returned, left list is chosen.
			node = createNode(source->pos, ((*leftList)->head));
			(*leftList)->head = node;
			insertListToHead(OptimalMoveList, (*leftList)); // Updating List from start
			freeList(*rightList);							//No use for rightList anymore.
		}
		else //rand()%2 returned 1.
		{	//When 1 is returned, right list is chosen.
			node = createNode(source->pos, (*rightList)->head);
			(*rightList)->head = node;
			insertListToHead(OptimalMoveList, (*rightList)); // Updating List from start.
			freeList(*leftList);							 //No use for leftList anymore.
		}
	}

	else if ((*leftList)->tail->captures > (*rightList)->tail->captures) // Left move is better
	{
		node = createNode(source->pos, ((*leftList)->head));
		(*leftList)->head = node;
		insertListToHead(OptimalMoveList, (*leftList)); // Updating List from start
		freeList(*rightList);							//No use for rightList anymore.
	}
	else // Right move is better
	{
		node = createNode(source->pos, (*rightList)->head);
		(*rightList)->head = node;
		insertListToHead(OptimalMoveList, (*rightList)); // Updating List from start.
		freeList(*leftList);							 //No use for leftList anymore.
	}
}
