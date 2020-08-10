#include "timer_global_count.h"

volatile unsigned long _mS;

void _16_bit_tiemr1_config(){
	
	TCCR1B |= (1ul<<(CS12)) | (1ul<<(WGM12));
	TIMSK1 |= (1ul<<(OCIE1A));
	//OCRnA=F_CPU/((frequency*2*N)-1)
	OCR1A = TIMER1_FREQ_CALCULATION;
	//here we set the frequency by changing the value of N
}

//in another file if(.1_ms-.1_ms>10) if event happens for 1 ms then do a thing


//.1ms
unsigned long _mS_counter(){
return _mS;
}

ISR(TIMER1_COMPA_vect){
	_mS += _mS;
}