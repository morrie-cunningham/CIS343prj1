/************************************************************************
 * minesweeper.c														*
 *																		*
 * Author(s): Morrie Cunningham and Devin Brown													*
 ***********************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE_MIN 5
#define BOARD_SIZE_MAX 15
#define PCT_MINES_MIN 10
#define PCT_MINES_MAX 70

typedef struct {
	bool is_mine;
	int mines;
	bool visible;
} Cell;

typedef enum {WON, LOST, INPROGRESS} Status;

/************************************************************************
 * YOU MUST NOT DEFINE ANY GLOBAL VARIABLES (i.e., OUTSIDE FUNCTIONS).  *
 * COMMUNICATION BETWEEN FUNCTIONS MUST HAPPEN ONLY VIA PARAMETERS.     *                           *
 ************************************************************************/

/************************************************************************
 * Function declarations/prototypes										*
 ************************************************************************/
void displayMenu();

int getBoardSize();

int getPercentMines();

void initBoard(int size, Cell board[][size]);

void placeMinesOnBoard(int size, Cell board[][size], int nbrMines);

void fillInMineCountForNonMineCells(int size, Cell board[][size]);

int nbrOfMines(int size, Cell board[][size]);

int getNbrNeighborMines(int row, int col, int size, Cell board[][size]);

void displayBoard(int size, Cell board[][size], bool displayMines);

Status selectCell(int row, int col, int size, Cell board[][size]);

int nbrVisibleCells(int size, Cell board[][size]);

void setImmediateNeighborCellsVisible(int row, int col, int size, Cell board[][size]);

void setAllNeighborCellsVisible(int row, int col, int size, Cell board[][size]);


/************************************************************************
 * Main driver of the program. Uses the functions defined above.		*
 ************************************************************************/
int main()
{
	int row, col, size, nbrMines;
	char command;
	bool displayMines = false;
	Status gameState = INPROGRESS;

	printf("!!!!!WELCOME TO THE MINESWEEPER GAME!!!!!\n\n");
	size = getBoardSize();

	// declare 2D array of cells
	Cell board[size][size];

	initBoard(size,board);

	// determine number of mine to place on the board
	nbrMines = (int) (size * size * (getPercentMines()/100.0));

	// place mines randomly on the board
	placeMinesOnBoard(size,board,nbrMines);

	// For each non-mine cell, sets the neighboring mine count
	fillInMineCountForNonMineCells(size,board);

	displayBoard(size,board,displayMines);

	while (true) {
		printf("Enter command (m/M for command menu): ");
		scanf("%c",&command);
		command = getchar();

		switch (command) {
			case 'm': case 'M':
				displayMenu();
				break;

			case 'c': case 'C':
				do {
					printf("Enter row and column of cell: ");
					scanf("%d%d",&row,&col);
					getchar();
					if (row < 1 || row > size || col < 1 || col > size) {
						printf("Invalid row or column values. Try again.\n");
					}
				} while (row < 1 || row > size || col < 1 || col > size);
				row--;
				col--;
				gameState = selectCell(row,col,size,board);
				displayBoard(size,board,displayMines);
				break;

			case 's': case 'S':
				displayMines = true;
				displayBoard(size,board,displayMines);
				break;

			case 'h': case 'H':
				displayMines = false;
				displayBoard(size,board,displayMines);
				break;

			case 'b': case 'B':
				displayBoard(size,board,displayMines);
				break;

			case 'q': case 'Q':
				printf("Bye.\n");
				return 0;

			default:
				printf("Invalid command. Try again.\n");
		}

		// display appropriate message if the game is over
		if (gameState == WON) {
			printf("You found all the mines. Congratulations. Bye.");
			return 0;
		} else if (gameState == LOST) {
			printf("Oops. Sorry, you landed on a mine. Bye");
			return 0;
		}
	}

	return 0;
}

/************************************************************************
 * Displays list of commands allowed at the prompt						*
 ************************************************************************/
void displayMenu()
{
	printf("List of available commands:\n");
	printf("   Show Mines: s/S\n");
	printf("   Hide Mines: h/H\n");
	printf("   Select Cell: c/C\n");
	printf("   Display Board: b/B\n");
	printf("   Display Menu: m/M\n");
	printf("   Quit: q/Q\n\n");
}

/************************************************************************
 * Initializes the fields of each cell on the board as follows:			*
 * 		is_mine field to false											*
 * 		mines field to 0												*
 * 		visible field to false											*
 ************************************************************************/
void initBoard(int size, Cell board[][size])
{
	int i, j;
	for(i = 0; i <= size; i++) {
		for(j = 0; j <= size; j++) {
			board[i][j].is_mine = false;
			board[i][j].mines = 0;
			board[i][j].visible = false;
		}
	}
}

/************************************************************************
 * Places the specified number of mines randomly on the board			*
 ************************************************************************/
void placeMinesOnBoard(int size, Cell board[][size], int nbrMines)
{
	srand((unsigned)time(NULL));
	int i = 0;
	while (i < nbrMines) {
		int row = rand() % size;
		int col = rand() % size;
		if (!board[row][col].is_mine) {
			board[row][col].is_mine = true;
			i++;
		}
	}
}

