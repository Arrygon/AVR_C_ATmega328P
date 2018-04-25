#include <avr/io.h>
#include <avr/interrupt.h>

/*volatile uint8_t counter = 0;
int main(void){
	
    DDRB |= _BV(5);
	
	TCCR1B |= _BV(CS12) | _BV(WGM12);
	
	OCR1A = 6250;
	
	TIMSK1 |= _BV(OCIE1A);
	
	sei();

    while (1){}
}
ISR(TIMER1_COMPA_vect){
	counter++;
	if(counter >= 10){
		PORTB ^= _BV(5);
		counter = 0;
	}
}*/

volatile uint8_t counter = 0;

int main(void){
	
	DDRB |= _BV(5);
	
	TCCR0A |= _BV(WGM01) ;
	TCCR0B |= _BV(CS00) | _BV(CS02);
	TIMSK0 |= _BV(OCIE0A);
	
	OCR0A = 155;
	
	sei();

	while (1){}
}
ISR(TIMER0_COMPA_vect){
	counter++;
	if(counter >= 100){
		PORTB ^= _BV(5);
		counter = 0;
	}	
}