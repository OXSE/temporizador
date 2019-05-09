// include the library code:
#include <LiquidCrystal.h>

int tiempoOn;
int tiempoOff;
const int motorPin =  2;      // the number of the LED pin
int motorState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
int minutos = 0;
int segundos = 0;
const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //pin real: rs = 14, E = 13, D4 = 12, D5 = 11, D6 = 6, D7 = 2

void setup() {
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, motorState);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Temporizador");
  //lcd.print();
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    
    if (motorState == LOW)
      motorState = HIGH;
    else
      motorState = LOW;
      
    digitalWrite(motorPin, motorState);
    segundos = segundos + 1;
  }

  if(segundos == 60){
    segundos = 0;
    minutos = 1;
  }
  
}

