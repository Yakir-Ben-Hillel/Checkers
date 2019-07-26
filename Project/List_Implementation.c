#include "PrototypesProject.h"

void PrintOpener();
void fillStartingBoard(Board *board);

void freeList(SingleSourceMovesList *lst)
{
	SingleSourceMovesListCell *next = NULL, *current = NULL;

	current = lst->head;

	while (current != NULL)
	{
		next = current->next;	// Saving the pointer to the next cell
		free(current->position); // Free the 'inner' Allocated memory
		free(current);			 // Free the current cell
		current = next;			 // Promoting the temp index to a cell in the list
	}
	free(lst);
}
SingleSourceMovesList *makeEmpty_List()
{
	SingleSourceMovesList *lst = (SingleSourceMovesList *)malloc(sizeof(SingleSourceMovesList));
	checkAllocation(lst);
	lst->head = lst->tail = NULL; // Initializing pointers to head and tail to NULL
	return lst;
}

BOOL isEmptyList(SingleSourceMovesList *lst)
{
	return (lst->head == NULL);
}
SingleSourceMovesListCell *createNode(checkersPos *pos, SingleSourceMovesListCell *next)
{
	SingleSourceMovesListCell *node;
	node = (SingleSourceMovesListCell *)malloc(sizeof(SingleSourceMovesListCell)); // Allocate the cell
	checkAllocation(node);
	node->position = (checkersPos *)malloc(sizeof(checkersPos));
	checkAllocation(node->position);
	// Filling the 'data field'
	node->position->col = pos->col;
	node->position->row = pos->row;
	// Updating pointer to the next cell
	node->next = next;

	return (node); // Returns allocated node
}
void insertNodeToTail(SingleSourceMovesList *lst, SingleSourceMovesListCell *newTail)
{
	newTail->next = NULL; // Validating the new node's pointer to the next cell is NULL

	if (isEmptyList(lst)) // In case the list is empty
		lst->head = lst->tail = newTail;
	else // the list isn't empty
	{
		lst->tail->next = newTail; // Connecting the new node to the tail
		lst->tail = newTail;	   // Updating the tail
	}
}
void insertListToHead(SingleSourceMovesList **lst, SingleSourceMovesList *newHead)
{
	if (isEmptyList(*lst))
	{
		(*lst) = newHead;
	}
	else
	{
		newHead->tail->next = (*lst)->head; // Validating the new node's pointer to head - connection to the current head
		(*lst)->head = newHead->head;
	}
}
void freeLoList(MultipleSingleSourceMovesList *Lol)
{
	MultipleSourceMovesListCell *currentLol = NULL;

	// Initializing pointers to nodes
	currentLol = Lol->head;

	while (currentLol != NULL)
	{
		// Free inner lists
		freeList(currentLol->Single_Source_moves_list);
		currentLol = currentLol->next; // Updating pointer to (inner) list
	}
}
MultipleSourceMovesListCell *createLolNode(SingleSourceMovesList *singleSourceMovesList, MultipleSourceMovesListCell *next) // Creates a node of List of lists
{
	MultipleSourceMovesListCell *node;
	node = (MultipleSourceMovesListCell *)malloc(sizeof(MultipleSourceMovesListCell)); // Allocate the cell
	checkAllocation(node);
	node->Single_Source_moves_list = singleSourceMovesList; // Updating the list received to be the cell in the multiple Source List cell
	// Updating pointer to the next cell
	node->next = next;

	return (node); // Returns allocated node
}
void insertLolNodeToTail(MultipleSingleSourceMovesList *Lol, MultipleSourceMovesListCell *newTail) // Adding the new to the tail (last list) of the list
{
	newTail->next = NULL; // Validating the new node's pointer to the next cell is NULL

	if (isEmptyLoList(Lol)) // In case the list is empty
		Lol->head = Lol->tail = newTail;
	else // the list isn't empty
	{
		Lol->tail->next = newTail; // Connecting the new node to the tail
		Lol->tail = newTail;	   // Updating the tail
	}
}
//void insertLolNodeToHead(MultipleSingleSourceMovesList* Lol, MultipleSourceMovesListCell *newHead); // Adding the list to the start of the list of lists
BOOL isEmptyLoList(MultipleSingleSourceMovesList *Lol) // Determines whether the list is empty or not
{
	return (Lol->head == NULL);
}
MultipleSingleSourceMovesList *makeEmpty_LoList() // Makes empty list
{
	MultipleSingleSourceMovesList *Lol;
	Lol = (MultipleSingleSourceMovesList *)malloc(sizeof(MultipleSingleSourceMovesList));
	checkAllocation(Lol);
	Lol->head = Lol->tail = NULL; // Initializing pointers to head and tail to NULL
	return Lol;
}
