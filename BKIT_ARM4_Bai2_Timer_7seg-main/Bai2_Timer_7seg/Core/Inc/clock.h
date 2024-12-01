/*
 * clock.h
 *
 *  Created on: Nov 29, 2024
 *      Author: Windows
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include "main.h"
#include "led_7seg.h"

extern uint8_t hour;
extern uint8_t min;
extern uint8_t second;
extern uint8_t buffer[4];

void clock_fsm(void);
void blink_colon(void);

#endif /* INC_CLOCK_H_ */
