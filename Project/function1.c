#include "PrototypesProject.h"
// Public  Prototypes
void checkAllocation(void *address);

// function1 Prototypes
static void soldierStatus(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures);
// return in the options array the nearest possible coordinates for moving and in accordance the place of an eaten soldier if exists
SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl); // Auxiliary function for building the tree moves

static BOOL isCellFree(Board board, checkersPos *soldier);
//static BOOL isBottom(player p);

// Tests- Static Prototypes
static void testsForT(Board board, checkersPos *src, checkersPos *options, checkersPos *captures);
static void testsForB(Board board, checkersPos *src, checkersPos *options, checkersPos *captures);
static void testsForTLeft(Board board, checkersPos *src, checkersPos *options, checkersPos *captures);
static void testsForTRight(Board board, checkersPos *src, checkersPos *options, checkersPos *captures);
static void testsForBLeft(Board board, checkersPos *src, checkersPos *options, checkersPos *captures);
static void testsForBRight(Board board, checkersPos *src, checkersPos *options, checkersPos *captures);

static void initializePlayer(Board board, checkersPos *src, player *currentPlayer); // Initializing the player based on the given coordinate
static void initializeBoardOfPlayer(Board board, Board *boardOfPlayer);             // Initializing the board of a given coordinate
static void handleBoardChange(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures);
// Update the board based on possible near moves and captions
static BOOL isThereACapture(checkersPos *options, checkersPos *captures, int *ind); // Determines whether there's an option of move with a
                                                                                    // capture between the given captures, if exist
                                                                                    // Return true in case there's a match between a capture and
static void fillOptions(checkersPos *soldier, checkersPos *options);
static void fillCaptures(checkersPos *soldier, checkersPos *captures);

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
    SingleSourceMovesTree *movesTree = NULL;
    player currentPlayer;

    if (!isCellFree(board, src)) // In case the cell is taken
    {
        initializePlayer(board, src, &currentPlayer);
        *movesTree = FindSingleSourceMovesAux(board, src, currentPlayer);
    }

    return (movesTree); // Returns the tree moves or a NULL in case the cell is free
}

static void initializePlayer(Board board, checkersPos *src, player *currentPlayer)
{
    *(currentPlayer) = board[src->row - 'A'][src->col - '0' - 1]; // Initializing the player found in the given coordinate
}

SingleSourceMovesTree FindSingleSourceMovesAux(Board board, checkersPos *src, player pl)
{
    // Initialized due to security reasons
    SingleSourceMovesTree treeOne = {NULL}, treeTwo = {NULL}, baseTree = {NULL};
    checkersPos *options = NULL, *captures = NULL;

    // Allocating a node
    baseTree.source = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
    checkAllocation(baseTree.source);                                  // Checking whether the memory allocation succeeded or not
    baseTree.source->pos = (checkersPos *)malloc(sizeof(checkersPos)); // Allocating pointer to position struct (checkersPos)
    checkAllocation(baseTree.source->pos);
    baseTree.source->pos = src;                                       // Updating the position of the current node

    if (baseTree.source == NULL)
    {
        return baseTree;
    }
    else
    { // Allocating 2 arrays for the near moves / captures
        options = (checkersPos *)calloc(2, sizeof(checkersPos));
        checkAllocation(options);
        captures = (checkersPos *)calloc(2, sizeof(checkersPos));
        checkAllocation(captures);

        initializeBoardOfPlayer(board, &baseTree.source->board); // Initializing board of the current root
        soldierStatus(board, src, pl, options, captures);        // Returns an array of 2 possible moves- index 0 to the left, index 1 to the right
        handleBoardChange(board, src, pl, options, captures);    // Handles change due to next move update in the the tree

        treeOne = FindSingleSourceMovesAux(board, &options[0], pl);
        treeTwo = FindSingleSourceMovesAux(board, &options[1], pl);

        // Free the arrays allocated at start
        free(options);
        free(captures);

        // Compliment case - Connecting sub - Trees to the base Tree
        baseTree.source->next_move[0] = treeOne.source;
        baseTree.source->next_move[1] = treeOne.source;
        return (baseTree);
    }
}
static void initializeBoardOfPlayer(Board board, Board *boardOfPlayer)
{
    int i = 0, j = 0;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            (*boardOfPlayer)[i][j] = board[i][j];
        }
    }
}

static void handleBoardChange(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures)
{
    int Ind = -1; // Index for the array of captures, Initialized in case there's a matched capture

    if (isThereACapture(options, captures, &Ind))
    {
        board[src->row - 'A'][src->col - '0' - 1] = ' ';                   // Removing the player from its last position
        board[options[0].row - 'A'][options[0].col - '0' - 1] = pl;        // Moving the player to the place given in options array
        board[captures[Ind].row - 'A'][captures[Ind].col - '0' - 1] = ' '; // Removing the captured player from board
    }
    else // No capture - updating the table by moving the player and deleting its last location
    {
        board[src->row - 'A'][src->col - '0' - 1] = ' '; // Removing the player from its last position
        board[options[0].row - 'A'][options[0].col - '0' - 1] = pl;
    }
}

static BOOL isThereACapture(checkersPos *options, checkersPos *captures, int *ind)
{
    // Check for the first potential capture                                                                                // Checks wether one of the captions matches the move option
    if ((captures[0].col != '0') && (captures[0].row != '0'))
    {                                                                                                 // In case its a valid coordinate
        if (abs(captures[0].col - options[0].col) == 1 && abs(captures[0].col - options[0].col) == 1) // The distance between the column coordinate and the row's coordinate is one- (diagonal- marks a capture)
        {
            *ind = 0; // Updating the index of the capture
            return TRUE;
        }
    }
    // Check for the second potential capture
    if ((captures[1].col != '0') && (captures[1].row != '0'))
    {
        if (abs(captures[1].col - options[1].col) == 1 && abs(captures[1].col - options[1].col) == 1) // The distance between the column coordinate and the row's coordinate is one- (diagonal- marks a capture)
        {
            *ind = 1; // Updating the index of the capture
            return TRUE;
        }
    }
    // In any other case
    return FALSE;
}

