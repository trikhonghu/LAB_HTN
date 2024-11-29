/*
 * ds3231.h
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#include "i2c.h"
#include "utils.h"

#define ADDRESS_SEC			0x00
#define ADDRESS_MIN			0x01
#define ADDRESS_HOUR		0x02
#define ADDRESS_DAY			0x03
#define ADDRESS_DATE		0x04
#define ADDRESS_MONTH		0x05
#define ADDRESS_YEAR		0x06

#define ADDRESS_ALARM_HOUR	0X09
#define ADDRESS_ALARM_MIN	0X08

extern uint8_t ds3231_hours;
extern uint8_t ds3231_min;
extern uint8_t ds3231_sec;
extern uint8_t ds3231_date;
extern uint8_t ds3231_day;
extern uint8_t ds3231_month;
extern uint8_t ds3231_year;

extern uint8_t ds3231_alarm_hour;
extern uint8_t ds3231_alarm_min;

extern const char* daysOfWeek[7];

void ds3231_init();

void ds3231_Write(uint8_t address, uint8_t value);

void ds3231_ReadTime();

void update_Time(uint8_t day, uint8_t date, uint8_t month, uint8_t year, uint8_t sec, uint8_t min, uint8_t hours);

void ds3231_ReadAlarm();

void update_Alarm();


#endif /* INC_DS3231_H_ */

