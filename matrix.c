/*	
	File:   matrix.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  functions that create, maintain and update the matrix
*/

#include "system.h"
#include "pio.h"
#include "struct.h"
#include "traffic.h"
#include "pacer.h"

//global varibles used for matrix functions
#define COL_NO 5
#define ROW_NO 7

//initialises matrix
int LED_Board[COL_NO][ROW_NO] =
    { {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };

//global varibles that assist with updating matrix 
int cur_col = 0;
int cur_row = 0;
int prev_col = 4;
int prev_row = 6;

//Sets all rows to low (off)
static const pio_t row_Array[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

//Sets all columns to low (off)
static const pio_t col_Array[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

// A function that draws the cars onto the matrix.
void draw_cars(Vehicle* cars)
{
	int i;
	for (i = 0; i < MAX_VEHICLES; ++i) {
		if (cars[i].length == 1) {
			LED_Board[cars[i].current.col][cars[i].current.row] = 2; // turn car->current on (need 2 as froggy is set to one)
		} else if (cars[i].length == 2) {
			LED_Board[cars[i].current.col][cars[i].current.row] = 2; // turn car->current on (need 2 as froggy is set to one)
			LED_Board[cars[i].current.col + (cars[i].current.row == CENTER_LANE ? 1 : -1)][cars[i].current.row] = 2; // turn back of car on
		}
	}
}

// A function that configures the matrix
void maxtrix_config(void)
{
    int col = 0;
    int row = 0;
    for (col = 0; col < LEDMAT_COLS_NUM; col++) {
        pio_config_set(col_Array[col], PIO_OUTPUT_HIGH);
    }
    for (row = 0; row < LEDMAT_ROWS_NUM; row++) {
        pio_config_set(row_Array[row], PIO_OUTPUT_HIGH);
    }
}

// displays froggy and traffic on the LED board 
void matrix_display(GameState* game)
{
    int current_column = 0;
    int current_row = 0;
	for (current_column = 0; current_column < COL_NO; ++current_column) { // clear the frame
		for (current_row = 0; current_row < ROW_NO; ++current_row) {
			LED_Board[current_column][current_row] = 0;
		}
	}
	draw_cars(game->vehicles);
	LED_Board[game->frog.current.col][game->frog.current.row] = 1; // draw frog
    for (current_column = 0; current_column < COL_NO; current_column++) {
        for (current_row = 0; current_row < ROW_NO; current_row++) {
            if (LED_Board[current_column][current_row] >= 1) {  // If it's froggy(1) or traffic(2)
				pio_output_low(col_Array[current_column]); // turn on the column
                pio_output_low(row_Array[current_row]); // turn on any rows that need to be on
            } else {
                pio_output_high(row_Array[current_row]); // turn off any rows that should be off
                
            }
        }
        pacer_wait();
        pio_output_high(col_Array[current_column]); // turn off the column
    }
}

//Updates the players position based on the nav switch
void move_frog(Player* frog, char direction)
{
    if (direction == 'S') {
        if (frog->current.row != 6) {   
            frog->previous.row = frog->current.row;
            frog->current.row++;
        }
    }

    if (direction == 'N') {
        if (frog->current.row != 0) {
            frog->previous.row = frog->current.row;
            frog->current.row--;
        }
    }

    if (direction == 'E') {
        if (frog->current.col != 4) {   
            frog->previous.col = frog->current.col;
            frog->current.col++;
        }
    }

    if (direction == 'W') {
        if (frog->current.col != 0) {
            frog->previous.col = frog->current.col;
            frog->current.col--;
        }
    }

}
