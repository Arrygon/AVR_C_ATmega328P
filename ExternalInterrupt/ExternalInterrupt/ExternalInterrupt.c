#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t flagINT0 = 0;

int main(void){
	
	DDRD |= _BV(6);
	
	EICRA |= _BV(ISC00) | _BV(ISC01);
	
	EIMSK |= _BV(INT0);
	
	/*sei();*/
	
    while (1){
		if(flagINT0 == 0){
			sei();
		}else{
			cli();
			_delay_ms(100);
			flagINT0 = 0;
		}/*end of if statement*/
	}/*end of while loop*/
}/*end of mai function*/

ISR(INT0_vect){
	PORTD ^= _BV(6);
	flagINT0 = 1;
}/*end of ISR for INT0*/