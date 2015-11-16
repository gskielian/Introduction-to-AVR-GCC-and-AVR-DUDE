#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= (1 << DDB5);

  //alternate blink
  while (1) {
    PORTB &= ~(1 << PB5); _delay_ms(100);
    PORTB |= (1 << PB5); _delay_ms(100);
  }

}

void TWI_INIT() {
	TWSR = 0x00;
	//set twbr to 1 
	TWBR = 0x01;
	//enable bit
	TWCR = (1<<TWEN);
}

//send start signal
void TWI_START() {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

//send stop signal
void TWI_STOP() {
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void TWI_WRITE(uint8_t u8data) {
	TWDR = u8data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t TWI_READ_ACK() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t TWI_READ_NACK() {
	TWCR = (1<<TWINT) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t TWI_GET_STATUS() {
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}


