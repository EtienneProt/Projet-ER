# Code pour le SPI en ER :
Etienne PROT

## Test du SPI : 

### Schéma de cablage : 

On prend deux arduino uno et on relit :
- les deux broches 13 (signal d'horloge)
- les deux broches 12 (Signal MISO : Master INPUT SLave OUTPUT)
- les deux broches 11 (signal MOSI : Master OUTPUT Slave INPUT)
- les deux broches 10 (signal de selection de l'esclave)

Pour le test on branche une led avec en série un résistance de 220 Ohms afin de vérifier le fonctionnement de la liaison SPI, ensuite on peut, si on veut, rajouter un oscilloscope sur différentes broches de l'arduino afin de voir les signaux. 
Personnelement j'ai un oscilloscope à une voie donc je l'ai mis au bornes de la led afin de voir le changement de tension à ses bornes. 

### Code pour l'arduino Master :

```C
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
```

### Pour l'arduino SLAVE :
```C
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
```
### Communication SPI entre deux cartes arduino :
La carte Slave aura le code précédent en C et la deuxième aura ce code :
```C
#include <SPI.h>
#include <string.h>
#define CS 10

int pwmval=0;

void send(char cs, int val) {
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
  
  digitalWrite(cs, LOW);
  SPI.transfer(val);
  digitalWrite(cs, HIGH);
  
  SPI.endTransaction();
}

void setup() {
  pinMode (10, OUTPUT);
  SPI.begin();
}

void loop() {
  send(CS , pwmval+=5);
  delay(1000);
}
```

Prendre pour le pont diviseur, des résistances 10 et 4.7 les plus petites possibles pour éviter l'effet de condensateur sur les platines d'essaies.
