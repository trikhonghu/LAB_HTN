/*
 * fsm_timer.c
 *
 *  Created on: Nov 15, 2023
 *      Author: Admin
 */


#include "fsm_timer.h"
#include "uart.h"

uint8_t mode_timer = 0;
uint8_t toggle_timer = 0;

uint8_t min_timer = 0;
uint8_t hours_timer = 0;


void fsm_timer(){
	switch (mode_timer) {
		case MIN_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				min_timer++;
			}
			if(min_timer >= 60){
				min_timer = 0;
			}

			if(flag_timer4 == 1){
				if(toggle_timer == 1){
					toggle_timer = 0;
					lcd_ShowIntNum(110, 100, min_timer, 2, GREEN, BLACK, 24);
					lcd_ShowIntNum(70, 100, hours_timer, 2, GREEN, BLACK, 24);
				}else{
					lcd_ShowIntNum(110, 100, min_timer, 2, BLACK, BLACK, 24);
					toggle_timer = 1;
				}
				setTimer4(50);
			}
			if(button_count[12] == 1){
				mode_timer = HOUR_MODE;
			}
			break;
		case HOUR_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				hours_timer++;
			}
			if(hours_timer >= 12){
				hours_timer = 0;
			}

			if(flag_timer4 == 1){
				if(toggle_timer == 1){
					toggle_timer = 0;
					lcd_ShowIntNum(110, 100, min_timer, 2, GREEN, BLACK, 24);
					lcd_ShowIntNum(70, 100, hours_timer, 2, GREEN, BLACK, 24);
				}else{
					lcd_ShowIntNum(70, 100, hours_timer, 2, BLACK, BLACK, 24);
					toggle_timer = 1;
				}
				setTimer4(50);
			}
			if(button_count[12] == 1){
				mode_timer = MIN_MODE;
			}
			break;

		default:
			break;
	}
}
