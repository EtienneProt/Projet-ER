#include <avr/io.h>
#include <util/delay.h>

uint16_t recep=0;

//SPI initvoid
void SPIMasterInit(void) {
//set MOSI, SCK and SS as output
  DDRB |= ( (1<<PB3)|(1<<PB5)|(1<<PB2) );
//set SS to high
  PORTB |= (1<<PB2);
  //PORTB &=~ (1<<PB2);
//enable master SPI at clock rate Fck/128
  SPCR |= ( (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1) );
}

//master send function
uint16_t SPIMasterSend(uint16_t data){
  recep=0;
//select slave
  PORTB &=~ (1<<PB2);
//send data 1
  SPDR=data>>8;
//wait for transmition complete
  while (!(SPSR &(1<<SPIF)));
  recep=SPDR;
//send data 2
  SPDR=data;
//wait for transmition complete
  while (!(SPSR &(1<<SPIF)));
  recep = recep<<8+SPDR;
//SS to high
  PORTB |= (1<<PB2);
  return SPDR;
}

int main(void) {
  Serial.begin(9600);
//initialize master SPI
  SPIMasterInit();
  _delay_ms(100);
//send the configuration address
  //SPIMasterSend(0x10);
//send the configuration
  Serial.println((SPIMasterSend((0x10<<8)+1)),HEX);
  _delay_us(50);
  Serial.println((SPIMasterSend((0x90<<8)+1)),HEX);
  _delay_us(50);
  Serial.println((SPIMasterSend((0x90<<8)+1)),HEX);

  while(1);

  
//initial PWM value
  uint8_t pwmval = 255;
  uint8_t addressPin = 4;
  
  while (1) {
    static uint8_t val=3;
//    SPIMasterSend((4<<8)+pwmval);
//    pwmval-=5;
//    Serial.println(recep);
//    _delay_ms(1000);

      SPIMasterSend((0x00<<8)+val);
      _delay_us(50);
      SPIMasterSend(0x8000);
      _delay_ms(1000);
      if (val==254) val=3; else val++;
      
  }
}
