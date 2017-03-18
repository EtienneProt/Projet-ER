//SPI master
#include <avr/io.h>
#include <util/delay.h>

//SPI initvoid
void SPIMasterInit(void) {
//set MOSI, SCK and SS as output
  DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB2);
//set SS to high
  PORTB |= (1<<PB2);
//enable master SPI at clock rate Fck/16
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
//master send function
void SPIMasterSend(uint8_t data){
//select slave
  PORTB &= ~(1<<PB2);
//send data
  SPDR=data;
//wait for transmition complete
  while (!(SPSR &(1<<SPIF)));
//SS to high
  PORTB |= (1<<PB2);
}

int main(void) {
//initialize master SPI
  SPIMasterInit();
//initial PWM value
  uint8_t pwmval = 0;
  while (1) {
    SPIMasterSend(pwmval+=5);
    _delay_ms(1000);
  }
}