/************************************************************************
 * For each non-mine cell on the board, set the "mines" field to the	*
 * number of mines in the immediate neighborhood.						*
 ************************************************************************/
void fillInMineCountForNonMineCells(int size, Cell board[][size])
{
	// TO DO
}

/************************************************************************
 * Counts and returns the number of mines on the board					*
 ************************************************************************/
int nbrOfMines(int size, Cell board[][size])
{
	int count = 0, i, j;

	for(i = 0; i <= size; i++) {
		for(j = 0; j <= size; j++) {
			if (board[i][j].is_mine() == true) {
				count++;
			}
		}
	}

	return count;
}

/************************************************************************
 * Returns the number of mines in the immediate neighborhood of a cell	*
 * at location (row,col) on the board.									*
 ************************************************************************/
int getNbrNeighborMines(int row, int col, int size, Cell board[][size])
{
	int count = 0;

	// TO DO

	return count;
}

/************************************************************************
 * Displays the board. If a cell is not currently visible and has a		*
 * mine, show the mine if the displayMines is true. Used for debugging	*
 * and testing purposes.												*
 ************************************************************************/
void displayBoard(int size, Cell board[][size], bool displayMines)
{
	printf("\n");
	int i, j;
	for(i = 0; i <= size + 1; i++) {
		for(j = 0; j <= size + 1; j++) {
			char *cell;
			if (i == 0){
				if (j == 0 || j == 1){
					cell = " ";
				} else {
					char str[3];
					sprintf(str, "%d", j-1);
					cell = str;
				}
			} else if (i == 1) {
				if (j == 0){
					cell = " ";
				} else if (j == 1){
					cell = "  ┌";
				} else {
					cell = "───";
				}
			} else {
				printf("B");
				if (j == 0){

					char str[3];
					sprintf(str, "%d", i-1);
					cell = str;
				} else if (j == 1) {
					cell = "  │";
				} else {
					if (board[i-2][j-2].visible) {
						if (board[i-2][j-2].is_mine) {
							cell = "*";
						} else {
							char str[3];
							sprintf(str, "%d", board[i-2][j-2].mines);
							cell = str;
						}
					} else {
						if (displayMines && board[i-2][j-2].is_mine) {
							cell = "*";
						} else {
							cell = "?";
						}
					}
				}
			}
			printf("%3s",cell);
			if (j == size + 1) {
				printf("\n");
			}
		}
	}
	printf("\n");
}

/************************************************************************
 * Prompts the user for board size, reads and validates the input		*
 * entered, and returns the integer if it is within valid range.		*
 * repeats this in a loop until the user enters a valid value.			*
 ************************************************************************/
int getBoardSize()
{
	int size = 10;

	while(1) {
		printf("Enter the board size (%d .. %d): ", BOARD_SIZE_MIN, BOARD_SIZE_MAX);
		scanf("%d", &size);

		if(size < BOARD_SIZE_MIN || size > BOARD_SIZE_MAX)
			printf("Please enter an integer between %d and %d!\n", BOARD_SIZE_MIN, BOARD_SIZE_MAX);
		else{
			break;
		}
	}
	return size;
}

/************************************************************************
 * Prompts the user for percentage of mines to place on the board,		*
 * reads and validates the input entered, and returns the integer if it	*
 * is within valid range. repeats this in a loop until the user enters	*
 * a valid value for board size.										*
 ************************************************************************/
int getPercentMines()
{
	int percent = 0;

	while(1) {
		printf("Enter the percentage of mines on the board (%d .. %d): ", PCT_MINES_MIN, PCT_MINES_MAX);
		scanf("%d",&percent);
		if(percent < PCT_MINES_MIN || percent > PCT_MINES_MAX)
			printf("Please enter an integer between %d and %d!\n", PCT_MINES_MIN, PCT_MINES_MAX);
		else{
			break;
		}
	}

	return percent;
}

/************************************************************************
 * Process cell selection by user during the game						*
 ************************************************************************/
Status selectCell(int row, int col, int size, Cell board[][size])
{
	board[row][col].visible = true;
	return INPROGRESS;
}

/************************************************************************
 * Returns the number of cells that are currently visible.				*
 ************************************************************************/
int nbrVisibleCells(int size, Cell board[][size])
{
	int count = 0;

	// TO DO

	return count;
}

/************************************************************************
 * If the mine count of a cell at location (row,col) is zero, then make	*
 * the cells ONLY in the immediate neighborhood visible.				*
 ************************************************************************/
void setImmediateNeighborCellsVisible(int row, int col, int size, Cell board[][size])
{
	// TO DO
}

/************************************************************************
 * If the mine count of a cell at location (row,col) is zero, then make	*
 * the cells in the immediate neighborhood visible and repeat this		*
 * process for each of the cells in this set of cells that have a mine	*
 * count of zero, and so on.											*
 ************************************************************************/
void setAllNeighborCellsVisible(int row, int col, int size, Cell board[][size])
{
	// TO DO
}
