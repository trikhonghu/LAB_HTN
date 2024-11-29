/*
 * ds3231.c
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */

#include "ds3231.h"

#define DS3231_ADDRESS 0x68<<1

uint8_t ds3231_buffer[7];
uint8_t ds3231_alram_buffer[2];

uint8_t ds3231_hours;
uint8_t ds3231_min;
uint8_t ds3231_sec;
uint8_t ds3231_date;
uint8_t ds3231_day;
uint8_t ds3231_month;
uint8_t ds3231_year;

uint8_t ds3231_alarm_hour;
uint8_t ds3231_alarm_min;

const char* daysOfWeek[7] = {
    "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"
};

void ds3231_init(){
	ds3231_buffer[0] = DEC2BCD(30); //second
	ds3231_buffer[1] = DEC2BCD(22); //minute
	ds3231_buffer[2] = DEC2BCD(21); //hour
	ds3231_buffer[3] = DEC2BCD(6);  //day
	ds3231_buffer[4] = DEC2BCD(15); //date
	ds3231_buffer[5] = DEC2BCD(9);  //month
	ds3231_buffer[6] = DEC2BCD(23); //year
	if(HAL_I2C_IsDeviceReady(&hi2c1, DS3231_ADDRESS, 3, 50) != HAL_OK){
		while(1);
	};
}

void ds3231_Write(uint8_t address, uint8_t value){
	uint8_t temp = DEC2BCD(value);
	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, address, I2C_MEMADD_SIZE_8BIT, &temp, 1,10);
}

void ds3231_ReadTime(){
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, ds3231_buffer, 7, 10);
	ds3231_sec = BCD2DEC(ds3231_buffer[0]);
	ds3231_min = BCD2DEC(ds3231_buffer[1]);
	ds3231_hours = BCD2DEC(ds3231_buffer[2]);
	ds3231_day = BCD2DEC(ds3231_buffer[3]);
	ds3231_date = BCD2DEC(ds3231_buffer[4]);
	ds3231_month = BCD2DEC(ds3231_buffer[5]);
	ds3231_year = BCD2DEC(ds3231_buffer[6]);
}

void update_Time(uint8_t day, uint8_t date, uint8_t month, uint8_t year, uint8_t sec, uint8_t min, uint8_t hours){
	ds3231_Write(ADDRESS_YEAR, year);
	ds3231_Write(ADDRESS_MONTH, month);
	ds3231_Write(ADDRESS_DATE, date);
	ds3231_Write(ADDRESS_DAY, day);
	ds3231_Write(ADDRESS_HOUR, hours);
	ds3231_Write(ADDRESS_MIN, min);
	ds3231_Write(ADDRESS_SEC, sec);
}

void ds3231_ReadAlarm(){
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0X08, I2C_MEMADD_SIZE_8BIT, ds3231_alram_buffer, 2, 10);
	ds3231_alarm_min = BCD2DEC(ds3231_alram_buffer[0]);
	ds3231_alarm_hour = BCD2DEC(ds3231_alram_buffer[1]);
}

void update_Alarm(){
	ds3231_Write(ADDRESS_ALARM_HOUR, ds3231_alarm_hour);
	ds3231_Write(ADDRESS_ALARM_MIN, ds3231_alarm_min);
}
