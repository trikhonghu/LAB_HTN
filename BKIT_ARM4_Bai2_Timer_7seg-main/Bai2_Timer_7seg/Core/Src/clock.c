/*
 * clock.c
 *
 *  Created on: Nov 29, 2024
 *      Author: Windows
 */

#include "clock.h"

uint8_t hour = 12;
uint8_t min = 30;
uint8_t second = 0;

uint8_t state_colon = 0;
uint8_t buffer[4] = {1, 2, 3, 0};

void clock_fsm(){
	second =  (second + 1)%60;
	if(second == 0){
		min = (min + 1)%60;
		if(min == 0){
			hour = (hour + 1)%60;
			buffer[0] = hour/10;
			buffer[1] = hour%10;
			buffer[2] = min/10;
			buffer[3] = min%10;
		}
	}
}

void blink_colon(){
	if(state_colon == 0){
		state_colon = 1;
	}else{
		state_colon = 0;
	}
	led7_SetColon(state_colon);
}
