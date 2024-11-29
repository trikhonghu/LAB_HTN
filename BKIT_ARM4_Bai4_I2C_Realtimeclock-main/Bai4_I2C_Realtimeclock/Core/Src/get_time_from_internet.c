/*
 * get_time_from_internet.c
 *
 *  Created on: May 31, 2024
 *      Author: Tris
 */

#include "get_time_from_internet.h"

uint8_t flag_get_time = 0;

void update_clock(void){
	if(button_count[13] == 1){
		uart_EspSendBytes("t", 1);
//		lcd_ShowStr(10, 250, "sent", WHITE, BLACK, 24, 0);
	}
}
