

#include <avr/io.h>
#include <avr/interrupt.h>
#include "I_O.h"
#include "PWM.h"


/*

// timer one as overflow PWM
int main(void)
{
    first_rgb_led_config();
	cli();
	_16_bit_tiemr1_config();
	sei();
    while (1) 
    {
	//	first_rgb_led_color(BLUE);
    }
}

ISR(TIMER1_COMPA_vect){
	first_rgb_led_color(BLUE);
}

ISR(TIMER1_COMPB_vect){
	first_rgb_led_color(WHITE);
}
*/

int main(void)
{
	first_rgb_led_config();
	cli();
	milliS_timer_config(10);
	_16_bit_tiemr1_config();
	sei();
	while (1)
	{
		//	first_rgb_led_color(BLUE);
	}
}

ISR(TIMER1_COMPA_vect){
	first_rgb_led_color(BLUE);
}

ISR(TIMER1_COMPB_vect){
	first_rgb_led_color(WHITE);
}

ISR(TIMER0_COMPA_vect){
	uint16_t period = timer_1_get_OCRA1();
	uint16_t duty = timer_1_get_OCRB1();
	
	if (duty<period){
		duty++;
	}
	else{
		duty = 0;
	}
	tiemr_1_OCRB1_set(duty);
}
