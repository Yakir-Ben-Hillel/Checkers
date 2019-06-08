#include "PrototypesProject.h"
static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list);
void Turn(Board board, player player)
{
    unsigned short bestPlaceInList;
    MultipleSingleSourceMovesList *mul_list;
    mul_list = FindAllPossiblePlayerMoves(board, player);
    bestPlaceInList=findPlaceofBestTurn(mul_list);
}


static unsigned short findPlaceofBestTurn(MultipleSingleSourceMovesList *mul_list)
{
    MultipleSourceMovesListCell *ptr;
    unsigned short max = 0;
    unsigned short counter = 0;
    ptr = mul_list->head;
    while (ptr != NULL)
    {
        if (ptr->Single_Source_moves_list->tail->captures > max)
        {
            max = ptr->Single_Source_moves_list->tail->captures;
        }
        ptr=ptr->next;
        counter++;
    }
    return counter;
}
//Just Started to write it down.