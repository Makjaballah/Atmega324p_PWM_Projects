/*
 * Project_Name    :   PWM_2
 * File_Name       :   main.c
 * Author          :   Mohamed Akram JABALLAH
 * Target          :   Atmega324p
*/


#include <avr/io.h>
#include <util/delay.h>



void Init_PWM (Freq);

int main (void) {

	DDRB |= (1 << 0);
	DDRD |= (1 << 4);

	Init_PWM (20);
	OCR1B = 0;

	for (;;) {

		while (OCR1B <= 1022) {

			OCR1B += 1;
			_delay_ms (5);
		}
		_delay_ms (1000);

		while (OCR1B > 0) {

			OCR1B -= 1;
			_delay_ms (5);
		}
		_delay_ms (1000);
	}

	return 0;
}


void Init_PWM (uint16_t Freq) {

	TCCR1A |=  (1 << COM1B1)  | (1 << WGM11) | (1 << WGM10);
	TCCR1B |=  (1 << CS11)    | (1 << CS10)  | (1 << WGM12) | (1 << WGM13);
	OCR1A = (F_CPU/(64*Freq))-1;
}
