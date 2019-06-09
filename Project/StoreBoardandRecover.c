#include "PrototypesProject.h"
// Save the current board into a binary file
#define FILE_OPERATION_ERROR -1
#define NUM_OF_BYTES_TO_SAVE  (BOARD_SIZE*BOARD_SIZE) * (2) / (SIZE_OF_A_BYTE)  // Each position will 'weigh' 2 bits
#define MASK_LSB_EMPTY 0X00 // 0000 0000
#define MASK_LSB_T 0X0001	//0000 0000 0000 0001 
#define MASK_LSB_B 0X0002 // 0000 0000 0000 0010
#define MASK_MOVE_2_LSB_TO_2_MSB(TYPE)  ( (TYPE) << ( (2 * SIZE_OF_A_BYTE) - 2) )
#define MASK_MOVES_2_LEFT(TYPE)  ( (TYPE) << (2) )
#define NUM_OF_BITS_ROW		(SIZE_OF_A_BYTE * (2))

void intializeLsbMask(unsigned char positionContent, unsigned char *MaskAdress, int countCouplesOfBits); // Initialize the couple bits (LSB) of the mask based on the position's content
static void saveArrToFile(char * filename, unsigned  char* zeroMasksArr, int numOfByteInd); // Saves the content of board to a binary file from an array of initialized bytes
unsigned char getCharBy2Bit(unsigned short int secluded_2_LSB); // Returns the right content of position based on coding of the saving process of the board to a binary file


void StoreBoard(Board board, char *filename)
{
	int i = 0, j = 0;
	unsigned char* zeroMasksArr = (unsigned char*)calloc(NUM_OF_BYTES_TO_SAVE, sizeof(unsigned char)); // Setting each byte to zeroswith calloc
	checkAllocation(zeroMasksArr);
	int numOfByteInd = 0, countCouplesOfBits = 0; // Counting the couples of bits that has been 'read' to the array, and in accordance the number of bytes in total
	
	for (i = 0; i < BOARD_SIZE; i++) // Scanning the rows
	{
		for (j = 0; j < BOARD_SIZE; j++) // Scanning the columns 
		{
			intializeLsbMask(board[i][j], zeroMasksArr + numOfByteInd, countCouplesOfBits); // Initialize array of bytes
			countCouplesOfBits += 2; // Counts a couple of bits 
			if (countCouplesOfBits == SIZE_OF_A_BYTE) // Updating the number of bytes that has been converted already
			{
				countCouplesOfBits = 0; // Initialized to zero every other byte
				numOfByteInd++;
			}
		}
	}
	saveArrToFile(filename, zeroMasksArr, numOfByteInd);
}
static void saveArrToFile(char * filename, unsigned  char* zeroMasksArr, int numOfByteInd)
{
	FILE * fpi = fopen(filename, "wb"); // Open a binary file for writing 
	checkFileOperation(fpi);
	int i = 0;
	for (i = 0; i < numOfByteInd; i++)
		fwrite(&zeroMasksArr[i], sizeof(unsigned char), 1, fpi);
	fclose(fpi);
}
void intializeLsbMask(unsigned char positionContent, unsigned char *MaskAdress, int countCouplesOfBits)
{
	// There's a need to move the couple of bits after initializing -
	// excluding the move of bits in the forth initialization of the mask in each byte
	switch (positionContent)
	{
		case'B': // Bottom player
		{
			if (countCouplesOfBits < SIZE_OF_A_BYTE - 2)
			{
				(*MaskAdress) |= MASK_LSB_B;
				*MaskAdress = MASK_MOVES_2_LEFT((*MaskAdress)); // Moving 2 bits to the left
			}
			else
				(*MaskAdress) |= MASK_LSB_B;
			break;
		}
		case'T': // Top player
		{
			if (countCouplesOfBits < SIZE_OF_A_BYTE - 2)
			{
				(*MaskAdress) |= MASK_LSB_T;
				*MaskAdress = MASK_MOVES_2_LEFT((*MaskAdress)); // Moving 2 bits to the left
			}
			else
				(*MaskAdress) |= MASK_LSB_T;
			break;

		}
		case ' ':// In case of an empty position 
		{
			if (countCouplesOfBits < SIZE_OF_A_BYTE -2)
			{
				(*MaskAdress) |= MASK_LSB_EMPTY; // For readiness causes
				*MaskAdress = MASK_MOVES_2_LEFT((*MaskAdress)); // Moving 2 bits to the left
			}
			else
				(*MaskAdress) |= MASK_LSB_EMPTY; // For readiness causes
			break;
		}
	}
}
void checkFileOperation(FILE* fpi)
{
	if (!fpi)
	{
		fprintf(stderr, "File operation error!\n");
		exit(FILE_OPERATION_ERROR);
	}
}
void LoadBoard(char* fileName, Board board)
{
	FILE* fpi = fopen(fileName, "rb"); // Opening the binary file for reading and constructing the board
	checkFileOperation(fpi);
	unsigned char positionMaskFirst = 0x00, positionMaskSecond = 0x00; // seclude_mask- 1100 0000 - unsigned to prevent 1's while moving to the right
	int numOfByte = 0;
	unsigned short int rowMaskPosition=0x0000 , seclude2_MSB_Mask = 0xC000; // 0000 0000 0000 0000 , 1100 0000 0000 0000 
	int i = 0, j = 0, move = 0;
	for (i = 0; i < BOARD_SIZE; i++) // Scanning the rows
	{
		for (j = 0; j < BOARD_SIZE; j++) // Scanning the columns 
		{
  			if ( ( (i==0) && (j==0) ) || (move == NUM_OF_BITS_ROW) )  // 2 * size of a byte meaning 2 bits for each position
			{
				move = 0; // Updating the number of bytes that need to be moved to zero
				// Read two halves of the row
				fread(&positionMaskFirst, sizeof(unsigned char), 1, fpi);
				fread(&positionMaskSecond, sizeof(unsigned char), 1, fpi);
				
				rowMaskPosition = (unsigned short int)positionMaskFirst;
				// Moving to the left 8 bits of the row mask
				rowMaskPosition = rowMaskPosition << SIZE_OF_A_BYTE;
				rowMaskPosition |= (unsigned short int)positionMaskSecond;

				board[i][j] = getCharBy2Bit(seclude2_MSB_Mask & (rowMaskPosition << move)); // Initialize the position in board
			}
			else if (move < NUM_OF_BITS_ROW) 
			{
				board[i][j] = getCharBy2Bit(seclude2_MSB_Mask & (rowMaskPosition << move)); // Initialize the position in board
			}
			move += 2; // Updating bits to move
		}
	}

	fclose(fpi); // Closing the file while done to be used
}
unsigned char getCharBy2Bit(unsigned short int secluded_2_LSB)
{
	switch (secluded_2_LSB)
	{
	case MASK_MOVE_2_LSB_TO_2_MSB(MASK_LSB_B):

		return 'B';
		break;
	case MASK_MOVE_2_LSB_TO_2_MSB(MASK_LSB_T):

		return 'T';
		break;
	case MASK_MOVE_2_LSB_TO_2_MSB(MASK_LSB_EMPTY): // Readiness causes

		return ' ';
		break;
	}
	return ' '; // due to warnings - will not reach to this point- design by contract
}

