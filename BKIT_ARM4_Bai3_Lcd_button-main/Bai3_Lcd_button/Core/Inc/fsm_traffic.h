/*
 * fsm_mode1.h
 *
 *  Created on: Nov 16, 2023
 *      Author: DELL
 */

#ifndef INC_FSM_TRAFFIC_H_
#define INC_FSM_TRAFFIC_H_

#include "global.h"
#include "software_timer.h"
#include "button.h"
#include "lcd.h"


void off_state(uint16_t x, uint16_t y_start);
void red_state(uint16_t x, uint16_t y_start);
void yellow_state(uint16_t x, uint16_t y_start);
void green_state(uint16_t x, uint16_t y_start);
void left_light(uint8_t col_code);
void right_light(uint8_t col_code);
void draw_filled_retangle(uint16_t x, uint16_t y_start);

void left_light_mode1();
void right_light_mode1();
void traffic_lights();


#endif /* INC_FSM_TRAFFIC_H_ */
