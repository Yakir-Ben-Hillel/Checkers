#include "PrototypesProject.h"

void PrintOpener();
void fillStartingBoard(Board *board);


void printList(SingleSourceMovesList* lst)
{
	SingleSourceMovesListCell * current = lst->head;

	while (current != NULL)
	{
		printf("%d%d ", lst->head->position->col, lst->head->position->row); // Printing the coordinates of the current position
		current = current->next; // Updating the "pointer" to cell in the list
	}
}
void freeList(SingleSourceMovesList* lst)
{
	SingleSourceMovesListCell * next = NULL, *current = NULL;

	current = lst->head;

	while (current != NULL)
	{
		next = current->next; // Saving the pointer to the next cell 
		free(current->position); // Free the 'inner' Allocated memory 
		free(current); // Free the current cell
		current = next; // Promoting the temp index to a cell in the list
	}
}
void makeEmptyList(SingleSourceMovesList *lst)
{
	lst->head = lst->tail = NULL; // Initializing pointers to head and tail to NULL
}
BOOL isEmptyList(SingleSourceMovesList* lst)
{
	return(lst->head == NULL);
}

SingleSourceMovesListCell* createNode(checkersPos* pos, SingleSourceMovesListCell *next)
{
	SingleSourceMovesListCell* node = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell)); // Allocate the cell
	checkAllocation(node);
	node->position = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocation(node->position);
	// Filling the 'data field'
	node->position->col = pos->col;
	node->position->row = pos->row;
	// Updating pointer to the next cell
	node->next = next;

	return (node); // Returns allocated node
}
void insertNodeToTail(SingleSourceMovesList* lst, SingleSourceMovesListCell *newTail)
{
	newTail->next = NULL; // Validating the new node's pointer to the next cell is NULL

	if (isEmptyList(lst)) // In case the list is empty
		lst->head = lst->tail = newTail;
	else // the list isn't empty
	{
		lst->tail->next = newTail; // Connecting the new node to the tail
		lst->tail = newTail; // Updating the tail
	}
}
void insertNodeToHead(SingleSourceMovesList* lst, SingleSourceMovesListCell *newHead)
{
	newHead->next = lst->head; // Validating the new node's pointer to head - connection to the current head

	if (isEmptyList(lst)) // In case the list is empty
		lst->head = lst->tail = newHead;
	else // the list isn't empty
	{
		lst->head = newHead; // Updating the head
	}
}

void freeLoList(MultipleSingleSourceMovesList* Lol)
{
	MultipleSourceMovesListCell *next = NULL, *currentLol = NULL;

	// Initializing pointers to nodes
	currentLol = Lol->head;

	while (currentLol != NULL)
	{
		// Free inner lists
		freeList(currentLol->Single_Source_moves_list);
	}
	currentLol = currentLol->next; // Updating pointer to (inner) list
}

MultipleSourceMovesListCell* createLolNode(SingleSourceMovesList* singleSourceMovesList, MultipleSourceMovesListCell *next) // Creates a node of List of lists 
{
	MultipleSourceMovesListCell* node = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell)); // Allocate the cell
	checkAllocation(node);
	node->Single_Source_moves_list = singleSourceMovesList; // Updating the list recieved to be the cell in the multiple Source List cell
	// Updating pointer to the next cell
	node->next = next;

	return (node); // Returns allocated node
}


void insertLolNodeToTail(MultipleSingleSourceMovesList* Lol, MultipleSourceMovesListCell *newTail) // Adding the new to the tail (last list) of the list  
{
	newTail->next = NULL; // Validating the new node's pointer to the next cell is NULL

	if (isEmptyLoList(Lol)) // In case the list is empty
		Lol->head = Lol->tail = newTail;
	else // the list isn't empty
	{
		Lol->tail->next = newTail; // Connecting the new node to the tail
		Lol->tail = newTail; // Updating the tail	
	}
}
//void insertLolNodeToHead(MultipleSingleSourceMovesList* Lol, MultipleSourceMovesListCell *newHead); // Adding the list to the start of the list of lists 
BOOL isEmptyLoList(MultipleSingleSourceMovesList* Lol) // Determines whether the list is empty or not
{
	return(Lol->head == NULL);
}
void makeEmptyLoList(MultipleSingleSourceMovesList *Lol) // Makes empty list 
{
	Lol->head = Lol->tail = NULL; // Initializing pointers to haid and tail to NULL
	Lol->head->next = NULL;
}

void printLoList(MultipleSingleSourceMovesList* Lol)// Prints the list of single source move
{
	MultipleSourceMovesListCell *currentListP = Lol->head;

	while (currentListP != NULL)
	{
		printList(currentListP->Single_Source_moves_list);
		printf("\n");
	}
}


void fillStartingBoard(Board *board)
{
	int i = 0, j = 0;

	// Filling top -A TO C
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (((i % 2 == 0) && (j % 2 == 1)) || ((i % 2 == 1) && (j % 2 == 0)))
				(*board)[i][j] = 'T'; // Top player
			else
				(*board)[i][j] = ' ';
		}
	}
	// Filling middle- 2 empty rows - D , E
	for (i = 3; i < 5; i++)
		for (j = 0; j < 8; j++)
			(*board)[i][j] = ' ';
	// Filling bottom - F TO H
	for (i = 5; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (((i % 2 == 0) && (j % 2 == 1)) || ((i % 2 == 1) && (j % 2 == 0)))
				(*board)[i][j] = 'B'; // Bottom player
			else
				(*board)[i][j] = ' ';
		}
	}
}
void PrintOpener()
{
	printf(":'$$$$$$::'$$::::'$$:'$$$$$$$$::'$$$$$$::'$$:::'$$:'$$$$$$$$:'$$$$$$$$:::'$$$$$$::\n");
	printf("'$$... $$: $$:::: $$: $$.....::'$$... $$: $$::'$$:: $$.....:: $$.... $$:'$$... $$:\n");
	printf("$$:::..:: $$:::: $$: $$::::::: $$:::..:: $$:'$$::: $$::::::: $$:::: $$: $$:::..::\n");
	printf("$$::::::: $$$$$$$$$: $$$$$$::: $$::::::: $$$$$:::: $$$$$$::: $$$$$$$$::. $$$$$$::\n");
	printf("$$::::::: $$.... $$: $$...:::: $$::::::: $$. $$::: $$...:::: $$.. $$::::..... $$:\n");
	printf("$$::: $$: $$:::: $$: $$::::::: $$::: $$: $$:. $$:: $$::::::: $$::. $$::'$$::: $$:\n");
	printf(".$$$$$$:: $$:::: $$: $$$$$$$$:. $$$$$$:: $$::. $$: $$$$$$$$: $$:::. $$:. $$$$$$::\n");
	printf(":......:::..:::::..::........:::......:::..::::..::........::..:::::..:::......:::\n");
	printf("\n\n\n");
}