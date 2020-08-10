#include "I_O_base.h"
#include "led_and_button.h"

button_base pin7_in;
output_base pin13_out;

int main(void)
{
	void _16_bit_tiemr1_config();
	pin7_in.config_pin_for_button();
	pin13_out.config_pin_for_output();

//	pin13_out.config_pin_for_output();
	
    while (1) 
    {
		if(pin7_in.is_pressed()){
			pin13_out.set_low();
		}
		else{
			pin13_out.set_high();
		}
    }
}

