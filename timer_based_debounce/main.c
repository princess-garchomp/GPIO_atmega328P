#include "I_O_board.h"
#include "timer_base.h"
#include "timer_debounce.h"

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


#define DEBOUNCE_THRESHOLD 50

switch_state g_A_switch_state = WAIT_FOR_PUSH;
switch_state g_E_switch_state = WAIT_FOR_PUSH;

debounce_state g_A_debounce_state=CHECK_FOR_PRESS;
debounce_state g_E_debouce_state=CHECK_FOR_PRESS;


int g_A_switch_debounce_counter =0;
int g_E_switch_debounce_counter =0;




int g_color_1_counter = 0;
int g_color_2_counter = 0;

void color_set_1();
void color_set_2();


int main(void)
{
	all_I_O_config();
	cli();
	//_8_bit_tiemr0_config();
	//	_16_bit_tiemr1_config(TIMER1_FREQ_CALCULATION);
	_8_bit_tiemr2_config(TIMER2_FREQ_CALCULATION);
	sei();
	while (1)
	{
		
		color_set_1();
		color_set_2();
		buton_stae_eval_fsm(&g_A_switch_state, &g_A_debounce_state);
		buton_stae_eval_fsm(&g_E_switch_state, &g_E_debouce_state);

	}
}

void color_set_1(){
	if((g_A_switch_state==PUSHED)){
		g_color_1_counter = (g_color_1_counter + 1)%8;
		first_rgb_led_color(g_color_1_counter);
	}
	else{}
}

void color_set_2(){
	if((g_E_switch_state==PUSHED)){
		g_color_2_counter = (g_color_2_counter + 1)%8;
		second_rgb_led_color(g_color_2_counter);
	}
	else{}
}

ISR(TIMER2_COMPA_vect){

	debounce_checker(&g_A_debounce_state, &g_A_switch_debounce_counter, A_is_pressed(), DEBOUNCE_THRESHOLD);
	debounce_checker(&g_E_debouce_state, &g_E_switch_debounce_counter, E_is_pressed(), DEBOUNCE_THRESHOLD);

}