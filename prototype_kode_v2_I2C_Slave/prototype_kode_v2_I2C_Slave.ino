//Usabilitech Rainrow prototype kode I2C Slave IN1060 Vaar 2020
//Kode til Slave-arduino(styrer skjermen utifra data
//den mottar fra Master).

//IC2 Library
#include <Wire.h>

//LCD Library
#include <LiquidCrystal.h>

//Slaveadressen defineres
#define SLAVE_ADDR 9

//Variabel for data lest fra master
int lestData = 0;

//Variabler til og oppsett av LCD
int contrast = 20;
int contrastPin = 10;
LiquidCrystal lcd(12, 11, 5, 4, 6, 2);


void setup() {
  //Kontrasten paa LCDen settes
  analogWrite(contrastPin, contrast);

  //LCDen startes
  lcd.begin(16, 2);

  //IC2 Kommunikasjon til den andre arduinoen startes
  Wire.begin(SLAVE_ADDR);

  //Funksjonen receiveEvent kjoeres naar data mottas fra master
  Wire.onReceive(receiveEvent);
}

//Funksjonen reveiceEvent leser dataen sendt fra master
//og putter den i variabelen vi definerte for dette.
void receiveEvent() {
  lestData = Wire.read();
}

void loop() {
  //If sjekker for hva LCDen skal printe ut utifra hva som har
  //blitt innlest fra master
  if (lestData == 1) {
    lcd.clear();
    lcd.print("Spiller 1");
    //Posisjonen for utskrift settes til rad 2 paa LCDen
    lcd.setCursor(0, 1);
    lcd.print("sin tur");
    lestData = 0;
  }
  
  if (lestData == 2) {
    lcd.clear();
    lcd.print("Spiller 2");
    //Posisjonen for utskrift settes til rad 2 paa LCDen
    lcd.setCursor(0, 1);
    lcd.print("sin tur");
    lestData = 0;
  }

  if (lestData == 3) {
    lcd.clear();
    lcd.print("Spiller 1 vant!");
    //Posisjonen for utskrift settes til rad 2 paa LCDen
    lcd.setCursor(0, 1);
    lcd.print("Trykk for reset");
    lestData = 0;
  }

  if (lestData == 4) {
    lcd.clear();
    lcd.print("Spiller 2 vant!");
    //Posisjonen for utskrift settes til rad 2 paa LCDen
    lcd.setCursor(0, 1);
    lcd.print("Trykk for reset");
    lestData = 0;
  }  
}
