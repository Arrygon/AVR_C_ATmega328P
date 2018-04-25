#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBR (F_CPU / 16 / BAUD) - 1

void setupUSART(void);
void printStringToUSART(char *str);

unsigned char ReceivedByte;

int main(void){
	
	DDRB |= _BV(PB5);
	setupUSART();
	sei();

	printStringToUSART("Hello, world!");

	while(1){}
}
void setupUSART(void){
	
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
	UBRR0L = UBR;
	UCSR0B |= _BV(RXCIE0);
	
	sei();
}
void printStringToUSART(char *str){
	
    	while(*str != '\0'){
		
		while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		UDR0 = *str;
		str++;
	}
}
ISR(USART_RX_vect){
	
	ReceivedByte = UDR0;

	if(ReceivedByte == 'n'){
		
		PORTB |= _BV(5);
	}else if(ReceivedByte == 'f'){

		PORTB &= ~_BV(5);
	}
}