#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 8

#define TRUE 1
#define FALSE 0
#define ALLOCATION_ERROR -1
typedef int BOOL;
/*Structs*/
typedef struct _checkersPos
{
    char row, col;
} checkersPos;
/*Structs*/
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char player;
typedef struct _SingleSourceMovesTreeNode
{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far;            //Number of Captures
    struct _SingleSourceMovesTreeNode *next_move[2]; // movement destinations
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
    SingleSourceMovesTreeNode *source;
} SingleSourceMovesTree;

/*Declartions*/
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos* src);
void checkAllocation(void *address);
void handleBoardChange(Board board, checkersPos* src, player pl, int direction, checkersPos *options, checkersPos *captures, unsigned int *countCaptures);
void fillStartingBoard(Board *board);

//Fill
void fillOptions(checkersPos *soldier, checkersPos *options,int direction);
void fillCaptures(checkersPos *soldier, checkersPos *captures,int direction);
//Fill

/*Tests*/
void soldierStatus(Board board, checkersPos* src, player pl, checkersPos *options, checkersPos *captures); //Added option for player(inserting B OR T).
BOOL isCellFree(Board board, checkersPos* soldier);
/*Tests*/

/*Printing*/
void printTreeInOrder(SingleSourceMovesTree *movesTree);
void printTreeBoardInOrderAux(SingleSourceMovesTreeNode *source);
void printTreeSourcesInOrderAux(SingleSourceMovesTreeNode *source);
void printBoard(Board board);
void PrintOpener();

/*Printing*/


/*Declartions*/
