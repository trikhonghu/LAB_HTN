/*
 * fsm_mode.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include "fsm_mode.h"

uint8_t mode = 0;
uint8_t toggle_normal = 0;

uint8_t alarm_state;

int is_touch_alarm(){
	if(!touch_IsTouched())
		return 0;
	else{
		lcd_ShowIntNum(20, 220, touch_GetX(), 4, WHITE, BLACK, 24);
		lcd_ShowIntNum(70, 220, touch_GetY(), 4, WHITE, BLACK, 24);
		return (touch_GetX() > 20 && touch_GetX() < 70 && touch_GetY() > 235 && touch_GetY() < 285);
	}
}
//lcd_ShowPicture(20, 235, 50, 50, bell_sign);

void displayTime(){
	lcd_ShowIntNum(70, 100, ds3231_hours, 2, GREEN, BLACK, 24);
//	lcd_ShowStr(95, 100, ":", GREEN, BLACK, 24, 1);
	lcd_ShowIntNum(110, 100, ds3231_min, 2, GREEN, BLACK, 24);
//	lcd_ShowStr(135, 100, ":", GREEN, BLACK, 24, 1);
	lcd_ShowIntNum(150, 100, ds3231_sec, 2, GREEN, BLACK, 24);
//	lcd_ShowIntNum(20, 130, ds3231_day, 2, YELLOW, BLACK, 24);
	lcd_ShowIntNum(70, 130, ds3231_date, 2, YELLOW, BLACK, 24);
	lcd_ShowChar(95, 130, '/', YELLOW, BLACK, 24, 0);
	lcd_ShowIntNum(110, 130, ds3231_month, 2, YELLOW, BLACK, 24);
	lcd_ShowChar(135, 130, '/', YELLOW, BLACK, 24, 0);
	lcd_ShowIntNum(150, 130, ds3231_year, 2, YELLOW, BLACK, 24);
	lcd_ShowStr(25, 130, daysOfWeek[ds3231_day-1], YELLOW, BLACK, 24, 0);
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
			ds3231_ReadTime();
			fsm_colon();
			displayTime();
			update_clock();
//			lcd_StrCenter(0,2,"TIMER_MODE",BLACK,BLACK,16,1);
//			lcd_StrCenter(0,2,"NORMAL_MODE",WHITE,BLUE,16,1);
			if(button_count[15] == 1 || is_touch_alarm()){
				alarm_state = 1-alarm_state;
				if(alarm_state == 1){
					lcd_ShowStr(0, 280, "Alarm ON ", RED, BLACK, 24, 0);
				}else{
					lcd_ShowStr(0, 280, "Alarm OFF", WHITE, BLACK, 24, 0);
				}
			}
			if(ds3231_min == ds3231_alarm_min && ds3231_hours == ds3231_alarm_hour && alarm_state == 1){
				mode = ALARM_MODE;
			}
			led7_SetDigit(alarm_state, 2, 0);

			if(touch_IsTouched()){
				mode = SET_TIME_MODE;
				HAL_GPIO_TogglePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin);
			}

			if(button_count[0] == 1){
				mode = SET_TIME_MODE;
				mode_set_time = MIN_MODE;
//				lcd_StrCenter(0,2,"NORMAL_MODE",BLACK,BLACK,16,1);
				lcd_Clear(BLACK);
				lcd_StrCenter(0,2,"SET_TIME_MODE",WHITE,BLACK,16,0);
			}
			break;
		case ALARM_MODE:
			led7_SetDigit(2, 1, 0);
			ds3231_ReadTime();
			fsm_colon();
			displayTime();
			play_note_in_main(note, dur, sizeof(dur)/4);
			if(ds3231_min != ds3231_alarm_min || button_count[15] == 1){
				mode = NORMAL_MODE;
				alarm_state = 1 - alarm_state;
				stop_buzzer();
				lcd_ShowStr(0, 280, "Alarm OFF", WHITE, BLACK, 24, 0);
			}
			break;
		case SET_TIME_MODE:
			fsm_set_time();
			if(button_count[0] == 1){
				mode = TIMER_MODE;
				mode_timer = MIN_MODE;
//				lcd_StrCenter(0,2,"SET_TIME_MODE",BLACK,BLACK,16,1);
				lcd_Clear(BLACK);
				lcd_StrCenter(0,2,"  TIMER_MODE  ",WHITE,BLACK,16,0);
				update_Alarm();
			}
			break;
		case TIMER_MODE:
			lcd_ShowIntNum(150, 100, ds3231_sec, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(20, 130, ds3231_day, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(70, 130, ds3231_date, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(110, 130, ds3231_month, 2, BLACK, BLACK, 24);
			lcd_ShowIntNum(150, 130, ds3231_year, 2, BLACK, BLACK, 24);
			fsm_timer();
			if(button_count[0] == 1){
				mode = NORMAL_MODE;
				lcd_StrCenter(0,2,"NORMAL_MODE",WHITE,BLACK,16,0);
				lcd_ShowPicture(20, 235, 50, 50, bell_sign);
				if(alarm_state == 1){
					lcd_ShowStr(0, 280, "Alarm ON ", RED, BLACK, 24, 0);
				}else{
					lcd_ShowStr(0, 280, "Alarm OFF", WHITE, BLACK, 24, 0);
				}
				update_Alarm();
			}
			break;
		default:
			break;
	}

}


