/*
 * fsm_set_time.h
 *
 *  Created on: Nov 15, 2023
 *      Author: Admin
 */

#ifndef INC_FSM_SET_TIME_H_
#define INC_FSM_SET_TIME_H_

#include "main.h"
#include "ds3231.h"
#include "lcd.h"
#include "software_timer.h"
#include "button.h"


#define MIN_MODE	11
#define HOUR_MODE	12
#define DAY_MODE 	13
#define DATE_MODE	14
#define MONTH_MODE	15
#define YEAR_MODE	16

extern uint8_t mode_set_time;
extern uint8_t send_string;

extern uint8_t flag;

void fsm_set_time();

#endif /* INC_FSM_SET_TIME_H_ */
