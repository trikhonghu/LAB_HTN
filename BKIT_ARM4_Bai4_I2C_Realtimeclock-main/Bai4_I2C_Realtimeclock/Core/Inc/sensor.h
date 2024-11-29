/*
 * sénor.h
 *
 *  Created on: Jun 1, 2024
 *      Author: Windows
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "adc.h"

void sensor_init();

void sensor_Read();

uint16_t sensor_GetLight();

uint16_t sensor_GetPotentiometer();

float sensor_GetVoltage();

float sensor_GetCurrent();

float sensor_GetTemperature();

#endif /* INC_SENSOR_H_ */
