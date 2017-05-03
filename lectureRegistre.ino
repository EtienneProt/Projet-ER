// Lecture de tous les registres du MAX6966 :
#include <SPI.h>
#define CS 8

int fq = 1000000; // Fréquence de transfert

int adr;

int pwmval = 0x00;

uint16_t receivedVal16 = 0;

void send(char cs, int adresse, int val, char rw) {
  digitalWrite(cs, LOW);
  adr = (adresse << 8) + val;
  SPI.beginTransaction(SPISettings(fq, MSBFIRST, SPI_MODE0));

  //  SPI.transfer(adresse);
  //  SPI.transfer(val);

  //SPI.transfer16(adr);

  receivedVal16 = SPI.transfer16(adr + (rw << 15));

  SPI.endTransaction();

  digitalWrite(cs, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode (CS, OUTPUT);
  digitalWrite(CS, HIGH);

  pinMode (13, OUTPUT);
  pinMode (12, INPUT);
  pinMode (11, OUTPUT);

  SPI.begin();

  delay(10);
}

void loop() {
  for (char a = 0; a <= 32; a++) {
    send(CS , a , pwmval, 1);
    Serial.print("Receive : ");
    Serial.print(receivedVal16|(1<<15), BIN);
    Serial.println(" ");
  }
  while(1);
}
