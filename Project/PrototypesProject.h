#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 8

#define TRUE 1
#define FALSE 0
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
    unsigned short total_captures_so_far;            //מספר הדילוגים עד כה
    struct _SingleSourceMovesTreeNode *next_move[2]; //יעדי התנועה
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
    SingleSourceMovesTreeNode *source;
} SingleSourceMovesTree;

/*Declartions*/
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
/*Declartions*/