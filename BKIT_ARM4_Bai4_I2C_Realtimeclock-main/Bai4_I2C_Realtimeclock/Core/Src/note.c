/*
 * note.c
 *
 *  Created on: Jun 1, 2024
 *      Author: Windows
 */

#include "note.h"

int note[62] = {
	  REST, NOTE_D4,
	  NOTE_G4, NOTE_AS4, NOTE_A4,
	  NOTE_G4, NOTE_D5,
	  NOTE_C5,
	  NOTE_A4,
	  NOTE_G4, NOTE_AS4, NOTE_A4,
	  NOTE_F4, NOTE_GS4,
	  NOTE_D4,
	  NOTE_D4,

	  NOTE_G4, NOTE_AS4, NOTE_A4,
	  NOTE_G4, NOTE_D5,
	  NOTE_F5, NOTE_E5,
	  NOTE_DS5, NOTE_B4,
	  NOTE_DS5, NOTE_D5, NOTE_CS5,
	  NOTE_CS4, NOTE_B4,
	  NOTE_G4,
	  NOTE_AS4,

	  NOTE_D5, NOTE_AS4,
	  NOTE_D5, NOTE_AS4,
	  NOTE_DS5, NOTE_D5,
	  NOTE_CS5, NOTE_A4,
	  NOTE_AS4, NOTE_D5, NOTE_CS5,
	  NOTE_CS4, NOTE_D4,
	  NOTE_D5,
	  REST, NOTE_AS4,

	  NOTE_D5, NOTE_AS4,
	  NOTE_D5, NOTE_AS4,
	  NOTE_F5, NOTE_E5,
	  NOTE_DS5, NOTE_B4,
	  NOTE_DS5, NOTE_D5, NOTE_CS5,
	  NOTE_CS4, NOTE_AS4,
	  NOTE_G4,

	  REST
};
int dur[62] = {
	  2, 4,
	  4, 8, 4,
	  2, 4,
	  2,
	  2,
	  4, 8, 4,
	  2, 4,
	  1,
	  4,

	  4, 8, 4,
	  2, 4,
	  2, 4,
	  2, 4,
	  4, 8, 4,
	  2, 4,
	  1,
	  4,

	  2, 4,
	  2, 4,
	  2, 4,
	  2, 4,
	  4, 8, 4,
	  2, 4,
	  1,
	  4, 4,

	  2, 4,
	  2, 4,
	  2, 4,
	  2, 4,
	  4, 8, 4,
	  2, 4,
	  1
};

void buzzer_start_freq(uint32_t freq){
	if(freq == 0) return;
	uint32_t timer_clock = 84000000; //APB1
	uint32_t prescaler = 0;
	uint32_t period =  (timer_clock/freq) - 1;

	//Adjust prescaler if the period is too large for 16_bit timer
	while(period > 65535){
		prescaler++;
		period = (timer_clock / (prescaler + 1)/freq) - 1;

	}

	__HAL_TIM_SET_PRESCALER(&htim13, prescaler);
	__HAL_TIM_SET_AUTORELOAD(&htim13, period);
	__HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, period/2);

	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1); //restart PWM to apply changes
}

void stop_buzzer(){
	HAL_TIM_PWM_Stop(&htim13, TIM_CHANNEL_1);
}

void play_note(int* note, int* dur, int len){
	for(int i = 0; i < len; i++){
		buzzer_start_freq(note[i]);
		HAL_Delay((1000/dur[i])*1.3);
		stop_buzzer();
	}
}

uint32_t index_note = 0;

void play_note_in_main(int* note, int* dur, int len){
	if(flag_timer_alarm == 1){
		stop_buzzer();
		buzzer_start_freq(note[index_note]);
		setTimerAlarm((1000/dur[index_note])*1.3);
		if(index_note >= len-1){
			index_note = 0;
		}else
			index_note++;
	}
}
