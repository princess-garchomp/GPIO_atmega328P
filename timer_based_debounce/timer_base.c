#include <avr/io.h>
#include "timer_base.h"

/*
//OCRnA=F_CPU/(frequency*2*N)-1

#define FOSC 16000000 // Clock Speed
#define TIMER1_FREQ 4 //4
#define TIMER1_PRE_SCALE 254 //254
//TIMER1_FREQ*2*TIMER1_PRE_SCALE > 122.07 or we get an interger overflow
//int is size 65536 so the following calculation needs to evaluate less then this
#define TIMER1_FREQ_CALCULATION (FOSC/(TIMER1_FREQ*2*TIMER1_PRE_SCALE))-1

#define TIMER2_FREQ 1000 //4
#define TIMER2_PRE_SCALE 254 //254
#define TIMER2_FREQ_CALCULATION (FOSC/(TIMER2_FREQ*2*TIMER2_PRE_SCALE))-1

*/

void _8_bit_tiemr0_config(){
	//fOCnA=((fclk_I/O)/(2*N*(1+OCRnA))
	//fclk_I/O is the system clock
	//N is the prescale set to 1024 set on the following line
	//OCRnA is the maximum number that this counter can count to (254 for 8 bit)
	TCCR0B|=(1ul<<(CS00))|(1ul<<(CS02));
	//the bigger this number the lower the frequency. the lower the frequency the the slower the interupts happen
	//hz=(1/time)
	// 1hz=1/1=1second
	//10hz=1/10=.1second 
	TIMSK0|=(1ul<<(TOIE0));
	
}
	
		// this is just an overflow timer
// void _16_bit_tiemr1_config(){
// 	 TCCR1B |= (1ul<<(CS12));
// 	 TIMSK1 |= (1ul<<(TOIE1));
// }

void _16_bit_tiemr1_config(int frequency){

		
	 TCCR1B |= (1ul<<(CS12)) | (1ul<<(WGM12));
	 TIMSK1 |= (1ul<<(OCIE1A));
	 //OCRnA=F_CPU/((frequency*2*N)-1)
	 OCR1A = (int)frequency;
	 //here we set the frequency by changing the value of N
}


void _8_bit_tiemr2_config(uint8_t frequency){
	TCCR2A|=(1ul<<(WGM21));
	TCCR2B|=(1ul<<(CS22))|(1ul<<(CS21));
	TIMSK2|=(1ul<<(OCIE2A));
	OCR2A = (uint8_t)frequency;
	//this has a max number of 256
}


