#include "I_O_board.h"

#define MODE_SELECT_TIMER_CONSTANT 60000
#define FRACTION_OF_SECOND 200

enum {WAIT_FOR_PUSH, PUSHED, WAIT_FOR_RELEASE, RELEASED}
	g_switch_state = WAIT_FOR_PUSH;
enum {COLOR_SELECT, FLASH_SPEED_SELECT}
	g_select_mode = COLOR_SELECT;
enum {LED_ON, LED_OFF}
	g_flsh_state = LED_ON;
	
int g_flash_duration_selector = 1;
long  g_button_is_pushed_timer = 0;
int g_color_counter = 0;
	
void switch_state_FSM();
void mode_select_FSM();
void color_set();
void flash_timer_select();
void flash_led_FSM();

int main(void)
{
    all_I_O_config();
    while (1) 
    {
 		switch_state_FSM();
 		mode_select_FSM();
 		color_set();
 		flash_timer_select();
 		flash_led_FSM();
    }
}

void switch_state_FSM(){
	
	static int fake_timer =0;
	static int fake_counter_2 =0;
	switch(g_switch_state){
		case(WAIT_FOR_PUSH):
			if(A_is_pressed()){
				fake_timer = fake_timer +1;
			}
			else{fake_timer = 0;}
			if(fake_timer >50){
				g_switch_state = PUSHED;
			}
			else{}
// 				if(A_is_pressed()){
// 					g_switch_state = PUSHED;
// 				}
//this is without the debounce timr in software. I think i need to add a debounce circuit so i dont have this sloppyness
			break;
		case(PUSHED):
			g_switch_state = WAIT_FOR_RELEASE;
		break;
		case(WAIT_FOR_RELEASE):
			g_button_is_pushed_timer = g_button_is_pushed_timer + 1;
			if(A_is_not_pressed()){
				fake_counter_2 = fake_counter_2 +1;
			}
			else{fake_counter_2=0;}
			if(fake_counter_2 >50){
				g_switch_state = RELEASED;
			}
			else{}
// 			if(A_is_not_pressed()){
// 				g_switch_state = RELEASED;
// 			}
//no debounce timer in software.
		break;
		case(RELEASED):
			g_button_is_pushed_timer = 0;
			g_switch_state = WAIT_FOR_PUSH;
		break;
	}
}
void mode_select_FSM(){
	
	switch(g_select_mode){
		case(COLOR_SELECT):
			if((g_switch_state==RELEASED)&&(g_button_is_pushed_timer>MODE_SELECT_TIMER_CONSTANT)){
				g_select_mode = FLASH_SPEED_SELECT;
			}
			else{}
		break;
		case(FLASH_SPEED_SELECT):
			if((g_switch_state==RELEASED)&&(g_button_is_pushed_timer>MODE_SELECT_TIMER_CONSTANT)){
				g_select_mode = COLOR_SELECT;
			}
			else{}
		break;
	}
	
}
void color_set(){
	if((g_select_mode==COLOR_SELECT)&&(g_switch_state==PUSHED)){
		g_color_counter = (g_color_counter + 1)%8;
		first_rgb_led_color(g_color_counter);
	}
	else{}
}
void flash_timer_select(){
	if((g_select_mode==FLASH_SPEED_SELECT)&&(g_switch_state==PUSHED)){
		g_flash_duration_selector = (g_flash_duration_selector + 1)%16;
	}
	else{}
}
void flash_led_FSM(){
	static int local_time = 1;
	switch(g_flsh_state){
		case(LED_ON):
			first_rgb_led_color(g_color_counter);
			if(local_time==0){
				g_flsh_state = LED_OFF;
			}
			else{}
		break;
		case(LED_OFF):
			first_rgb_led_color(WHITE);
			if(local_time==0){
				g_flsh_state = LED_ON;
			}
			else{}
		break;	
	}
	local_time = (local_time + 1)%(g_flash_duration_selector*FRACTION_OF_SECOND);
}
