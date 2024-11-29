/*
 * fsm.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Windows
 */
#include "fsm.h"

uint16_t mode = 0;
uint16_t sent = 0;
uint16_t init_sent = 0;
uint8_t temp[100];
uint32_t val = 0;

void fsm_machine(){
	switch (mode) {
		case 0:
			buzzer_SetVolume(0);
			sent = 0;
			if(flag_timer4 == 1){
				val = (int)getWattage();
				uart_Rs232SendString("Wattage : ");
				uart_Rs232SendNum(val);
				uart_Rs232SendString(".");
				uart_Rs232SendNum((int)(getWattage()*100)%100);
				uart_Rs232SendString("\n");
				uart_Rs232SendString("Light : ");
				if(!isLight()){
					uart_Rs232SendString("Strong\n");
				}else{
					uart_Rs232SendString("Weak\n");
				}
				uart_Rs232SendString("Humidity :");
				uart_Rs232SendNum((float)((float)sensor_GetPotentiometer()/4094)*100);
				uart_Rs232SendString("%");
				uart_Rs232SendString("\n");
				uart_Rs232SendString("Temperature : ");
				uart_Rs232SendNum(sensor_GetTemperature());
				uart_Rs232SendString("\n\n");
				setTimer4(1000);
			}
			if(isHumidity()){
				mode = 1;
				setTimer3(1000);
			}else{
				mode = 0;
			}
			break;
		case 1:
			buzzer_SetVolume(50);

			if(!isHumidity())
				mode = 0;
			if(!sent){
				uart_Rs232SendString("Humidity is higher than 70%\n\n");
				sent = 1;
			}
			if(flag_timer3 == 1){
				mode = 2;
				setTimer3(1000);
			}
			break;
		case 2:
			buzzer_SetVolume(0);

			if(!isHumidity())
				mode = 0;

			if (flag_timer3 == 1) {
				mode = 1;
				sent = 0;
				setTimer3(1000);
			}
			break;
		default:
			break;
	}
}


