/*
 * fsm_timer.h
 *
 *  Created on: Nov 15, 2023
 *      Author: Admin
 */

#ifndef INC_FSM_TIMER_H_
#define INC_FSM_TIMER_H_

#include "main.h"
#include "ds3231.h"
#include "lcd.h"
#include "software_timer.h"
#include "button.h"


#define MIN_MODE	11
#define HOUR_MODE	12

extern uint8_t mode_timer;


extern uint8_t min_timer;
extern uint8_t hours_timer;

void fsm_timer();

#endif /* INC_FSM_TIMER_H_ */
