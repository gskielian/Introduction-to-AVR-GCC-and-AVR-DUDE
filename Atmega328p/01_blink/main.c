#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= (1 << DDB5);

  //effectively above is
  //DDRB = 0b00001000;
  
  //alternate blink
  while (1) {
    PORTB &= ~(1 << PB5); _delay_ms(10);
    PORTB |= (1 << PB5); _delay_ms(10);
  }

  //effectively above is
  //  while (1) {
  //    PORTB = 0b00001000; _delay_ms(1000);
  //    PORTB = 0b00000000; _delay_ms(1000);
  //  }
  
}
