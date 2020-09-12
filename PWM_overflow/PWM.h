#ifndef PWM_H
#define PWM_H

#include <stdint.h>
void _16_bit_tiemr1_config();
void tiemr_1_OCRA1_set(uint16_t data);
void tiemr_1_OCRB1_set(uint16_t data);

uint16_t timer_1_get_OCRA1();
uint16_t timer_1_get_OCRB1();
void milliS_timer_config(uint8_t milliS);


#endif