/*
 * Project_Name    :   PWM_Duty_Interrupt1
 * File_Name       :   main.c
 * Author          :   Mohamed Akram JABALLAH
 * Target          :   Atmega324p
*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR (TIMER1_COMPA_vect) {

	PORTB |= (1 << PORTB0);
}

ISR (TIMER1_COMPB_vect) {

	PORTB &= ~ (1 << PORTB0);
}


void PWM_Init (uint16_t OCR_val) {

	TCCR1A |= 0x00;
	TCCR1B |= (1 << WGM12)  | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);

	if (OCR_val > 100) {

		OCR_val = 100;
	}

	OCR1A = OCR_val * 100;
	OCR1B = 10000 - (OCR_val * 100);
}


int main (void) {

	DDRB   = 0xFF;
	PORTB &= 0xFF;
	sei ();

	for (;;) {

		for (uint16_t duty = 1; duty <= 99; duty++) {
			PWM_Init (duty);
			_delay_ms (10);
		}

		for (uint16_t duty = 99; duty >= 1; duty--) {
			PWM_Init (duty);
			_delay_ms (10);
		}
	}

	return 0;
}



















