#ifndef TIMER_DEBOUNCE
#define TIMER_DEBOUNCE

typedef enum {WAIT_FOR_PUSH=0b00, PUSHED=0b01, WAIT_FOR_RELEASE=0b10, RELEASED=0b11}
	switch_state;

typedef enum {CHECK_FOR_PRESS=0b00, CHECK_FOR_RELEASE=0b01}
	debounce_state;

//this function goes into main
void buton_stae_eval_fsm (switch_state* g_button_state, debounce_state* g_debounce_state);

//this functino goes into the timer ISR
void debounce_checker(debounce_state* g_debounce_state, int* g_debounce_tiemr, _Bool button_pushed, int debounce_constant);

#endif