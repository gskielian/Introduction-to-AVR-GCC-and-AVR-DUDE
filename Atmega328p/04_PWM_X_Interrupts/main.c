#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//function prototype
void pwm_init();
void interrupt_init();

//interrupt flag
volatile uint8_t flag = 1;

int main(void) {
	uint8_t i;

	pwm_init();
	interrupt_init();

	//pwm duty-cycle sweep
	while (1) {
		for (i = 0; i < 256; i++){ 
			if (flag) continue;
			OCR1A = i; 
			_delay_ms(100);
		}
	}
}

void pwm_init() {
	//turn PB1 into an output
	DDRB = (1 << DDB1);

	//fast pwm mode
	TCCR1A |= (1 << COM1A1) | (1 << WGM10);
	TCCR1B |= (1 << CS10) | (1 << WGM12);
}

void interrupt_init() {
	//setting hardware interrupt to normally high
	PORTD |= (1 << PD2);

	//falling edge of INT 0 generates an interrupt request
	EICRA |= (1 << ISC01) | (0 << ISC00);

	//listening for changes on INT0
	EIMSK |= (1 << INT0);

	//turn on interrupts
	sei();
}

ISR(INT0_vect) {
	OCR1A = 0x00;
	flag = 1; // sets flag, we keep delays outside of the interrupt
}
