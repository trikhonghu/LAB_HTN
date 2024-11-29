/*
 * fsm.h
 *
 *  Created on: Nov 16, 2023
 *      Author: DELL
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "global.h"
#include "software_timer.h"
#include "button.h"
#include "lcd.h"
#include "fsm_traffic.h"


extern uint8_t col_mode;
extern uint16_t period;
extern uint16_t temp_count[3];

void blink_light(uint8_t col_mode);
void show_frequency(uint16_t period);
void traffic_lights_operation();

#endif /* INC_FSM_H_ */
