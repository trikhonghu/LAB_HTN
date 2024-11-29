/*
 * fsm.c
 *
 *  Created on: Nov 16, 2023
 *      Author: DELL
 */

#include "fsm.h"


uint8_t col_mode = 0; // 1: RED, 2: YELLOW, 3: GREEN
uint16_t period = 0;


void blink_light(uint8_t col_mode){
	if (blink_state == 0){
		left_light(0);
		right_light(0);
		if(flag_timer5 == 1){
			blink_state = 1;
			left_light(0);
			right_light(0);
			setTimer5(500);
		}
	}
	else if (blink_state == 1){
		if (col_mode == 1){
			left_light(1);
			right_light(1);
		}
		else if (col_mode == 3){
			left_light(3);
			right_light(3);
		}
		else if (col_mode == 2){
			left_light(2);
			right_light(2);
		}

		if (flag_timer5 == 1){
			blink_state = 0;
			setTimer5(500);
			left_light(0);
			right_light(0);
		}
	}
}

void show_frequency(uint16_t period){
	lcd_ShowStr(10, 270, "Period: ", BLUE, WHITE, 16, 1);
	lcd_ShowIntNum(70, 270, period, 8, BRED, WHITE, 16);
}

void traffic_lights_operation(){
	if (mode == 1){
		traffic_lights();
	}
	else if (mode == 2){
		// RED
		temp_count[1] = 0;
		temp_count[2] = 0;
		if(temp_count[0] == 0)
			temp_count[0] =count_red;
		blink_light(1);
		if (button_count[1] == 1) {
			temp_count[0] = temp_count[0] + 1000;
		}
		show_frequency(temp_count[0]);
		if (button_count[2] == 1){
			if (temp_count[0] > 99000 || temp_count[0] < (count_green + count_yellow)) {
				temp_count[0] = count_red;
				lcd_ShowStr(10, 290, "Can't change RED's period.", BLUE, WHITE, 16, 1);
			}
			count_red = temp_count[0];
		}
	}
	else if (mode == 3){
		// GREEN
		temp_count[0] = 0;
		temp_count[2] = 0;
		if(temp_count[1] == 0)
			temp_count[1] =count_green;
		blink_light(3);
		if (button_count[1] == 1) {
			temp_count[1] = temp_count[1] + 1000;
		}
		show_frequency(temp_count[1]);
		if (button_count[2] == 1){
			if (temp_count[1] > 99000 || count_red < (temp_count[1] + count_yellow)) {
				temp_count[1] = 1000;
				lcd_ShowStr(10, 290, "Can't change GREEN's period.", BLUE, WHITE, 16, 1);
			}
			count_green = temp_count;
		}
	}
	else if (mode == 4){
		// YELLOW
		temp_count[1] = 0;
		temp_count[0] = 0;
		if(temp_count[2] == 0)
			temp_count[2] =count_yellow;
		blink_light(2);
		if (button_count[1] == 1) {
			temp_count[2] = temp_count[2] + 1000;
		}
		show_frequency(temp_count[2]);
		if (button_count[2] == 1){
			if (temp_count[2] > 99000 || count_red < (count_green + temp_count[2])) {
				temp_count[2] = 1000;
				lcd_ShowStr(10, 290, "Can't change YELLOW's period.", BLUE, WHITE, 16, 1);
			}
			count_yellow = temp_count[2];
		}
	}
}



