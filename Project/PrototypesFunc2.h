#pragma once 
#include "PrototypesProject.h"

typedef struct _SingleSourceMovesListCell {
	checkersPos						*position; // Indicataes the position of player 
	unsigned short					captures; // number of captures per position
	struct _SingleSourceMovesListCell	*next; // next move to be done
}SingleSourceMovesListCell;

typedef struct _SingleSourceMoveList {
	SingleSourceMovesListCell  *head;
	SingleSourceMovesListCell  *tail;
}SingleSourceMovesList;

#define MAX (a,b)  ( a > b ? a : b)

void freeList(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNode(checkersPos* pos, SingleSourceMovesListCell *next); // Creates a node in the list
void insertNodeToTail(SingleSourceMovesList* lst, SingleSourceMovesListCell *newTail); // Adding the new to the tail of the list  
void insertNodeToHead(SingleSourceMovesList* lst, SingleSourceMovesListCell *newHead); // Adding an element to the start of the list 
BOOL isEmptyList(SingleSourceMovesList* lst); // Determines whether the list is empty or not
void makeEmptyList(SingleSourceMovesList *lst); // Makes empty list 
void printList(SingleSourceMovesList* lst); // Prints the list of single source move

// Function 2
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree * movesTree);





	