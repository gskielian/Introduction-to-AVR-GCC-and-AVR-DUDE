#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB = 0b00001000;

  while (1) {
    PORTB = 0x00; _delay_ms(100);
    PORTB = 0b00001000; _delay_ms(100);
  }
  /*
  //alternate blink
  while (1) {
    PORTB &= ~(1 << PB3); _delay_ms(100);
    PORTB |= (1 << PB3); _delay_ms(100);
  }
  */
}
