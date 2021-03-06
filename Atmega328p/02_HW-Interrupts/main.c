#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


//function prototype
void interrupt_setup();

//interrupt volatile byte
volatile uint8_t flag = 0;

int main(void) {

	//data direction bit, setting PB3 to output
	DDRB = (1 << PB3);

	//setup interrupts
	interrupt_setup();

	//blink code
	while (1) {
		if (flag) {
			_delay_ms(1000); //keeps light on and debounces
			flag = 0; //resets flag
			PORTB &= (0 << PB3); //turns light back off
		}
	}

}

//interrupt service routine: code that runs when trigger interrupt
ISR(INT0_vect) {
	PORTB |= (1 << PB3); // turns light on
	flag = 1; // sets flag, we keep delays outside of the interrupt
}

void interrupt_setup() {
	//setting hardware interrupt to normally high
	PORTD |= (1 << PD2);

	//falling edge of INT 0 generates an interrupt request
	EICRA |= (1 << ISC01) | (0 << ISC00);

	//listening for changes on INT0
	EIMSK |= (1 << INT0);

	//turn on interrupts
	sei();
}

