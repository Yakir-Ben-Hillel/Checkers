#include "PrototypesProject.h"

MultipleSingleSourceMovesList *FindAllPossiblePlayerMoves(Board board, player player)
{
	int i = 0, j = 0;
	MultipleSingleSourceMovesList *MulSrcMovesLoLst = NULL;
	SingleSourceMovesTree *srcMovestr = NULL;
	checkersPos src = {0};
	SingleSourceMovesList *srcMovesLst = NULL;
	makeEmptyLoList(MulSrcMovesLoLst); // Making an empty list of possible moves lists

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == player) // Player recognized as the desired one
			{						   // Updating source structure
				src.row = i;
				src.col = j;
				// Finding a single source moves tree
				srcMovestr = FindSingleSourceMoves(board, &src);
				// Find the best move in each single source moves tree
				srcMovesLst = FindSingleSourceOptimalMove(srcMovestr);
				// Building a List of best moves for each source
				insertLolNodeToTail(MulSrcMovesLoLst, createLolNode(MulSrcMovesLoLst->head->Single_Source_moves_list, NULL));
			}
		}
	}
	return (MulSrcMovesLoLst); // Returning the
}
