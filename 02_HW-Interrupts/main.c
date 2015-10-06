#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t flag = 0;

int main(void) {

  /////////////
  //led setup//
  /////////////

  //data direction bit, setting PB3 to output
  DDRB = (1 << PB3);


  ////////////////////
  //Interrupt stuff //
  ////////////////////
  
  //setting hardware interrupt to normally high
  PORTB |= (1 << PB2);
  
  //falling edge of INT 0 generates an interrupt request
  MCUCR |= (1 << ISC01) | (0 << ISC00);

  //listening for changes on INT0
  GIMSK |= (1 << INT0);

  //set global interrupts
  sei();

  /////////
  //Blink//
  /////////
  
  while (1) {
    if (flag) {
	    _delay_ms(100); //keeps light on and debounces
	    flag = 0; //resets flag
	    PORTB &= (0 << PB3); //turns light back off
    }
  }

}

ISR(INT0_vect) {
    PORTB |= (1 << PB3); // turns light on
    flag = 1; // sets flag, we keep delays outside of the interrupt
}
