#pragma once
#include "PrototypesFunc2.h"

typedef struct __MultipleSourceMovesListCell {
	SingleSourceMovesList *Single_Source_moves_list; // Pointer to a single source moves list
	struct __MultipleSourceMovesListCell * next; // Pointer to the next list
} MultipleSourceMovesListCell;

typedef struct __MultipleSingleSourceMovesList
{
	MultipleSourceMovesListCell *head; // Points to the first list in the multiple-source-moves list 
	MultipleSourceMovesListCell *tail; // Points to the last list in the multiple-source-moves list
}MultipleSingleSourceMovesList;

// Function 3 
MultipleSingleSourceMovesList* FindAllPossiblePlayerMoves(Board board, player player);

void freeLoList(MultipleSingleSourceMovesList* Lol);
MultipleSourceMovesListCell* createLolNode(SingleSourceMovesList* singleSourceMovesList, MultipleSourceMovesListCell *next); // Creates a node of List of lists 
void insertLolNodeToTail(MultipleSingleSourceMovesList* Lol, MultipleSourceMovesListCell *newTail); // Adding the new to the tail (last list) of the list  
//void insertLolNodeToHead(MultipleSingleSourceMovesList* Lol , MultipleSourceMovesListCell *newHead); // Adding the list to the start of the list of lists 
BOOL isEmptyLoList(MultipleSingleSourceMovesList* Lol); // Determines whether the list is empty or not
void makeEmptyLoList(MultipleSingleSourceMovesList *Lol); // Makes empty list 
void printLoList(MultipleSingleSourceMovesList* Lol); // Prints the list of single source move