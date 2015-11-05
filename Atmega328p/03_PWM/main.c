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
			OCR1A = i; 
			_delay_ms(100);
		}
	}
}

void pwm_init() {
	//turn PB1 into an output
	//just for note, this __is__ the OCR1A pin
	DDRB = (1 << DDB1);

	//fast pwm mode
	TCCR1A |= (1 << COM1A1) | (1 << WGM10);
	TCCR1B |= (1 << CS10) | (1 << WGM12);
}
