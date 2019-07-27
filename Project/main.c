#include "PrototypesProject.h"

int main()
{
	// The game board
	Board startingBoard = {
		{' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
		{'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
		{' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
		{' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
		{'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
	};

	Menu(startingBoard);
}
