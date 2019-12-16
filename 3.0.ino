#include <elapsedMillis.h>

const uint8_t dataPinSIPO = 11, clockPinSIPO = 10, latchPinSIPO = 9;
const uint8_t dataPinPISO = 2, clockPinPISO = 13, latchPinPISO = 12;
volatile int state = -1, brzina = 300;
byte incoming = 72;
int bin = 0;

void setup() {
  pinMode(dataPinPISO, INPUT_PULLUP);
  pinMode(clockPinPISO, OUTPUT);
  pinMode(latchPinPISO, OUTPUT);
  pinMode(dataPinSIPO, OUTPUT);
  pinMode(clockPinSIPO, OUTPUT);
  pinMode(latchPinSIPO, OUTPUT);
  digitalWrite(latchPinPISO, HIGH);
  digitalWrite(clockPinPISO, LOW);
  digitalWrite(latchPinSIPO, HIGH);
  digitalWrite(clockPinSIPO, LOW);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  attachInterrupt(digitalPinToInterrupt(dataPinPISO), isr, RISING);
}

void loop() {
  float temp = 2;
  for(int i = 1;; i *= temp) {
    if((i == 16 && temp == 2) || (i == 1 && temp == 0.5))
      temp = 1 / temp;
      
    elapsedMillis counter;
    while(counter < 300) {
      binary(i - 1);
      if((millis() % 300 < 10 || millis() % 300 > 290) || (millis() % brzina < 10 || millis() % brzina > brzina - 10)) {
        binary(i - 1);
      }
  
      digitalWrite(latchPinSIPO, LOW);
      for(int k = 0; k < 12; k++) {
        digitalWrite(dataPinSIPO, !!(bin & (1 << k)));
        digitalWrite(clockPinSIPO, HIGH);
        digitalWrite(clockPinSIPO, LOW);
      }
      digitalWrite(latchPinSIPO, HIGH);
      
      state = -1;
      digitalWrite(latchPinPISO, LOW);
      digitalWrite(latchPinPISO, HIGH);
      incoming = shiftIn(dataPinPISO, clockPinPISO, MSBFIRST);
      if(state != -1)
        delay(brzina);
      else
        delay(500);
    }
  }
}

void binary(int x) {
  bin = 0;
  int temp;
  for(int i = 0; i < 3; i++) {
    if(i == state) {
      temp = random(0, 15);
      for(int j = 0; j < 4; j++) {
        bin <<= 1;
        bin |= temp % 2;
        temp /= 2;
      }
    } else {
      for(int j = 0; j < 4; j++) {
        if((i * 4 + j) % 4 == 0)
          temp = x;
        bin <<= 1;
        bin |= temp % 2;
        temp /= 2;
      }
    }
  }
  //Serial.println(bin, BIN);
}

void isr() {
  switch(incoming) {
    case 2:
      state = 0;
      Serial.println("Randomize first row");
      break;
    case 4:
      state = 1;
      Serial.println("Randomize second row");
      break;
    case 8:
      state = 2;
      Serial.println("Randomize third row");
      break;
    case 18:
    case 20:
    case 24:
      if(brzina == 100)
        return;
      brzina -= 5;
      Serial.print("Brzina = ");
      Serial.println(brzina);
      break;
    case 34:
    case 36:
    case 40:
      if(brzina == 300)
        return;
      brzina += 5;
      Serial.print("Brzina = ");
      Serial.println(brzina);
      break;
  }
}
