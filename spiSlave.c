//SPI slave
#include <avr/io.h>
#include <avr/interrupt.h>
//SPI init
void SPISlaveInit(void) {
//set MISO as output
  DDRB |= (1<<PB4);
//enable SPI and enable SPI interrupt
  SPCR = (1<<SPE)|(1<<SPIE);
}
void InitPort(void) {
//set PD6 (OC0A) as output
  DDRD|=(1<<PD6);
}
//Initialize Timer0
void InitTimer0(void) {
//Set Initial Timer value
  TCNT0=0;
//Place compare value to Output compare register
  OCR0A=0;
//Set fast PWM mode
//and make clear OC0A on compare match
  TCCR0A|=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
}
void StartTimer0(void) {
//Set prescaller 64 and start timer
  TCCR0B|=(1<<CS01)|(1<<CS00);
}
ISR(SPI_STC_vect) {
  OCR0A=SPDR;
}

int main(void) {
//initialize slave SPI
  SPISlaveInit();
  InitPort();
  InitTimer0();
  StartTimer0();
  sei();
  while (1) {
    //loop
  }
  return 0;
}
