#include "PWM.h"
#include <avr/io.h>


void _16_bit_tiemr1_config(){

	//no prescaler
	//wgm12 is CTC mode
	TCCR1B |= (1ul<<(CS10)) | (1ul<<(WGM12));
	//overfolw interrupt enable
	TIMSK1 |= (1ul<<(OCIE1A)|(1ul<<OCIE1B));
	//OCRnA=F_CPU/((frequency*2*N)-1)
	OCR1A = 800;
	OCR1B = 100;
	//here we set the frequency by changing the value of N
}

void tiemr_1_OCRA1_set(uint16_t data){
	OCR1A = data;
}
void tiemr_1_OCRB1_set(uint16_t data){
	OCR1B = data;
}

uint16_t timer_1_get_OCRA1(){
	return OCR1A;
}

uint16_t timer_1_get_OCRB1(){
	return OCR1B;
}

//ISRTIMER1_COMPA_vect){on led;}

//ISR(TIMER1_COMPB_vect){led off;}
	
void milliS_timer_config(uint8_t milliS){
		TCCR0A |= (1ul<<WGM01); //ctc mote
		TCCR0B |= (1ul<< CS02)|(1ul<<CS00);//prescaler 1024
		//freq = Fcpu/(2*n*(1+OCRnA))
		//freq =Fcpu*milliS/(1000*2*1024*(1+OCRnA))
		
		//OCRna = milliS*Fcpu/(1000*2*1024)-1
		OCR0A = milliS*7.8125-1;
		TIMSK0 |= (1ul<<OCIE0A);
}