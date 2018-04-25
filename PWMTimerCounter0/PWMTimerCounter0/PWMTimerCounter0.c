#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile double dutyCycle = 0;

int main(void){
    DDRD |= _BV(6);
	
	TCCR0A |= _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	
	TIMSK0 |= _BV(TOIE0);
	
	OCR0A = (dutyCycle / 100) * 255;
	
	sei();
	
	TCCR0B |= _BV(CS02);// | _BV(CS01)
	
    while (1){
		_delay_ms(100);
		
		dutyCycle ++;
		
		if(dutyCycle > 100){
			dutyCycle = 0;
		}
		
	}
}
ISR(TIMER0_OVF_vect){
	OCR0A = (dutyCycle / 100) * 255;
}

