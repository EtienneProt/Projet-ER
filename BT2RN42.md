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

```C

/*
SLAVE
MODULE BLUETOOTH

v1.0

*/

int LED = 13;
int c;



void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()>0)
  {
   c = Serial.read();
   if (c == 0) digitalWrite(LED, LOW);
   if (c ==1 ) digitalWrite(LED, HIGH); 
  }
}
```
