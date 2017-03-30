const char led = 9;

int w;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT) ;
}

void loop() {
  recevoir();
  if (w == 1) {
    digitalWrite(led, HIGH);
  }
  if (w == 0) {
    digitalWrite(led, LOW);
  }
  delay(500);
}

void recevoir() {
  if (Serial.available()) {
    w = Serial.read();
    Serial.println(w);
    //Serial.flush();
  }
}

