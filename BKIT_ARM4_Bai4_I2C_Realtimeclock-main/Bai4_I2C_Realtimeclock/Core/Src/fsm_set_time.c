/*
 * fsm_set_time.c
 *
 *  Created on: Nov 15, 2023
 *      Author: Admin
 */
#include "fsm_set_time.h"

uint8_t mode_set_time = 0;
uint8_t toggle = 0;

int is_leap_year(int year){
	if((year % 4 ==0 && year % 100 !=0) || year%400 == 0)
		return 1;
	return 0;
}

void fsm_set_time(){
	switch (mode_set_time) {
		case MIN_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				ds3231_min++;
			}
			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				ds3231_min--;
				if(ds3231_min == 0)
					ds3231_min = 59;
			}
			if(ds3231_min >= 60){
				ds3231_min = 0;
			}

			if(flag_timer3 == 1){
				if(toggle == 1){
					toggle = 0;
					displayTime();
				}else{
					lcd_ShowIntNum(110, 100, ds3231_min, 2, BLACK, BLACK, 24);
					toggle = 1;
				}
				setTimer3(50);
			}
			if(button_count[12] == 1){
				mode_set_time = HOUR_MODE;
				ds3231_Write(ADDRESS_MIN, ds3231_min);
			}
			break;
		case HOUR_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				ds3231_hours++;
			}
			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				ds3231_hours--;
				if(ds3231_hours == 0)
					ds3231_hours = 23;
			}
			if(ds3231_hours >= 24){
				ds3231_hours = 0;
			}

			if(flag_timer3 == 1){
				if(toggle == 1){
					toggle = 0;
					displayTime();
				}else{
					lcd_ShowIntNum(70, 100, ds3231_hours, 2, BLACK, BLACK, 24);
					toggle = 1;
				}
				setTimer3(50);
			}
			if(button_count[12] == 1){
				mode_set_time = DATE_MODE;
				ds3231_Write(ADDRESS_HOUR, ds3231_hours);
			}
			break;
		case DAY_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				ds3231_day++;
			}
			if(ds3231_day > 7){
				ds3231_day = 1;
			}

			if(flag_timer3 == 1){
				if(toggle == 1){
					toggle = 0;
					displayTime();
				}else{
					lcd_ShowIntNum(20, 130, ds3231_day, 2, BLACK, BLACK, 24);
					toggle = 1;
				}
				setTimer3(50);
			}
			if(button_count[12] == 1){
				mode_set_time = DATE_MODE;
				ds3231_Write(ADDRESS_DAY, ds3231_day);
			}
			break;
		case DATE_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				ds3231_date++;
			}
			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				ds3231_date--;
			}
			if(ds3231_month == 2){
				if(is_leap_year(ds3231_year) == 1){
					if(ds3231_date > 29)
						ds3231_date = 1;
					if(ds3231_date == 0)
						ds3231_date = 29;
				}else{
					if(ds3231_date > 28)
						ds3231_date = 1;
					if(ds3231_date == 0)
						ds3231_date = 28;
				}

			}else if(ds3231_month == 1 ||
					ds3231_month == 3 ||
					ds3231_month == 5 ||
					ds3231_month == 7 ||
					ds3231_month == 8 ||
					ds3231_month == 10 ||
				ds3231_month == 12){
				if(ds3231_date > 31){
					ds3231_date = 1;
				}
				if(ds3231_date == 0)
					ds3231_date = 31;
			}else{
				if(ds3231_date > 30)
					ds3231_date = 1;
				if(ds3231_date == 0)
					ds3231_date = 30;
			}

			if(flag_timer3 == 1){
				if(toggle == 1){
					toggle = 0;
					displayTime();
				}else{
					lcd_ShowIntNum(70, 130, ds3231_date, 2, BLACK, BLACK, 24);
					toggle = 1;
				}
				setTimer3(50);
			}
			if(button_count[12] == 1){
				mode_set_time = MONTH_MODE;
				ds3231_Write(ADDRESS_DATE, ds3231_date);
				ds3231_day = getDayOfWeek(ds3231_date, ds3231_month, ds3231_year);
				ds3231_Write(ADDRESS_DAY, ds3231_day);
			}
			break;

		case MONTH_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				ds3231_month++;
			}
			if(ds3231_month >= 13){
				ds3231_month = 1;
			}

			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				ds3231_month--;
				if(ds3231_month == 0)
					ds3231_month = 12;
			}

			if(flag_timer3 == 1){
				if(toggle == 1){
					toggle = 0;
					displayTime();
				}else{
					lcd_ShowIntNum(110, 130, ds3231_month, 2, BLACK, BLACK, 24);
					toggle = 1;
				}
				setTimer3(50);
			}
			if(button_count[12] == 1){
				mode_set_time = YEAR_MODE;
				ds3231_Write(ADDRESS_MONTH, ds3231_month);
				ds3231_day = getDayOfWeek(ds3231_date, ds3231_month, ds3231_year);
				ds3231_Write(ADDRESS_DAY, ds3231_day);
			}
			break;
		case YEAR_MODE:
			if(button_count[3] == 1 || button_count[3] >= 40 && button_count[3] % 4 == 1){
				ds3231_year++;
			}

			if(ds3231_year > 99)
				ds3231_year = 0;

			if(button_count[7] == 1 || button_count[7] >= 40 && button_count[7] % 4 == 1){
				ds3231_year = (ds3231_year + 99)%100;
			}

			if(flag_timer3 == 1){
				if(toggle == 1){
					toggle = 0;
					displayTime();
				}else{
					lcd_ShowIntNum(150, 130, ds3231_year, 2, BLACK, BLACK, 24);
					toggle = 1;
				}
				setTimer3(50);
			}
			if(button_count[12] == 1){
				mode_set_time = MIN_MODE;
				ds3231_Write(ADDRESS_YEAR, ds3231_year);
				ds3231_day = getDayOfWeek(ds3231_date, ds3231_month, ds3231_year);
				ds3231_Write(ADDRESS_DAY, ds3231_day);
			}
			break;
		default:
			break;
	}
}
