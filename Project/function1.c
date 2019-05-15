#include "PrototypesProject.h"
#define ALLOCATION_ERROR -1
static BOOL isCellTaken(Board board, checkersPos *soldier);
SingleSourceMovesTree *FindSingleSourceMovesAux(Board board, checkersPos *src);
void checkAllocation(void *address);
static BOOL isUP(player p);
checkersPos* soldierStatus(Board board, checkersPos* src); 

void checkAllocation(void *address)
{
    if (!address)
    {
        fprintf(stderr, "Memory Allocation Error!\n");
        exit(ALLOCATION_ERROR);
    }
}

SingleSourceMovesTree FindSingleSourceMoves(Board board, checkersPos *src)
{
    SingleSourceMovesTree *movesTree;

    if (isCellTaken(board, src))
    {
        *movesTree = FindSingleSourceMovesAux(board, src);
    }
    else
        return NULL;
}

SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src) // Au
{
    SingleSourceMovesTree treeOne, treeTwo, baseTree = {0};

    // Allocating a node
    baseTree.source = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
    checkAllocation(baseTree.source); // Checking whether the memory allocation succeeded or not
                                      // To update the pointer to soldier
    if (baseTree.source == NULL)
    {
        return baseTree;
    }
    else
    {
        if (isUP)
        {  
            checkersPos arr[2] = soldierStatus(board, src); // Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
            treeOne = FindSingleSourceMovesAux(board, src);
            treeTwo = FindSingleSourceMovesAux(board, src);
        }
        else
        {
            treeOne = FindSingleSourceMovesAux(board, src);
            treeTwo = FindSingleSourceMovesAux(board, src);
        }
    }
}

static BOOL isUP(player p)
{
    if (p == 'B')
        return TRUE;
    else
        return FALSE;
}

static BOOL isCellTaken(Board board, checkersPos *soldier)
{
    if (board[soldier->col][soldier->row] != ' ') // Space marks empty cell
    {
        return TRUE;
    }
    else
        return FALSE;
}
