/*
 * Project_Name    :   PWM_1
 * File_Name       :   main.c
 * Author          :   Mohamed Akram JABALLAH
 * Target          :   Atmega324p
*/


#include <avr/io.h>
#include <util/delay.h>



void Init_PWM (void);

int main (void) {

	DDRD |= (1 << 4);
	Init_PWM();
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


void Init_PWM (void) {

	TCCR1A |=   (1 << COM1B1)  | (1 << WGM11) | (1 << WGM10);
	TCCR1B |=   (1 << CS10)    | (1 << WGM12);
	TCNT1   = 0x00;

}





