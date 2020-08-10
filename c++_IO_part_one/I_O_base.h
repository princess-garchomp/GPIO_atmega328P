#pragma once

#include <avr/io.h>
#include <stdbool.h>

//this if for the input

class button_state_machine{
	
	public:
		button_state_machine();
		_Bool debounce_detect(_Bool button_state);
	
	private:
		enum {WAIT_FOR_PRESS, CONFIRM_PUSHED, WAIT_FOR_RELEASE, CONFIRM_RELEASED}
			machine_state;
		uint16_t time_entered_state;
};
	
class button_base{
		
		public:
			_Bool is_pressed();
			_Bool is_released();
			_Bool debounce_press();
			void config_pin_for_button();
		private:
			button_state_machine press_state;
};

//this is the output

class output_base{
	public:
		void set_high();
		void set_low();
		void config_pin_for_output();
	};