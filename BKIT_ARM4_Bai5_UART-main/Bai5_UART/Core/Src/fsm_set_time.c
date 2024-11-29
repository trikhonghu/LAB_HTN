/*
 * fsm_set_time.c
 *
 *  Created on: Nov 15, 2023
 *      Author: Admin
 */
#include "fsm_set_time.h"
#include "uart.h"
#include "uartRingBuffer.h"
#include "fsm_mode.h"

uint8_t mode_set_time = 0;
uint8_t toggle = 0;
uint8_t send_string = 0;
uint8_t temp =0;
uint8_t check = 0;
uint8_t count_request = 0;
uint8_t flag;

void fsm_set_time(){
	switch (mode_set_time) {
		case MIN_MODE:
			check = 0;
			if(flag == 1){
				rxTail = rxHead;
				flag = 0;
			}
			if(flag_timer6 == 1){
				if(count_request > 2){
					lcd_Clear(BLACK);
					mode = NORMAL_MODE;
					lcd_StrCenter(3,2,"ERROR REQUESTING",RED,BLACK,16,1);
					count_request = 0;
					setTimer7(1000);
				}else{
					uart_Rs232SendString("Request minutes\n");
					count_request++;
					setTimer6(5000);
				}
			}

			if(!send_string){
				//uart_Rs232SendString("UPDATING MINUTE\n");
				send_string = 1;
				lcd_StrCenter(0,2,"UPDATING_MINUTE",WHITE,BLACK,16,1);
			}

				if(rxHead != rxTail){
					dataReceived = 0;
					uint8_t data = rxBuffer[rxTail];
					rxTail = (rxTail + 1)%BUFFER_SIZE;
					uart_Rs232SendNum(data);
					uart_Rs232SendString("sent\n");
					if(data < 47 || data > 57){// * used to end data
						uart_Rs232SendString("syntax, request again");
						check = 1;
						flag = 1;
					}
					if(!check && data != 47){
						temp = temp*10 + (data - 48);
					}else if(data == 47 && !check){
						if(temp >= 60)
							temp = 0;
						ds3231_min = temp;
						ds3231_Write(ADDRESS_MIN, ds3231_min);
						check = 0;
						temp = 0;
						flag = 1;
						count_request = 0;
						lcd_Clear(BLACK);
						mode = NORMAL_MODE;
					}else{
						temp = 0;
					}
				}
				//uart_Rs232SendNum(data);
				//uart_Rs232SendString(" sent\n");

			//uart_Rs232SendNum(ds3231_min);

			if(button_count[3] == 1 || (button_count[3] >= 40 && button_count[3] % 4 == 1)){
				ds3231_min++;
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
				send_string--;
				lcd_Clear(BLACK);
				temp = 0;
			}
			break;
		case HOUR_MODE:

			check = 0;
			if(flag == 1){
				rxTail = rxHead;
				flag = 0;
			}
			if(flag_timer6 == 1){
				if(count_request > 2){
					lcd_Clear(BLACK);
					mode = NORMAL_MODE;
					lcd_StrCenter(3,2,"ERROR REQUESTING",RED,BLACK,16,1);
					count_request = 0;
					setTimer7(1000);
				}else{
					uart_Rs232SendString("Request hour\n");
					count_request++;
					setTimer6(5000);
				}
			}

			if(!send_string){
				//uart_Rs232SendString("UPDATING MINUTE\n");
				send_string = 1;
				lcd_StrCenter(0,2,"UPDATING_HOUR",WHITE,BLACK,16,1);
			}

				if(rxHead != rxTail){
					dataReceived = 0;
					uint8_t data = rxBuffer[rxTail];
					rxTail = (rxTail + 1)%BUFFER_SIZE;
					uart_Rs232SendNum(data);
					uart_Rs232SendString("sent\n");
					if(data < 47 || data > 57){// * used to end data
						uart_Rs232SendString("syntax, request again");
						check = 1;
						flag = 1;
					}
					if(!check && data != 47){
						temp = temp*10 + (data - 48);
					}else if(data == 47 && !check){
						if(temp >= 24)
							temp;
						ds3231_hours = temp;
						ds3231_Write(ADDRESS_HOUR, ds3231_hours);
						check = 0;
						temp = 0;
						flag = 1;
						count_request = 0;
						lcd_Clear(BLACK);
						mode = NORMAL_MODE;
					}else{
						temp = 0;
					}
				}
			if(button_count[3] == 1 || (button_count[3] >= 40 && button_count[3] % 4 == 1)){
				ds3231_hours++;
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
				mode_set_time = DAY_MODE;
				ds3231_Write(ADDRESS_HOUR, ds3231_hours);
				send_string--;
				lcd_Clear(BLACK);
				temp = 0;
			}
			break;
		case DAY_MODE:
			check = 0;
			if(flag == 1){
				rxTail = rxHead;
				flag = 0;
			}
			if(flag_timer6 == 1){
				if(count_request > 2){
					lcd_Clear(BLACK);
					mode = NORMAL_MODE;
					lcd_StrCenter(3,2,"ERROR REQUESTING",RED,BLACK,16,1);
					count_request = 0;
					setTimer7(1000);
				}else{
					uart_Rs232SendString("Request day\n");
					count_request++;
					setTimer6(5000);
				}
			}

			if(!send_string){
				//uart_Rs232SendString("UPDATING MINUTE\n");
				send_string = 1;
				lcd_StrCenter(0,2,"UPDATING_DAY",WHITE,BLACK,16,1);
			}

				if(rxHead != rxTail){
					dataReceived = 0;
					uint8_t data = rxBuffer[rxTail];
					rxTail = (rxTail + 1)%BUFFER_SIZE;
					uart_Rs232SendNum(data);
					uart_Rs232SendString("sent\n");
					if(data < 47 || data > 57){// * used to end data
						uart_Rs232SendString("syntax, request again");
						check = 1;
						flag = 1;
					}
					if(!check && data != 47){
						temp = temp*10 + (data - 48);
					}else if(data == 47 && !check){
						if(temp > 7)
							temp = 1;
						ds3231_day = temp;
						ds3231_Write(ADDRESS_DAY, ds3231_day);
						check = 0;
						temp = 0;
						flag = 1;
						count_request = 0;
						lcd_Clear(BLACK);
						mode = NORMAL_MODE;
					}else{
						temp = 0;
					}
				}
			if(button_count[3] == 1 || (button_count[3] >= 40 && button_count[3] % 4 == 1)){
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
				send_string--;
				lcd_Clear(BLACK);
				temp = 0;
			}
			break;
		case DATE_MODE:

			check = 0;
			if(flag == 1){
				rxTail = rxHead;
				flag = 0;
			}
			if(flag_timer6 == 1){
				if(count_request > 2){
					lcd_Clear(BLACK);
					mode = NORMAL_MODE;
					lcd_StrCenter(3,2,"ERROR REQUESTING",RED,BLACK,16,1);
					count_request = 0;
					setTimer7(1000);
				}else{
					uart_Rs232SendString("Request date\n");
					count_request++;
					setTimer6(5000);
				}
			}

			if(!send_string){
				//uart_Rs232SendString("UPDATING MINUTE\n");
				send_string = 1;
				lcd_StrCenter(0,2,"UPDATING_DATE",WHITE,BLACK,16,1);
			}

				if(rxHead != rxTail){
					dataReceived = 0;
					uint8_t data = rxBuffer[rxTail];
					rxTail = (rxTail + 1)%BUFFER_SIZE;
					uart_Rs232SendNum(data);
					uart_Rs232SendString("sent\n");
					if(data < 47 || data > 57){// * used to end data
						uart_Rs232SendString("syntax, request again");
						check = 1;
						flag = 1;
					}
					if(!check && data != 47){
						temp = temp*10 + (data - 48);
					}else if(data == 47 && !check){
						if(ds3231_month == 1 ||
								ds3231_month == 3 ||
								ds3231_month == 5 ||
								ds3231_month == 7 ||
								ds3231_month == 8 ||
								ds3231_month == 10 ||
								ds3231_month == 12){
							if(temp > 31)
								temp = 1;
						}else if(ds3231_month == 4 ||
								ds3231_month == 6 ||
								ds3231_month == 9 ||
								ds3231_month == 11){
							if(temp > 30)
								temp = 1;
						}else{
							if ((ds3231_year % 4 == 0 && ds3231_year % 100 != 0)
									|| (ds3231_year % 400 == 0)){
								if(temp > 29)
									temp = 1;
							}else{
								if(temp > 28)
									temp = 1;
							}
						}
						ds3231_date = temp;
						ds3231_Write(ADDRESS_DATE, ds3231_date);
						check = 0;
						temp = 0;
						flag = 1;
						count_request = 0;
						lcd_Clear(BLACK);
						mode = NORMAL_MODE;
					}else{
						temp = 0;
					}
				}
			if(button_count[3] == 1 || (button_count[3] >= 40 && button_count[3] % 4 == 1)){
				ds3231_date++;
			}
			if(ds3231_date > 31){
				ds3231_date = 1;
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
				send_string--;
				lcd_Clear(BLACK);
				temp = 0;
				temp = 0;
			}
			break;

		case MONTH_MODE:
			check = 0;
			if(flag == 1){
				rxTail = rxHead;
				flag = 0;
			}
			if(flag_timer6 == 1){
				if(count_request > 2){
					lcd_Clear(BLACK);
					mode = NORMAL_MODE;
					lcd_StrCenter(3,2,"ERROR REQUESTING",RED,BLACK,16,1);
					count_request = 0;
					setTimer7(1000);
				}else{
					uart_Rs232SendString("Request month\n");
					count_request++;
					setTimer6(5000);
				}
			}

			if(!send_string){
				//uart_Rs232SendString("UPDATING MINUTE\n");
				send_string = 1;
				lcd_StrCenter(0,2,"UPDATING_MINUTE",WHITE,BLACK,16,1);
			}

				if(rxHead != rxTail){
					dataReceived = 0;
					uint8_t data = rxBuffer[rxTail];
					rxTail = (rxTail + 1)%BUFFER_SIZE;
					uart_Rs232SendNum(data);
					uart_Rs232SendString("sent\n");
					if(data < 47 || data > 57){// * used to end data
						uart_Rs232SendString("syntax, request again");
						check = 1;
						flag = 1;
					}
					if(!check && data != 47){
						temp = temp*10 + (data - 48);
					}else if(data == 47 && !check){
						ds3231_month = temp;
						if(temp > 12)
							temp = 1;
						ds3231_Write(ADDRESS_MONTH, ds3231_month);
						check = 0;
						temp = 0;
						flag = 1;
						count_request = 0;
						lcd_Clear(BLACK);
						mode = NORMAL_MODE;
					}else{
						temp = 0;
					}
				}
			if(button_count[3] == 1 || (button_count[3] >= 40 && button_count[3] % 4 == 1)){
				ds3231_month++;
			}
			if(ds3231_month >= 13){
				ds3231_month = 1;
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
				send_string--;
				lcd_Clear(BLACK);
				temp = 0;
			}
			break;
		case YEAR_MODE:
			check = 0;
			if(flag == 1){
				rxTail = rxHead;
				flag = 0;
			}
			if(flag_timer6 == 1){
				if(count_request > 2){
					lcd_Clear(BLACK);
					mode = NORMAL_MODE;
					lcd_StrCenter(3,2,"ERROR REQUESTING",RED,BLACK,16,1);
					count_request = 0;
					setTimer7(1000);
				}else{
					uart_Rs232SendString("Request year\n");
					count_request++;
					setTimer6(5000);
				}
			}

			if(!send_string){
				//uart_Rs232SendString("UPDATING MINUTE\n");
				send_string = 1;
				lcd_StrCenter(0,2,"UPDATING_YEAR",WHITE,BLACK,16,1);
			}

				if(rxHead != rxTail){
					dataReceived = 0;
					uint8_t data = rxBuffer[rxTail];
					rxTail = (rxTail + 1)%BUFFER_SIZE;
					uart_Rs232SendNum(data);
					uart_Rs232SendString("sent\n");
					if(data < 47 || data > 57){// * used to end data
						uart_Rs232SendString("syntax, request again");
						check = 1;
						flag = 1;
					}
					if(!check && data != 47){
						temp = temp*10 + (data - 48);
					}else if(data == 47 && !check){
						ds3231_year = temp;
						ds3231_Write(ADDRESS_YEAR, ds3231_year);
						check = 0;
						temp = 0;
						flag = 1;
						count_request = 0;
						lcd_Clear(BLACK);
						mode = NORMAL_MODE;
					}else{
						temp = 0;
					}
				}
			if(button_count[3] == 1 || (button_count[3] >= 40 && button_count[3] % 4 == 1)){
				ds3231_year++;
			}

			if(button_count[7] == 1 || (button_count[7] >= 40 && button_count[7] % 4 == 1)){
				ds3231_year--;
			}

			if(ds3231_year < 0) ds3231_year = 0;

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
				send_string--;
				lcd_Clear(BLACK);
				temp = 0;
			}
			break;
		default:
			break;
	}
}
