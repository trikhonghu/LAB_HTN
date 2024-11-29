/*
 * fsm_mode.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#ifndef INC_FSM_MODE_H_
#define INC_FSM_MODE_H_

#include "main.h"

#include "ds3231.h"
#include "lcd.h"
#include "software_timer.h"
#include "button.h"
#include "fsm_set_time.h"
#include "fsm_timer.h"
#include "get_time_from_internet.h"
#include "note.h"
#include "bell_picture.h"
#include "touch.h"

#define NORMAL_MODE 0
#define SET_TIME_MODE 1
#define TIMER_MODE	2
#define ALARM_MODE	3


extern uint8_t mode;
extern uint8_t alarm_state;

void fsm_machine_mode();

#endif /* INC_FSM_MODE_H_ */
