/*
 * get_time_from_internet.h
 *
 *  Created on: May 31, 2024
 *      Author: Windows
 */

#ifndef INC_GET_TIME_FROM_INTERNET_H_
#define INC_GET_TIME_FROM_INTERNET_H_

#include "ds3231.h"
#include "button.h"
#include "lcd.h"

extern uint8_t flag_get_time;

void update_clock(void);

#endif /* INC_GET_TIME_FROM_INTERNET_H_ */
