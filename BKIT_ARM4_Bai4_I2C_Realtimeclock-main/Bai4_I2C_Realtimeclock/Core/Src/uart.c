/*
 * uart.c
 *
 *  Created on: May 31, 2024
 *      Author: Windows
 */
#include "uart.h"


uint8_t msg[100];
uint8_t msg_time[100];

uint8_t receive_buffer1 = 0, receive_buffer2 = 0;
uint8_t check_esp = 0;

uint8_t flag_receive_time = 0;

uint16_t id = 0;

//void uart_init_rs232(){
//	HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
//}
//
//void uart_Rs232SendString(uint8_t* str){
//	HAL_UART_Transmit(&huart1, (void*)msg, sprintf((void*)msg,"%s",str), 10);
//}
//
//void uart_Rs232SendBytes(uint8_t* bytes, uint16_t size){
//	HAL_UART_Transmit(&huart1, bytes, size, 10);
//}

int getDayOfWeek(int day, int month, int year) {
    // Zeller's Congruence algorithm to find the day of the week
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int K = year % 100;
    int J = year / 100;
    int f = day + ((13 * (month + 1)) / 5) + K + (K / 4) + (J / 4) - (2 * J);
    int dayOfWeek = ((f % 7) + 7) % 7 + 1;  // Ensure dayOfWeek is non-negative

    // Mapping dayOfWeek to the name of the day
    return dayOfWeek;
}

void uart_Rs232SendNum(uint32_t num){
	if(num == 0){
		uart_Rs232SendString("0");
		return;
	}
    uint8_t num_flag = 0;
    int i;
	if(num < 0) uart_Rs232SendString("-");
    for(i = 10; i > 0; i--)
    {
        if((num / mypow(10, i-1)) != 0)
        {
            num_flag = 1;
            sprintf((void*)msg,"%d",num/mypow(10, i-1));
            uart_Rs232SendString(msg);
        }
        else
        {
            if(num_flag != 0)
            	uart_Rs232SendString("0");
        }
        num %= mypow(10, i-1);
    }
}

void uart_Rs232SendNumPercent(uint32_t num)
{
	sprintf((void*)msg,"%ld",num/100);
    uart_Rs232SendString(msg);
    uart_Rs232SendString(".");
    sprintf((void*)msg,"%ld",num%100);
    uart_Rs232SendString(msg);
}

void uart_init_esp(){
	HAL_UART_Receive_IT(&huart2, &receive_buffer2, 1);
	HAL_GPIO_WritePin(ESP12_PWR_GPIO_Port, ESP12_PWR_Pin, 1);
}

void uart_EspSendBytes(uint8_t* bytes, uint16_t size){
	HAL_UART_Transmit(&huart2, bytes, size, 10);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	if(huart->Instance == USART1){
//		// rs232 isr
//		// can be modified
//		HAL_UART_Transmit(&huart1, &receive_buffer1, 1, 10);
//
//		// turn on the receive interrupt
//		HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
//	}

	if(huart->Instance == USART2){
//		if(receive_buffer2 == 'O') check_esp = 1;
//		else if(receive_buffer2 == 'a') light_status = 0;
//		else if(receive_buffer2 == 'A') light_status = 1;
		if(receive_buffer2 == 'O'){
			HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
//			lcd_ShowIntNum(10, 200, receive_buffer2, 10, WHITE, BLACK, 24);
			flag_receive_time = 1 - flag_receive_time;
		}
		if(flag_receive_time == 1){
			if(receive_buffer2 == 'K'){
				flag_receive_time = 1 - flag_receive_time;
				id = 0;
//				lcd_ShowStr(0, 200, msg_time, WHITE, BLACK, 24, 0);
//				lcd_ShowChar(0, 270, msg_time[9], WHITE, BLACK, 24, 1);
				uint8_t _sec = msg_time[18] - '0' + (msg_time[17] - '0')*10;
				uint8_t _min = msg_time[15] - '0' + (msg_time[14] - '0')*10;
				uint8_t _hours = msg_time[12] - '0' + (msg_time[11] - '0')*10;
				uint8_t _month = msg_time[6] - '0' + (msg_time[5] - '0')*10;
				uint8_t _year = msg_time[3] - '0' + (msg_time[2] - '0')*10;
				uint8_t _date = msg_time[9] - '0' + (msg_time[8] - '0')*10;

				uint8_t _day = getDayOfWeek(_date, _month, _year);

//				lcd_ShowIntNum(0, 220, _hours, 2, WHITE, BLACK, 24);
				update_Time(_day, _date, _month, _year, _sec, _min, _hours);
//				if(msg[0] == '\0')
//					lcd_ShowStr(0, 200, "Null 0", WHITE, BLACK, 24, 0);
//				if(msg[1] == '\0')
//					lcd_ShowStr(0, 250, "Null 1", WHITE, BLACK, 24, 0);4

			}else{
				if(receive_buffer2 != 'O'){
					msg_time[id++] = receive_buffer2;
				}
			}
		}
		HAL_UART_Receive_IT(&huart2, &receive_buffer2, 1);
	}
}

uint8_t uart_EspCheck(){
	if(check_esp == 1) return 1;
	return 0;
}



