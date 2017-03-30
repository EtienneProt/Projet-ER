```C
/*
MASTER
MODULE BLUETOOTH

v1.0

*/


int Pin = 9;
int P;


void setup() {
  pinMode(Pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  P = digitalRead(Pin);
  if (P == 0)
    Serial.write(0);
  else 
    Serial.write(1);
}
```