static void soldierStatus(Board board, checkersPos *src, player pl, checkersPos *options, checkersPos *captures) //Added option for player(inserting B OR T).
{                                                                                                                //Rows can get input from 'A' to 'H', columns can get input from '1' to '8'.
                                                                                                                 // you can't initialize a struct type with NULL, that's why
                                                                                                                 // when you added the extra asterisk it worked- because the elements
                                                                                                                 // in the array became pointers, and than its legit to initialize with NULL
    if (pl == 'T')                                                                                               // In case 'T' is the player
    {
        testsForT(board, src, options, captures);
    }
    else // In case 'B' is the player
    {
        testsForB(board, src, options, captures);
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

// static BOOL isBottom(player p)
// {
//     if (p == 'B')
//         return TRUE;
//     else
//         return FALSE;
// }

static BOOL isCellFree(Board board, checkersPos *soldier)
{                                                   // converting the characters from an ASCII values to decimal numbers (indexes)
    if ((soldier->row == 0) && (soldier->col == 0)) // Not an initialized coordinate
        return TRUE;
    else if (board[(int)soldier->row - 'A'][(int)soldier->col - '0' - 1] != ' ') // Space marks empty cell
    {
        return FALSE; // The cell is not free
    }
    else // In any other case
        return TRUE;
}

//**********************************files separation - tests********************************************//

static void testsForTLeft(Board board, checkersPos *src, checkersPos *options, checkersPos *captures)
{
    checkersPos *soldier - NULL;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);
    if ((src->col != '1') && (src->col != '8') && (src->row != 'H')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        soldier->col = src->col - 1;
        soldier->row = src->row + 1;
        if (isCellFree(board, soldier))
        { //Checking left side of 'T' step option.
            fillOptions(soldier, options);
        }
        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'F'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            soldier = src;
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
static void testsForTRight(Board board, checkersPos *src, checkersPos *options, checkersPos *captures)
{
    checkersPos *soldier = NULL;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);

    if ((src->col != '1') && (src->col != '8') && (src->row != 'H')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        soldier->row = src->row + 1;
        soldier->col = src->col + 1;
        if (isCellFree(board, soldier))
        { //Checking right side of 'T' step option.
            fillOptions(soldier, options);
        }
        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'F'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            soldier = src;
            soldier->row = src->row + 1;
            soldier->col = src->col + 1;
            if ((!isCellFree(board, soldier) && (board[(int)soldier->row - 'A'][soldier->col - '0' - 1] == 'B')))
            { //Checks if the variable of the right is an enemy.
                fillCaptures(soldier, options);
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
static void testsForB(Board board, checkersPos *src, checkersPos *options, checkersPos *captures)
{
    testsForBLeft(board, src, options, captures);
    testsForBRight(board, src, options, captures);
}
static void testsForT(Board board, checkersPos *src, checkersPos *options, checkersPos *captures)
{
    testsForTLeft(board, src, options, captures);
    testsForTRight(board, src, options, captures);
}

static void testsForBLeft(Board board, checkersPos *src, checkersPos *options, checkersPos *captures)
{
    checkersPos *soldier;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);

    if ((src->col != '1') && (src->col != '8') && (src->row != 'A')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        soldier->col = src->col - 1;
        soldier->row = src->row - 1;
        if (isCellFree(board, soldier))
        { //Checking left side of 'T' step option.
            fillOptions(soldier, options);
        }

        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'C'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            soldier = src;
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
static void testsForBRight(Board board, checkersPos *src, checkersPos *options, checkersPos *captures)
{

    checkersPos *soldier;
    soldier = (checkersPos *)malloc(sizeof(checkersPos));
    checkAllocation(soldier);

    if ((src->col != '1') && (src->col != '8') && (src->row != 'A')) //might have steps from both sides.
    {                                                                //Test 1:Checking if sides are empty.
        soldier->col = src->col + 1;
        soldier->row = src->row - 1;
        if (isCellFree(board, soldier))
        { //Checking left side of 'T' step option.
            fillOptions(soldier, options);
        }

        else if ((src->col >= '3') && (src->col <= '6') && (src->row <= 'C'))
        { //TEST 2: checks if the soldier can eat an enemy soldier.
            soldier = src;
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

static void fillOptions(checkersPos *soldier, checkersPos *options)
{                                                   // Remember to initialize options array and captures array with '0' in each cell of the arrays
    if (options[0].col == 0 && options[0].row == 0) // first cell is empty
    {
        options[0].col = soldier->col;
        options[0].row = soldier->row;
    }
    else if (options[1].col == 0 && options[1].row == 0) // second cell is empty
    {
        options[1].col = soldier->col;
        options[1].row = soldier->row;
    }
    return; // in case both cells are taken
}
static void fillCaptures(checkersPos *soldier, checkersPos *captures)
{                                                     // Remember to initialize options array and captures array with '0' in each cell of the arrays
    if (captures[0].col == 0 && captures[0].row == 0) // first cell is empty
    {
        captures[0].col = soldier->col;
        captures[0].row = soldier->row;
    }
    else if (captures[1].col == 0 && captures[1].row == 0) // second cell is empty
    {
        captures[1].col = captures->col;
        captures[1].row = captures->row;
    }
    return; // in case both cells are taken
}
