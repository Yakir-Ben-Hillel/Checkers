#include "PrototypesProject.h"
#define ALLOCATION_ERROR -1
static BOOL isCellFree(Board board, checkersPos *soldier);
SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src);
void checkAllocation(void *address);
static BOOL isBottom(player p);
checkersPos *soldierStatus(Board board, checkersPos *src, player pl);
// blah blah
checkersPos *soldierStatus(Board board, checkersPos *src, player pl) //Added option for player(inserting B OR T).
{                                                                    //Rows can get input from 'A' to 'H', columns can get input from '1' to '8'.
    checkersPos *options[2];
    options[0] = options[1] = NULL;
    if (pl == 'T')
    {//hello
        if ((src->col != '1') && (src->col != '8') && (src->row != 'H')) //might have steps from both sides.
        {//Test 1:Checking if sides are empty.
            checkersPos *solider;
            solider->col = src->col - 1;
            solider->row = src->row + 1;
            if (isCellFree(board, solider))
            { //Checking left side of 'T' step option.
                options[0] = solider;
            }
            solider->col = src->col + 1;
            if (isCellFree(board, solider))
            { //Checking right side of 'T' step option.
                options[1] = solider;
            }
        }//Unfinished.
        if((src->col>=3)&&(src->col<=6))
        {
            
        }
    }
}
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

    if (isCellFree(board, src))
    {
        *movesTree = FindSingleSourceMovesAux(board, src);
    }
    else
    {
        movesTree = NULL;

        return *movesTree;
    }
}

SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src) // Aux
{
    SingleSourceMovesTree treeOne, treeTwo, baseTree = {0};
    checkersPos *arr;

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
        if (isBottom)
        {
            arr = (checkersPos*)malloc(2 * sizeof(checkersPos));
            arr = soldierStatus(board, src, 'B'); // Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
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

static BOOL isBottom(player p)
{
    if (p == 'B')
        return TRUE;
    else 
        return FALSE;
}

static BOOL isCellFree(Board board, checkersPos *soldier)
{
    if (board[soldier->col][soldier->row] != ' ') // Space marks empty cell
    {
        return TRUE;
    }
    else
        return FALSE;
}
