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
			OCR1B = i; 
			_delay_ms(100);
		}
	}
}

void pwm_init() {
	/**
	 * inverse of the PWM is on PB3
	 * and basically have 2 pwm's from OCR1B
	 * we can keep either in input mode to prevent actuation
	 */

	//ddr for pwm pin (inverted)
	//DDRB = (1 << DDB3);

	//ddr for pwm pin (non-inverted)
	DDRB |= (1 << DDB4);

	//fast pwm mode
	TCCR0A |= (1<<WGM01) | (1<<WGM00);

	//no prescaling
	TCCR0B = 1<<CS00;

	//set the clock, again for no pre-scaler
	TCCR1 =  1<<CS10;

	//allow PWM on 1B
	GTCCR  = (1 << PWM1B);

	//set compare bits
	GTCCR |= (0 << COM1B1) | (1 << COM1B0);
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
	PORTB |= (1 << PB3); // turns light on
	flag = 1; // sets flag, we keep delays outside of the interrupt
}
