/*
 * fsm_timer.c
 *
 *  Created on: Nov 15, 2023
 *      Author: Admin
 */


#include "fsm_timer.h"

uint8_t mode_timer = 0;
uint8_t toggle_timer = 0;

uint8_t min_timer = 0;
uint8_t hours_timer = 0;

uint8_t flag_colon;

void fsm_colon(){
	if(flag_timer6 == 1){
		if(flag_colon == 0){
			lcd_ShowStr(95, 100, ":", GREEN, BLACK, 24, 1);
			lcd_ShowStr(135, 100, ":", GREEN, BLACK, 24, 1);
			led7_SetDigit(flag_colon, 0, 0);
			flag_colon = 1;
		}
		else if(flag_colon == 1){
			lcd_ShowStr(95, 100, ":", BLACK, BLACK, 24, 1);
			lcd_ShowStr(135, 100, ":", BLACK, BLACK, 24, 1);
			led7_SetDigit(flag_colon, 0, 0);
			flag_colon = 0;
		}
//		lcd_ShowStr(95, 100, ":", GREEN, BLACK, 24, 1);
//		lcd_ShowStr(135, 100, ":", GREEN, BLACK, 24, 1);
//		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
//		flag_colon = flag_colon + 1;
//		led7_SetDigit(flag_colon, 0, 0);
		setTimer6(500);
	}
	led7_SetDigit(flag_timer6, 1, 0);
}

void fsm_timer(){
	switch (mode_timer) {
		case MIN_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				min_timer++;
				ds3231_alarm_min++;
			}
			if(min_timer >= 60){
				min_timer = 0;
			}

			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				min_timer--;
				ds3231_alarm_min--;
				if(ds3231_alarm_min == 0){
					min_timer = 59;
					ds3231_alarm_min = 59;
				}
			}

			if(ds3231_alarm_min >= 60){
				ds3231_alarm_min = 0;
			}

			if(flag_timer4 == 1){
				if(toggle_timer == 1){
					toggle_timer = 0;
					lcd_ShowIntNum(110, 100, ds3231_alarm_min, 2, GREEN, BLACK, 24);
					lcd_ShowIntNum(70, 100, ds3231_alarm_hour, 2, GREEN, BLACK, 24);
				}else{
					lcd_ShowIntNum(110, 100, ds3231_alarm_min, 2, BLACK, BLACK, 24);
					toggle_timer = 1;
				}
				setTimer4(50);
			}
			if(button_count[12] == 1){
				mode_timer = HOUR_MODE;
//				update_Alarm();
			}
			break;
		case HOUR_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				hours_timer++;
				ds3231_alarm_hour++;
			}
			if(hours_timer >= 24){
				hours_timer = 0;
			}

			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				hours_timer--;
				ds3231_alarm_hour--;
				if(ds3231_alarm_hour == 0){
					min_timer = 23;
					ds3231_alarm_hour = 23;
				}
			}

			if(ds3231_alarm_hour < 0){
				min_timer = 23;
				ds3231_alarm_hour = 23;
			}

			if(ds3231_alarm_hour >= 24){
				ds3231_alarm_hour = 0;
			}

			if(flag_timer4 == 1){
				if(toggle_timer == 1){
					toggle_timer = 0;
					lcd_ShowIntNum(110, 100, ds3231_alarm_min, 2, GREEN, BLACK, 24);
					lcd_ShowIntNum(70, 100, ds3231_alarm_hour, 2, GREEN, BLACK, 24);
				}else{
					lcd_ShowIntNum(70, 100, ds3231_alarm_hour, 2, BLACK, BLACK, 24);
					toggle_timer = 1;
				}
				setTimer4(50);
			}
			if(button_count[12] == 1){
				mode_timer = MIN_MODE;
//				update_Alarm();
			}
			break;

		default:
			break;
	}
}
