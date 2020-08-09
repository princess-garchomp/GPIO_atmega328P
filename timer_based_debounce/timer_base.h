#ifndef TIMER_BASE_H
#define TIMER_BASE_H

#include <avr/interrupt.h>

void _8_bit_tiemr0_config();
void _16_bit_tiemr1_config(int frequency);
void _8_bit_tiemr2_config(uint8_t frequency);

#endif