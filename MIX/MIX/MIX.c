#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile double dutyCycle= 0;

int main(void){
	
	DDRD |= _BV(6) | _BV(5) | _BV(4);
	
	TCCR0A |= _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	TCCR0B |= _BV(CS01);
	TIMSK0 |= _BV(TOIE0);
	
	//setADCup();
	ADMUX |= _BV(REFS0) | _BV(MUX0);
	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADSC);
	DIDR0 = (1 << ADC1D);
	
	TCCR1B |= _BV(CS12) | _BV(WGM12);
	OCR1A = 31250;
	TIMSK1 |= _BV(OCIE1A);
	
	sei();
	
	
	
	while (1){
		PORTD ^= _BV(5);
		_delay_ms(100);
	}
}
//void setADCup(){
//	ADMUX |= _BV(REFS0) | _BV(MUX0);
//	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADSC);
//	DIDR0 = (1 << ADC1D);
//}
// ????????FUNCTION DOESN'T WORK ???????
ISR(TIMER0_OVF_vect){
	OCR0A = dutyCycle;
}
ISR(ADC_vect){
	dutyCycle = ADC / 4;
	ADCSRA |= _BV(ADSC);
}
ISR(TIMER1_COMPA_vect){
	PORTD ^= _BV(4);
}
