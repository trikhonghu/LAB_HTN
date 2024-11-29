/*
 * fsm.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Windows
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "software_timer.h"
#include "ex.h"
#include "sensor.h"
#include "buzzer.h"
#include "uart.h"

extern uint16_t mode;
//extern uint8_t count_adc;

void fsm_machine();

#endif /* INC_FSM_H_ */
