/*
 * fsm_mode1.c
 *
 *  Created on: Nov 16, 2023
 *      Author: DELL
 */

#include "fsm_traffic.h"

void draw_filled_retangle(uint16_t x, uint16_t y_start){
	lcd_Fill(x - 35, y_start - 35, x + 35, y_start + 175, BLACK);
}

void off_state(uint16_t x, uint16_t y_start){
	lcd_DrawCircle(x, y_start, GRAY, 30, 1);
	lcd_DrawCircle(x, y_start + 70, GRAY, 30, 1);
	lcd_DrawCircle(x, y_start + 140, GRAY, 30, 1);
}
void red_state(uint16_t x, uint16_t y_start){
	lcd_DrawCircle(x, y_start, RED, 30, 1);
	lcd_DrawCircle(x, y_start + 70, GRAY, 30, 1);
	lcd_DrawCircle(x, y_start + 140, GRAY, 30, 1);
}
void yellow_state(uint16_t x, uint16_t y_start){
	lcd_DrawCircle(x, y_start, GRAY, 30, 1);
	lcd_DrawCircle(x, y_start + 70, YELLOW, 30, 1);
	lcd_DrawCircle(x, y_start + 140, GRAY, 30, 1);
}
void green_state(uint16_t x, uint16_t y_start){
	lcd_DrawCircle(x, y_start, GRAY, 30, 1);
	lcd_DrawCircle(x, y_start + 70, GRAY, 30, 1);
	lcd_DrawCircle(x, y_start + 140, GREEN, 30, 1);
}
void left_light(uint8_t col_code){
	if (col_code == 0){
		off_state(60, 90);
	}
	else if (col_code == 1){
		red_state(60, 90);
	}
	else if (col_code == 2){
		yellow_state(60, 90);
	}
	else if (col_code == 3){
		green_state(60, 90);
	}
}
void right_light(uint8_t col_code){
	if(col_code == 0){
		off_state(180, 90);
	}
	else if (col_code == 1){
		red_state(180, 90);
	}
	else if (col_code == 2){
		yellow_state(180, 90);
	}
	else if (col_code == 3){
		green_state(180, 90);
	}
}

void left_light_mode1(){
	if (status0 == 0){
		left_light(0);
		status0 = 1;
		setTimer3(count_red);
	}
	else if (status0 == 1){
		left_light(1);
		if (flag_timer3 == 1){
			status0 = 3;
			setTimer3(count_green);
		}
	}
	else if (status0 == 2){
		left_light(2);
		if (flag_timer3 == 1){
			status0 = 1;
			setTimer3(count_red);
		}
	}
	else if (status0 == 3){
		left_light(3);
		if (flag_timer3 == 1){
			status0 = 2;
			setTimer3(count_yellow);
		}
	}
}
void right_light_mode1(){
	if (status1 == 0){
		right_light(0);
		status1 = 3;
		setTimer4(count_green);
	}
	else if (status1 == 1){
		right_light(1);
		if (flag_timer4 == 1){
			status1 = 3;
			setTimer4(count_green);
		}
	}
	else if (status1 == 2){
		right_light(2);
		if (flag_timer4 == 1){
			status1 = 1;
			setTimer4(count_red);
		}
	}
	else if (status1 == 3){
		right_light(3);
		if (flag_timer4 == 1){
			status1 = 2;
			setTimer4(count_yellow);
		}
	}
}

void traffic_lights(){
	left_light_mode1();
	right_light_mode1();
}

