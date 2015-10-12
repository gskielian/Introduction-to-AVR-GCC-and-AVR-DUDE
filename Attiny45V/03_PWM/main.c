#include <avr/io.h>
#include <util/delay.h>

//function prototype
void pwm_init();

int main(void) {
	uint8_t i;

	pwm_init();

	//pwm duty-cycle sweep
	while (1) {
		for (i = 0; i < 256; i++){ 
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

	//ddr for pwm pin (non-inverted
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
