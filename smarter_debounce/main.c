#include "I_O_board.h"
#include "button_state_eval.h"

#define DEBOUNCE_THRESHOLD 50

switch_state g_A_switch_state = WAIT_FOR_PUSH;
switch_state g_E_switch_state = WAIT_FOR_PUSH;
switch_state g_I_switch_state = WAIT_FOR_PUSH;

int g_A_switch_debounce =0;
int g_E_switch_debounce =0;
int g_I_switch_debounce =0;


int g_color_1_counter = 0;
int g_color_2_counter = 0;

void color_set_1();
void color_set_2();

int main(void)
{
	all_I_O_config();
	while (1)
	{
		color_set_1();
		color_set_2();
		buton_stae_eval_fsm(&g_A_switch_state, &g_A_switch_debounce, A_is_pressed(), DEBOUNCE_THRESHOLD);
		buton_stae_eval_fsm(&g_E_switch_state, &g_E_switch_debounce, E_is_pressed(), DEBOUNCE_THRESHOLD);

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
