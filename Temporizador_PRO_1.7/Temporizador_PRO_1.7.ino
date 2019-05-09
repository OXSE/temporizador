// include the library code:
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <avr/wdt.h>

int tiempoOn = 8; // segundos
int tiempoOff = 1; // minutos
int eepromTiempoOn = 10; 
int eepromTiempoOff = 11; 
const int motorPin =  1;      // the number of the LED pin
int subirEstado;
int bajarEstado;
int menuEstado;
const int subir = 11;
const int bajar = 12;
const int menu = 13;
int motorState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
int minutos = 0;
int segundos = 0;
int contadorMenu = 0;
const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //pin real: rs = 14, E = 13, D4 = 12, D5 = 11, D6 = 6, D7 = 2

void setup() {
  // ******************************************************** Watch Dog
  wdt_disable();    // Sumamente importante, para desabilitar el WDT
  // ******************************************************** Watch Dog
  pinMode(motorPin, OUTPUT);
  pinMode(subir, INPUT);
  pinMode(bajar,INPUT);
  pinMode(menu, INPUT);
  tiempoOn = EEPROM.read(eepromTiempoOn);
  tiempoOff = EEPROM.read(eepromTiempoOff);
  digitalWrite(motorPin, motorState);
  lcd.begin(16, 2);
  segundos = 0;
  // ******************************************************** Watch Dog
  wdt_enable(WDTO_8S); // habilitamos el reloj de arena a 8 segundos
  // ******************************************************** Watch Dog
}

void loop() {
  subirEstado = digitalRead(subir);
  bajarEstado = digitalRead(bajar);
  menuEstado = digitalRead(menu);
  if((subirEstado == LOW) && (bajarEstado == LOW) && (menuEstado == HIGH)){
    contadorMenu = contadorMenu + 1;
    delay(200);
    lcd.clear();
   }

   
    if(contadorMenu == 0){
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
   }
   
   if(contadorMenu == 1){
    lcd.setCursor(0, 0);
    lcd.print("Ajuste 1 de 2");
    lcd.setCursor(0, 1);
    lcd.print("Tiempo ON ");
    lcd.print(tiempoOn);
    lcd.print("s");
    if((subirEstado == HIGH) && (bajarEstado == LOW) && (menuEstado == LOW)){
      tiempoOn = tiempoOn + 1;
       delay(200);
       if(tiempoOn >= 60){
      tiempoOn = 0;
      lcd.clear();
   }
   }

    if((subirEstado == LOW) && (bajarEstado == HIGH) && (menuEstado == LOW)){
      tiempoOn = tiempoOn - 1;
      delay(200);
      if(tiempoOn <= 0){
      tiempoOn = 59;
      lcd.clear();
     }
    }  
   }   
   if(contadorMenu == 2){
    lcd.setCursor(0, 0);
    lcd.print("Ajuste 2 de 2");
    lcd.setCursor(0, 1);
    lcd.print("Tiempo Off ");
    lcd.print(tiempoOff);
    lcd.print("m");

    if((subirEstado == HIGH) && (bajarEstado == LOW) && (menuEstado == LOW)){
      tiempoOff = tiempoOff + 1;
       delay(200);
       if(tiempoOff >= 256){
      tiempoOff = 0;
       lcd.clear();
   }
   }

    if((subirEstado == LOW) && (bajarEstado == HIGH) && (menuEstado == LOW)){
      tiempoOff = tiempoOff - 1;
      delay(200);
       if(tiempoOff <= 0){
       tiempoOff = 255;
       lcd.clear();
   }
   }
   }
  
 
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    // ******************************************************** Watch Dog 
  wdt_reset(); // sino regreso en 8 segundos llama a reset
 // ******************************************************** Watch Dog
    segundos = segundos + 1;
   
  }


  if(segundos == 60){
    segundos = 0;
    minutos = minutos + 1;
    tiempoOn = EEPROM.read(eepromTiempoOn);
    tiempoOff = EEPROM.read(eepromTiempoOff);
    lcd.begin(16, 2);
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
    if(contadorMenu == 3){
      contadorMenu = 0;
      EEPROM.write(eepromTiempoOn, tiempoOn);
      EEPROM.write(eepromTiempoOff,tiempoOff);
      lcd.setCursor(0, 0);
      lcd.print("Guardado!");
      delay(1000);
      lcd.clear();
    }
    
  // ******************************************************** Watch Dog 
  wdt_reset(); // sino regreso en 8 segundos llama a reset
 // ******************************************************** Watch Dog
 
}
 
