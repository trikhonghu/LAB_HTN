/*
 * fsm_mode.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include "fsm_mode.h"

uint8_t mode = 0;
uint8_t toggle_normal = 0;

void displayTime(){
	lcd_ShowIntNum(70, 100, ds3231_hours, 2, GREEN, BLACK, 24);
	lcd_ShowIntNum(110, 100, ds3231_min, 2, GREEN, BLACK, 24);
	lcd_ShowIntNum(150, 100, ds3231_sec, 2, GREEN, BLACK, 24);
	lcd_ShowIntNum(20, 130, ds3231_day, 2, YELLOW, BLACK, 24);
	lcd_ShowIntNum(70, 130, ds3231_date, 2, YELLOW, BLACK, 24);
	lcd_ShowIntNum(110, 130, ds3231_month, 2, YELLOW, BLACK, 24);
	lcd_ShowIntNum(150, 130, ds3231_year, 2, YELLOW, BLACK, 24);
}

void off_all(){
	lcd_ShowIntNum(70, 100, ds3231_hours, 2, BLACK, BLACK, 24);
	lcd_ShowIntNum(110, 100, ds3231_min, 2, BLACK, BLACK, 24);
	lcd_ShowIntNum(150, 100, ds3231_sec, 2, BLACK, BLACK, 24);
	lcd_ShowIntNum(20, 130, ds3231_day, 2, BLACK, BLACK, 24);
	lcd_ShowIntNum(70, 130, ds3231_date, 2, BLACK, BLACK, 24);
	lcd_ShowIntNum(110, 130, ds3231_month, 2, BLACK, BLACK, 24);
	lcd_ShowIntNum(150, 130, ds3231_year, 2, BLACK, BLACK, 24);
}

void fsm_machine_mode(){
	switch (mode) {
		case NORMAL_MODE:
			if(flag_timer7 == 1){
				lcd_StrCenter(3,2,"ERROR REQUESTING",BLACK,BLACK,16,1);
				ds3231_ReadTime();
				displayTime();
				lcd_StrCenter(0,2,"TIMER_MODE",BLACK,BLACK,16,1);
				lcd_StrCenter(0,2,"NORMAL_MODE",WHITE,BLUE,16,1);
				if(ds3231_min == min_timer && ds3231_hours == hours_timer && ds3231_sec <10){
					if(flag_timer5 == 1){
						if(toggle_normal == 1){
							toggle_normal = 0;
							displayTime();
						}else{
							off_all();
							toggle_normal = 1;
						}
						setTimer5(50);
					}
				}
			}
			if(button_count[0] == 1){
				mode = SET_TIME_MODE;
				mode_set_time = MIN_MODE;
				send_string = 0;
				lcd_Clear(BLACK);
			}
			break;
		case SET_TIME_MODE:
			fsm_set_time();
			//lcd_StrCenter(0,2,"NORMAL_MODE",BLACK,BLACK,16,1);
			//lcd_StrCenter(0,2,"SET_TIME_MODE",WHITE,BLUE,16,1);
			if(button_count[0] == 1){
				mode = TIMER_MODE;
				mode_timer = MIN_MODE;
				send_string = 0;
				lcd_Clear(BLACK);
			}
			break;
		case TIMER_MODE:
			if(!send_string){
				uart_Rs232SendString("Set alarm\n");
				send_string = 1;
			}
			lcd_ShowIntNum(150, 100, ds3231_sec, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(20, 130, ds3231_day, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(70, 130, ds3231_date, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(110, 130, ds3231_month, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(150, 130, ds3231_year, 2, BLACK, BLACK, 24);
			fsm_timer();
			lcd_StrCenter(0,2,"SET_TIME_MODE",BLACK,BLACK,16,1);
			lcd_StrCenter(0,2,"TIMER_MODE",WHITE,BLUE,16,1);
			if(button_count[0] == 1){
				mode = NORMAL_MODE;
				send_string = 0;
				lcd_Clear(BLACK);
			}
			break;
		default:
			break;
	}

}


