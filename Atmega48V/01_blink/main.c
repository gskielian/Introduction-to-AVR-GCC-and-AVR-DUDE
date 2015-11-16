#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRC |= (1 << DDC3);

  
  //alternate blink
  while (1) {
    PORTC &= ~(1 << PC3); _delay_ms(1000);
    PORTC |= (1 << PC3); _delay_ms(1000);
  }

  //effectively above is
  //  while (1) {
  //    PORTB = 0b00001000; _delay_ms(1000);
  //    PORTB = 0b00000000; _delay_ms(1000);
  //  }
  
}
