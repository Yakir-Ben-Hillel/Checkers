#include "PrototypesProject.h"
static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list);
void Turn(Board board, player player)
{
    unsigned short bestPlaceInList;
    MultipleSingleSourceMovesList *mul_list;
    MultipleSourceMovesListCell *ptr;
    SingleSourceMovesListCell *lst_ptr;
    mul_list = FindAllPossiblePlayerMoves(board, player);
    ptr = mul_list->head;
    bestPlaceInList = findPlaceofBestTurn(mul_list);
    for (unsigned short i = 1; i <= bestPlaceInList; i++)
    {
        ptr = ptr->next;
    }
    lst_ptr = ptr->Single_Source_moves_list->head;
    while (lst_ptr->next != NULL)
    {
        checkersPos capture;
        capture.row = ((lst_ptr->position->row) + (lst_ptr->next->position->row)) / 2;//Captured row position.
        capture.col = ((lst_ptr->position->col) + (lst_ptr->next->position->col)) / 2;//captured col position.
        board[lst_ptr->position->row - 'A'][lst_ptr->position->col - '0' - 1] = ' '; // Removing the player from its last position
        board[capture.row - 'A'][capture.col - '0' - 1] = ' '; //Changing the captured into empty space.
        board[lst_ptr->next->position->row - 'A'][lst_ptr->next->position->col - '0' - 1] = player; //inserting player to next move.
        lst_ptr = lst_ptr->next;
    }
    freeLoList(mul_list);
}

static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list)
{
    MultipleSourceMovesListCell *ptr;
    unsigned short max = 0;
    unsigned short counter = 0;
    unsigned short place = 0;
    ptr = mul_list->head;
    while (ptr != NULL)
    {
        if (ptr->Single_Source_moves_list->tail->captures > max)
        {
            max = ptr->Single_Source_moves_list->tail->captures;
            place = counter;
        }
        ptr = ptr->next;
        counter++;
    }
    return place;
}
