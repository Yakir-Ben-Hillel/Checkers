#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 8

#define TRUE 1
#define FALSE 0
#define ALLOCATION_ERROR -1
#define MAX(a, b) (a > b ? a : b)

typedef int BOOL;

/*Structs*/

typedef struct __checkersPos
{
    char row, col;
} checkersPos;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char player;
typedef struct __SingleSourceMovesTreeNode
{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far;             //Number of Captures
    struct __SingleSourceMovesTreeNode *next_move[2]; // movement destinations
} SingleSourceMovesTreeNode;

typedef struct __SingleSourceMovesTree
{
    SingleSourceMovesTreeNode *source;
} SingleSourceMovesTree;

typedef struct __SingleSourceMovesList
{
    struct __SingleSourceMovesListCell *head;
    struct __SingleSourceMovesListCell *tail;
} SingleSourceMovesList;
typedef struct __SingleSourceMovesListCell
{
    checkersPos *position;                    // Indicates the position of player
    unsigned short captures;                  // number of captures per position
    struct __SingleSourceMovesListCell *next; // next move to be done
} SingleSourceMovesListCell;

typedef struct __MultipleSourceMovesListCell
{
    struct __SingleSourceMovesList *Single_Source_moves_list; // Pointer to a single source moves list
    struct __MultipleSourceMovesListCell *next;               // Pointer to the next list
} MultipleSourceMovesListCell;

typedef struct __MultipleSingleSourceMovesList
{
    struct __MultipleSourceMovesListCell *head; // Points to the first list in the multiple-source-moves list
    struct __MultipleSourceMovesListCell *tail; // Points to the last list in the multiple-source-moves list
} MultipleSingleSourceMovesList;
/*Structs*/

/*Declartions*/
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
void checkAllocation(void *address);
void handleBoardChange(Board board, checkersPos *src, player pl, int direction, checkersPos *options, checkersPos *captures, unsigned short *countCaptures);
void fillStartingBoard(Board *board);

//Fill
void fillOptions(checkersPos *soldier, checkersPos *options, int direction);
void fillCaptures(checkersPos *soldier, checkersPos *captures, int direction);
//Fill

/*Tests*/
BOOL isThereACapture(checkersPos *options, checkersPos *captures, int *ind); // Determines whether there's an option of a move with a
void soldierStatus(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures); //Added option for player(inserting B OR T).
BOOL isCellFree(Board board, checkersPos *soldier);
/*Tests*/

/*Printing*/
void printTreeInOrder(SingleSourceMovesTree *movesTree);
void printBoard(Board board);
void printTreeBoardInOrderAux(SingleSourceMovesTreeNode *source);

void printTreeInOrderAux(SingleSourceMovesTreeNode *source);
void printTreeSourcesInOrderAux(SingleSourceMovesTreeNode *source);

// void printTreeSourcesInOrderAux(SingleSourceMovesTreeNode *source);
void PrintOpener();

/*Printing*/

/*Tree Implementations*/
 void initializePlayer(Board board, checkersPos *src, player *currentPlayer);											   // Initializing the player based on the given coordinate
 void initializeBoardOfPlayer(Board board, player pl, Board *boardOfPlayer, checkersPos src, checkersPos *options, checkersPos *captures);
 void allocateTreeNode(SingleSourceMovesTree *baseTree, checkersPos *src);	   // Allocates tree Node
 void allocateOptionsAndCaptures(checkersPos **options, checkersPos **captures); //Allocate options and captures arrays.
 void makeLeaf(SingleSourceMovesTreeNode *leaf, checkersPos *src);			   //Makes a leaf.
 void handleLeaf(SingleSourceMovesTree *baseTree, Board board, player pl, checkersPos *src, checkersPos *options, checkersPos *captures);
/*Tree Implementations*/


//List Implementations.
void freeList(SingleSourceMovesList *lst);
SingleSourceMovesListCell *createNode(checkersPos *pos, SingleSourceMovesListCell *next); // Creates a node in the list
void insertNodeToTail(SingleSourceMovesList *lst, SingleSourceMovesListCell *newTail);    // Adding the new to the tail of the list
void insertListToHead(SingleSourceMovesList **lst, SingleSourceMovesList*newHead);    // Adding an element to the start of the list
BOOL isEmptyList(SingleSourceMovesList *lst);                                             // Determines whether the list is empty or not
void makeEmptyList(SingleSourceMovesList **lst);                                          // Makes empty list
void printList(SingleSourceMovesList *lst);                                               // Prints the list of single source move
//List Implementations.

// Function 2
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *movesTree);

// Function 3
MultipleSingleSourceMovesList *FindAllPossiblePlayerMoves(Board board, player player);

void freeLoList(MultipleSingleSourceMovesList *Lol);
MultipleSourceMovesListCell *createLolNode(SingleSourceMovesList *singleSourceMovesList, MultipleSourceMovesListCell *next); // Creates a node of List of lists
void insertLolNodeToTail(MultipleSingleSourceMovesList *Lol, MultipleSourceMovesListCell *newTail);                          // Adding the new to the tail (last list) of the list
//void insertLolNodeToHead(MultipleSingleSourceMovesList* Lol , MultipleSourceMovesListCell *newHead); // Adding the list to the start of the list of lists
BOOL isEmptyLoList(MultipleSingleSourceMovesList *Lol);   // Determines whether the list is empty or not
void makeEmptyLoList(MultipleSingleSourceMovesList *Lol); // Makes empty list
void printLoList(MultipleSingleSourceMovesList *Lol);     // Prints the list of single source move

/*Declartions*/
