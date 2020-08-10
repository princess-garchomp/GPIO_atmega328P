#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

//the frequency is something that I am setting
//OCRnA=F_CPU/(frequency*2*N)-1
#define FOSC 16000000 // Clock Speed
#define TIMER1_FREQ 12
#define TIMER1_PRE_SCALE 64
//should result in .1_mS for every intyerrup

//this calculates what value should go into OCRxA register to make an IRQ happen every time the frequency has passed
#define TIMER1_FREQ_CALCULATION (FOSC/(TIMER1_FREQ*2*TIMER1_PRE_SCALE))-1



void _16_bit_tiemr1_config();


//.1ms
unsigned long _mS_counter();