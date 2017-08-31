/*	
	File:   main.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr: Calls functions that run the game
*/

#include "system.h"
#include "matrix.h"
#include "navigation.h"
#include "message.h"
#include "timer.h"
#include "traffic.h"
#include "player.h"
#include "game.h"
#include "time.h"
#include "global.h"
#include "ir_uart.h"


int main(void)
{
	//calls the initialisation functions
    system_init();
    navigation_init();
    text_init();
    ir_uart_init();
    char direction = 'U'; 
    char screen = 'S'; 
    char result;
    

	//calls functions in relation to the starting message (before game begins)
    start_message();
    while (direction != 'P') {
        display_message();
        navigation_update();
        direction = get_movement();
    }
	
	//calls the rest of initialisation functions
    maxtrix_config();
  	GameState game;
  	init_game(&game);

	//Runs the game for the length given in global.h
  	Timer time;
  	init_time(&time, GAME_LENGTH);
  	while (time.ms > 0) {
    		run_game(&game);
    		if (ir_uart_read_ready_p()) {
				game.op_score = ir_uart_getc();
			}
    		time_diff(&time);
  	}
  	
  	//IR for results
	ir_uart_putc(game.my_score);
  	while (game.op_score==255) {
		if (ir_uart_read_ready_p()) {
			game.op_score = ir_uart_getc();
		}
	}
	
	//Calls function to calculated winner/loser or draw
	result = game_result(game.op_score, game.my_score);
	
	//initialisation for after game messages (points and result)
	text_nonscroll_init();
	points_message(game.my_score);
	
	//calls functions in relation to changing after game messages (points and result)
	while (1) {
		display_message();
        navigation_update();
        direction = get_movement();
		if (direction == 'P') {
			if (screen == 'S') {
				text_scroll_init();
				results_message(result);
				screen = 'R'; 
			}
			else if (screen == 'R') {
				text_nonscroll_init();
				points_message(game.my_score);
				screen = 'S'; 
			}
		}
	}
  	return 0;
}
