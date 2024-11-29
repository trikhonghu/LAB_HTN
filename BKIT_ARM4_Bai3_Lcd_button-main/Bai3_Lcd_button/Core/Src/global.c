/*
 * global.c
 *
 *  Created on: Nov 16, 2023
 *      Author: DELL
 */

#include "global.h"

uint8_t mode_step = 1;
uint8_t mode = 1;

uint8_t status0 = 0;
uint8_t status1 = 0;
uint8_t blink_state = 0;

uint16_t count_red = 5000;
uint16_t count_yellow = 2000;
uint16_t count_green = 3000;
uint16_t temp_count[3] = {5000, 2000, 3000};
// RED - YELLOW - GREEN

uint8_t count_mode;
