#include "I_O_base.h"
#include "timer_global_count.h"

#define MASK(X) (1ul<<(X))

//this is the output

button_state_machine::button_state_machine(){
	machine_state = WAIT_FOR_PRESS;
}

_Bool button_state_machine::debounce_detect(_Bool button_evaluation){
	uint16_t current_time = _mS_counter();
	
	switch(machine_state){
		case WAIT_FOR_PRESS:
			if(button_evaluation==1){
				time_entered_state = current_time;
				machine_state = CONFIRM_PUSHED;
			}
		break;
		case CONFIRM_PUSHED:
			if(button_evaluation==0){
				machine_state = WAIT_FOR_PRESS;
			}
			else if((uint16_t)(time_entered_state-current_time)>=100)
			{
				machine_state = WAIT_FOR_RELEASE;
			}
		break;
		case WAIT_FOR_RELEASE:
			if(button_evaluation==0){
				machine_state = CONFIRM_RELEASED;
			}
		break;
		case CONFIRM_RELEASED:
			if(button_evaluation==1){
				machine_state = WAIT_FOR_RELEASE;
			}
			else if((uint16_t)(time_entered_state-current_time)>=100){
				machine_state = WAIT_FOR_PRESS;
			}
		break;
	}
	return 0;
}



void button_base::config_pin_for_button(){			
	DDRD &= ~(MASK(PD7));
	PORTD|= MASK(PD7);
}

_Bool button_base::is_pressed(){
	return!(PIND & MASK(PD7));
}

_Bool button_base::is_released(){
	return!(is_pressed());
}

_Bool button_base::debounce_press(){
	return press_state.debounce_detect(is_pressed());
}

//this is the input



void output_base::config_pin_for_output(){
	DDRB|=MASK(PB5);
	void set_low();
}

void output_base::set_low(){
	PORTB &= ~MASK(PB5);
}

void output_base::set_high(){
	PORTB|=MASK(PB5);
}