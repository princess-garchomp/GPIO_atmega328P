#include "timer_debounce.h"
#include "timer_base.h"

//this function goes into main
void buton_stae_eval_fsm (switch_state *g_button_state, debounce_state *g_debounce_state){
	
	switch(*g_button_state){
		case(WAIT_FOR_PUSH):
			if(*g_debounce_state==CHECK_FOR_RELEASE){
				*g_button_state=PUSHED;
			}
		else{}
		break;
		
		case(PUSHED):
			*g_button_state=WAIT_FOR_RELEASE;
		break;
		
		case(WAIT_FOR_RELEASE):
		if(*g_debounce_state==CHECK_FOR_PRESS){
			*g_button_state=RELEASED;
		}
		else{}
		break;
		
		case(RELEASED):
			*g_button_state=WAIT_FOR_PUSH;
		break;
	}
}

//this function goes into the ISR 
void debounce_checker(debounce_state *g_debounce_state, int *g_debounce_tiemr, _Bool button_pushed, int debounce_constant){
	
	switch(*g_debounce_state){
		case(CHECK_FOR_PRESS):
		if(button_pushed==1){
			*g_debounce_tiemr=*g_debounce_tiemr+1;
			if(*g_debounce_tiemr>debounce_constant){
				*g_debounce_tiemr=0;
				*g_debounce_state=CHECK_FOR_RELEASE;
			}
			else{}
		}
		else{*g_debounce_tiemr=0;}
		break;
		
		case(CHECK_FOR_RELEASE):
		if(button_pushed==0){
			*g_debounce_tiemr=*g_debounce_tiemr+1;
			if(*g_debounce_tiemr>debounce_constant){
				*g_debounce_tiemr=0;
				*g_debounce_state=CHECK_FOR_PRESS;
			}
			else{}
		}
		else{*g_debounce_tiemr=0;}
		break;
	}
	
}