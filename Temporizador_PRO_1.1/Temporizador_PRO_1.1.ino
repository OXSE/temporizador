// include the library code:
#include <LiquidCrystal.h>

int tiempoOn = 8; // segundos
int tiempoOff = 1; // minutos
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
  segundos = 0;
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Temporizador");
  if(motorState == LOW){
    
    lcd.print(" Off");
  }else{
   lcd.print(" On ");
  }
  lcd.setCursor(0,1);
  lcd.print(minutos);
  lcd.print(':');
  lcd.print(segundos);
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   

    segundos = segundos + 1;
  }


  if(segundos == 60){
    segundos = 0;
    minutos = minutos + 1;
  }
  
  if (motorState == LOW){
      if(minutos == tiempoOff){
        minutos = 0;
        segundos = 0;
        motorState = HIGH;
        digitalWrite(motorPin, motorState);
        lcd.clear();
      }
    }  

  if (motorState == HIGH){
      if(segundos == tiempoOn){
        motorState = LOW;
        digitalWrite(motorPin, motorState);
        segundos = 0;
        minutos = 0;
        lcd.clear();
      }
    } 
  
}

