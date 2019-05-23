#include "PrototypesProject.h"
/*Prototypes*/
static void testsForT(Board board, checkersPos* src, checkersPos *options, checkersPos *captures);
static void testsForB(Board board, checkersPos* src, checkersPos *options, checkersPos *captures);
static void testsForTLeft(Board board, checkersPos* src, checkersPos *options, checkersPos *captures);
static void testsForTRight(Board board, checkersPos* src, checkersPos *options, checkersPos *captures);
static void testsForBLeft(Board board, checkersPos* src, checkersPos *options, checkersPos *captures);
static void testsForBRight(Board board, checkersPos* src, checkersPos *options, checkersPos *captures);
/*Prototypes*/

void soldierStatus(Board board, checkersPos* src, player pl, checkersPos *options, checkersPos *captures) //Added option for player(inserting B OR T).
{																												//Rows can get input from 'A' to 'H', columns can get input from '1' to '8'.
																												// you can't initialize a struct type with NULL, that's why
																												// when you added the extra asterisk it worked- because the elements
																												// in the array became pointers, and than its legit to initialize with NULL
	if (pl == 'T')																								// In case 'T' is the player
	{
		testsForT(board, src, options, captures);
	}
	else // In case 'B' is the player
	{
		testsForB(board, src, options, captures);
	}
}

static void testsForTLeft(Board board, checkersPos* src, checkersPos *options, checkersPos *captures)
{
    checkersPos *soldier = NULL;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);
    if ((src->col != '1') && (src->row != 'H')) //might have steps from both sides.
    {                                         //Test 1:Checking if sides are empty.
        soldier->col = src->col - 1;
        soldier->row = src->row + 1;
        if (isCellFree(board, soldier))
        { //Checking left side of 'T' step option.
            fillOptions(soldier, options);
        }
        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'F'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            *soldier = *src;
            soldier->row = soldier->row + 1;
            soldier->col = soldier->col - 1;
            if ((!isCellFree(board, soldier) && (board[(int)(soldier->row) - 'A'][soldier->col - '0' - 1] == 'B')))
            { //Checks if the variable of the left is an enemy.
                fillCaptures(soldier, captures);
                soldier->row = soldier->row + 1;
                soldier->col = soldier->col - 1;
                if (isCellFree(board, soldier))
                { //if the next step on the right is free jump over the enemy("eat it").
                    fillOptions(soldier, options);
                }
            }
        }
    }
}
static void testsForTRight(Board board, checkersPos* src, checkersPos *options, checkersPos *captures)
{
    checkersPos *soldier = NULL;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);

    if ((src->col != '8') && (src->row != 'H')) //might have steps from both sides.
    {                                         //Test 1:Checking if sides are empty.
        soldier->row = src->row + 1;
        soldier->col = src->col + 1;
        if (isCellFree(board, soldier))
        { //Checking right side of 'T' step option.
            fillOptions(soldier, options);
        }
        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'F'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            *soldier = *src;
            soldier->row = src->row + 1;
            soldier->col = src->col + 1;
            if ((!isCellFree(board, soldier) && (board[(int)soldier->row - 'A'][soldier->col - '0' - 1] == 'B')))
            { //Checks if the variable of the right is an enemy.
                fillCaptures(soldier, captures);
                soldier->row = soldier->row + 1;
                soldier->col = soldier->col + 1;
                if (isCellFree(board, soldier))
                {
                    fillOptions(soldier, options);
                }
            }
        }
    }
}
static void testsForB(Board board, checkersPos* src, checkersPos *options, checkersPos *captures)
{
    testsForBLeft(board, src, options, captures);
    testsForBRight(board, src, options, captures);
}
static void testsForT(Board board, checkersPos* src, checkersPos *options, checkersPos *captures)
{
    testsForTLeft(board, src, options, captures);
    testsForTRight(board, src, options, captures);
}

static void testsForBLeft(Board board, checkersPos* src, checkersPos *options, checkersPos *captures)
{
    checkersPos *soldier = NULL;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);

    if ((src->col != '1') && (src->row != 'A')) //might have steps from both sides.
    {                                         //Test 1:Checking if sides are empty.
        soldier->col = src->col - 1;
        soldier->row = src->row - 1;
        if (isCellFree(board, soldier))
        { //Checking left side of 'T' step option.
            fillOptions(soldier, options);
        }

        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'C'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            *soldier = *src;
            soldier->row = soldier->row - 1;
            soldier->col = soldier->col - 1;
            if ((!isCellFree(board, soldier) && (board[(int)(soldier->row - 'A')][soldier->col - '0' - 1] == 'T')))
            { //Checks if the variable of the left is an enemy.
                fillCaptures(soldier, captures);
                soldier->row = soldier->row - 1;
                soldier->col = soldier->col - 1;
                if (isCellFree(board, soldier))
                { //if the next step on the right is free jump over the enemy("eat it").
                    fillOptions(soldier, options);
                }
            }
        }
    }
}
static void testsForBRight(Board board, checkersPos* src, checkersPos *options, checkersPos *captures)
{

    checkersPos *soldier = NULL;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);

    if ((src->col != '8') && (src->row != 'A')) //might have steps from both sides.
    {                                         //Test 1:Checking if sides are empty.
        soldier->col = src->col + 1;
        soldier->row = src->row - 1;
        if (isCellFree(board, soldier))
        { //Checking left side of 'T' step option.
            fillOptions(soldier, options);
        }

        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'C'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            *soldier = *src;
            soldier->row = soldier->row - 1;
            soldier->col = soldier->col + 1;
            if ((!isCellFree(board, soldier) && (board[(int)soldier->row - 'A'][soldier->col - '0' - 1] == 'T')))
            { //Checks if the variable of the left is an enemy.
                fillCaptures(soldier, captures);
                soldier->row = soldier->row - 1;
                soldier->col = soldier->col + 1;
                if (isCellFree(board, soldier))
                { //if the next step on the right is free jump over the enemy("eat it").
                    fillOptions(soldier, options);
                }
            }
        }
    }
}

BOOL isCellFree(Board board, checkersPos* soldier)
{ // converting the characters from an ASCII values to decimal numbers (indexes)
	if ((soldier->row == 0) && (soldier->col == 0))
		return TRUE;
	else if (board[(int)soldier->row - 'A'][(int)soldier->col - '0' - 1] != ' ') // Space marks empty cell
	{
		return FALSE; // The cell is not free
	}
	else // In any other case
		return TRUE;
}
