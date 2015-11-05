#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= (1 << DDB5);

  //effectively above is
  //DDRB = 0b00001000;
  
  //alternate blink
  while (1) {
    if (PIND & (1<<PD2))
        


    PORTB &= ~(1 << PB5); _delay_ms(1000);
    PORTB |= (1 << PB5); _delay_ms(1000);
  }

}

void TWI_INIT() {
	//400kHz
	TWSR = 0x00;
	TWBR = 0x0C;
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

void TWI_WRITE(uint8_t data) {
	TWDR = data;
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


