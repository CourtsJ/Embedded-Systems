/*	
	File:   message.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   11 Oct 2016
	Descr:  

*/


#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "uint8toa.h"

//globals used for message functions
#define PACER_RATE 1000
#define MESSAGE_RATE 20
#define LOOP_RATE PACER_RATE

//initialises text for start and end message
void text_init(void){
	tinygl_init (LOOP_RATE);
	tinygl_font_set(&font3x5_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	pacer_init (PACER_RATE);
}

//re-initialises for points screen
void text_nonscroll_init(void){
	tinygl_font_set(&font5x7_1);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
}

//re-initialises for results screen
void text_scroll_init(void){
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

//message before game start		
void start_message(void) {
    tinygl_text ("PRESS BUTTON TO BEGIN");
}


//description
void points_message(uint8_t my_score) {
	char score_text[4];
	uint8toa(my_score, score_text, 0);
    tinygl_text(score_text);
}

//message for results screen
void results_message(char result) {
	if (result=='W') {
		tinygl_text("WINNER");
	} 
	else if (result=='L')
	{
		tinygl_text("LOSER");
	}
	else if (result == 'D'){
		tinygl_text("DRAW");
	}
}

//called to display given message
void display_message(void) {
	pacer_wait();
	tinygl_update();
}
