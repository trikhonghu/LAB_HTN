/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "software_timer.h"

#include "tim.h"
#include "led_7seg.h"

extern uint16_t flag_timer2;
extern uint16_t flag_timer3;
extern uint16_t flag_timer4;
extern uint16_t flag_timer5;

void timer_init();
void setTimer2(uint16_t duration);
void setTimer3(uint16_t duration);
void setTimer4(uint16_t duration);
void setTimer5(uint16_t duration);

#endif /* INC_SOFTWARE_TIMER_H_ */
