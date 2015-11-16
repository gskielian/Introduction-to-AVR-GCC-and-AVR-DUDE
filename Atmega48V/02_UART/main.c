#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#define FOSC 128000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

int main(void) {
	DDRC |= (1 << DDC3); //third from the edge

	USART_Init(MYUBRR); //defined automatically via a macro

		while (1) {
			/*test once every two seconds*/
			/*can detect via ftdi cable through a level shifter*/
			PORTC &= ~(1 << PC3); _delay_ms(1000);
			PORTC |= (1 << PC3); USART_Transmit('a'); _delay_ms(1000);
		}
}

void USART_Init( unsigned int ubrr) {
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit, no parity */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00)|(0<<UPM00);
}

//sending frame with 5 to 8 bits
void USART_Transmit( unsigned char data ) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

//receiving frame with 5 to 8 bits
unsigned char USART_Receive( void ) {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
