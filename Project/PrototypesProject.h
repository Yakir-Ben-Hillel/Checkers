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
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos src);
void checkAllocation(void *address);
void printBoard(Board board); // debugging purpose only
void printTreeInOrder(SingleSourceMovesTree *movesTree);
void printTreeInOrderAux(SingleSourceMovesTreeNode *source);
void handleBoardChange(Board board, checkersPos src, player pl, int direction, checkersPos *options, checkersPos *captures, unsigned int *countCaptures);

//Fill
void fillOptions(checkersPos *soldier, checkersPos *options);
void fillCaptures(checkersPos *soldier, checkersPos *captures);
//Fill

/*Tests*/
void soldierStatus(Board board, checkersPos src, player pl, checkersPos *options, checkersPos *captures); //Added option for player(inserting B OR T).
BOOL isCellFree(Board board, checkersPos soldier);

/*Tests*/

/*Declartions*/
