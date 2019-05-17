#include "PrototypesProject.h"
//Static Declartions
static BOOL isCellFree(Board board, checkersPos *soldier);
static SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src);
static BOOL isBottom(player p);
static void testsForT(Board board, checkersPos *src, checkersPos **options);
static checkersPos *testsForTLeft(Board board, checkersPos *src);
static checkersPos *testsForTRight(Board board, checkersPos *src);
static void testsforB(Board board, checkersPos *src, checkersPos **options);
static checkersPos *testsForBLeft(Board board, checkersPos *src);
static checkersPos *testsForBRight(Board board, checkersPos *src);
static checkersPos *soldierStatus(Board board, checkersPos *src, player pl);
//Static Declartions
static checkersPos *testsForTLeft(Board board, checkersPos *src)
{
    checkersPos *solider;
    if ((src->col != '1') && (src->col != '8') && (src->row != 'H')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        solider->col = src->col - 1;
        solider->row = src->row + 1;
        if (isCellFree(board, solider))
        { //Checking left side of 'T' step option.
            return solider;
        }
        else if ((src->col >= 3) && (src->col <= 6) && (src->row <= 'F'))
        { //TEST 2: checks if the solider can eat an enemy solider.
            solider = src;
            solider->row = solider->row + 1;
            solider->col = solider->col - 1;
            if ((!isCellFree(board, solider) && (board[solider->row][solider->col] == 'B')))
            { //Checks if the variable of the left is an enemy.
                solider->row = solider->row + 1;
                solider->col = solider->col - 1;
                if (isCellFree(board, solider))
                { //if the next step on the right is free jump over the enemy("eat it").
                    return solider;
                }
            }
        }
    }
    solider = NULL;
    return solider;
}
static checkersPos *testsForTRight(Board board, checkersPos *src)
{
    checkersPos *solider;
    if ((src->col != '1') && (src->col != '8') && (src->row != 'H')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        solider->row = src->row + 1;
        solider->col = src->col + 1;
        if (isCellFree(board, solider))
        { //Checking right side of 'T' step option.
            return solider;
        }
        else if ((src->col >= 3) && (src->col <= 6) && (src->row <= 'F'))
        { //TEST 2: checks if the solider can eat an enemy solider.
            solider = src;
            solider->row = src->row + 1;
            solider->col = src->col + 1;
            if ((!isCellFree(board, solider) && (board[solider->row][solider->col] == 'B')))
            { //Checks if the variable of the right is an enemy.
                solider->row = solider->row + 1;
                solider->col = solider->col + 1;
                if (isCellFree(board, solider))
                {
                    return solider;
                }
            }
        }
    }
    solider = NULL;
    return solider;
}
static void testsForT(Board board, checkersPos *src, checkersPos **options)
{
    options[0] = testsForTLeft(board, src);
    options[1] = testsForTRight(board, src);
}

static checkersPos *testsForBLeft(Board board, checkersPos *src)
{
    checkersPos *solider;
    if ((src->col != '1') && (src->col != '8') && (src->row != 'A')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        solider->col = src->col - 1;
        solider->row = src->row - 1;
        if (isCellFree(board, solider))
        { //Checking left side of 'T' step option.
            return solider;
        }

        else if ((src->col >= 3) && (src->col <= 6) && (src->row <= 'C'))
        { //TEST 2: checks if the solider can eat an enemy solider.
            solider = src;
            solider->row = solider->row - 1;
            solider->col = solider->col - 1;
            if ((!isCellFree(board, solider) && (board[solider->row][solider->col] == 'T')))
            { //Checks if the variable of the left is an enemy.
                solider->row = solider->row - 1;
                solider->col = solider->col - 1;
                if (isCellFree(board, solider))
                { //if the next step on the right is free jump over the enemy("eat it").
                    return solider;
                }
            }
        }
    }
    solider = NULL;
    return solider;
}
static checkersPos *testsForBRight(Board board, checkersPos *src)
{
    checkersPos *solider;
    if ((src->col != '1') && (src->col != '8') && (src->row != 'A')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        solider->col = src->col + 1;
        solider->row = src->row - 1;
        if (isCellFree(board, solider))
        { //Checking left side of 'T' step option.
            return solider;
        }

        else if ((src->col >= 3) && (src->col <= 6) && (src->row <= 'C'))
        { //TEST 2: checks if the solider can eat an enemy solider.
            solider = src;
            solider->row = solider->row - 1;
            solider->col = solider->col + 1;
            if ((!isCellFree(board, solider) && (board[solider->row][solider->col] == 'T')))
            { //Checks if the variable of the left is an enemy.
                solider->row = solider->row - 1;
                solider->col = solider->col + 1;
                if (isCellFree(board, solider))
                { //if the next step on the right is free jump over the enemy("eat it").
                    return solider;
                }
            }
        }
    }
    solider = NULL;
    return solider;
}
static void testsForR(Board board, checkersPos *src, checkersPos **options)
{
    options[0] = testsForRLeft(board, src);
    options[1] = testsForRight(board, src);
}

static checkersPos *soldierStatus(Board board, checkersPos *src, player pl) //Added option for player(inserting B OR T).
{                                                                           //Rows can get input from 'A' to 'H', columns can get input from '1' to '8'.
    checkersPos *options[2];
    checkersPos *solider;
    options[0] = options[1] = NULL;
    if (pl == 'T')
    {
        testsForT(board, src, options);
    }
    else
    {
        testsforB(board,src,options);
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
            arr = (checkersPos *)malloc(2 * sizeof(checkersPos));
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
    free(arr);
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
