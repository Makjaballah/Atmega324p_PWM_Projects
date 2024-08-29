/*
 * Project_Name    :   PWM_Duty_Interrupt2
 * File_Name       :   main.c
 * Author          :   Mohamed Akram JABALLAH
 * Target          :   Atmega324p
*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR (TIMER1_COMPA_vect);
ISR (TIMER1_COMPB_vect);
ISR (TIMER0_COMPA_vect);

void PWM_Init (uint16_t Freq);
void PWM_Duty (uint8_t Time_val);


int main (void) {

	DDRB   = 0xFF;
	PORTB &= 0xFF;

	PWM_Init (250);
	PWM_Duty (20);
	sei ();
	for (;;) {

	}

	return 0;
}


ISR (TIMER1_COMPA_vect) {

	PORTB |= (1 << PORTB0);
}


ISR (TIMER1_COMPB_vect) {

	PORTB &= ~ (1 << PORTB0);
}


ISR (TIMER0_COMPA_vect) {

	uint16_t period = OCR1A;
	OCR1B ++;

	if (OCR1B >= period) {

		OCR1B = 0;
	}
}


void PWM_Init (uint16_t Freq) {

	TCCR1B |= (1 << WGM12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
	OCR1A = (F_CPU/(Freq))-1;
	OCR1B = 0;
}


void PWM_Duty (uint8_t Time_val) {

	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
	OCR0A = (Time_val*488.29)-1;
}
