/*
 * ex.c
 *
 *  Created on: Nov 26, 2023
 *      Author: Windows
 */

#include "ex.h"

float getWattage(){
	return sensor_GetVoltage() * sensor_GetCurrent();
}

uint16_t isLight(){
	if((float)sensor_GetLight()/4095 > 0.5)
		return 1;
	return 0;
}

uint16_t isHumidity(){
	if((float)sensor_GetPotentiometer()/4094 > 0.7)
		return 1;
	return 0;
}
