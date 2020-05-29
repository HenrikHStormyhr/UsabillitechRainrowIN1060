//Usabilitech Rainrow prototype kode I2C Master IN1060 Vaar 2020
//Kode til Master-arduino(har alle knapper og holder
//styr paa spillbrettet)

//Ting til I2C (kommunikasjon til skjermen paa den andre arduinoen)
#include <Wire.h>
int dataSomSendes = 0;

//Variabler
//Knapper
int knapp1 = 2;
int knapp2 = 3;
int knapp3 = 4;
int knapp4 = 5;
int knapp5 = 6;
int knapp6 = 7;
int knapp7 = 8;
int knapp8 = 9;
int knapp9 = 10;

//Bytt spiller knapp
int byttSpillerKnapp = 11;

//Hvem sin tur
int hvemSinTur = 1;

//Ruter Spiller 1
bool rute1S1 = false;
bool rute2S1 = false;
bool rute3S1 = false;
bool rute4S1 = false;
bool rute5S1 = false;
bool rute6S1 = false;
bool rute7S1 = false;
bool rute8S1 = false;
bool rute9S1 = false;

//Ruter Spiller 2
bool rute1S2 = false;
bool rute2S2 = false;
bool rute3S2 = false;
bool rute4S2 = false;
bool rute5S2 = false;
bool rute6S2 = false;
bool rute7S2 = false;
bool rute8S2 = false;
bool rute9S2 = false;

//debounce
unsigned long tid;
unsigned long sistTrykket = 5000;
int knappStatus = LOW;
long gangerTrykket = 0;

//Input loop variabler
int inputMin = 2;
int inputMax = 11;

//Hvem sin tur null variabel
bool hvemSinTurNullVar = false;

//nyttSpill variabel
bool nyttSpill = false;

//Spiller 1 sin tur print variabel
bool spiller1Print = true;

//Spiller 2 sin tur print variabel
bool spiller2Print = false;

void setup() {
  //Starter Serial for debug
  Serial.begin(9600);
  //Setter pinmodes til alle knappene med for loop
  for (int i = inputMin; i<=inputMax; i++) {
    pinMode(i, INPUT);
  }

  //I2C Tilkoblingen med den andre arduinoen startes
  Wire.begin();
}

void loop() {
  tid = millis();

  //Nar spillet er ferdig
  while (hvemSinTur == 0) {
    tid = millis();
    
    //Printer ut at spillet er ferdig en gang
    if (hvemSinTurNullVar == true) {
      spiller1Print = false;
      spiller2Print=false;
      Serial.println("Spillet er ferdig. Klikk paa boksknappen for aa starte et nytt spill.");
      hvemSinTurNullVar = false;
      nyttSpill = true;
    }

  //Bytt-spiller knapp med debounce
  if (digitalRead(byttSpillerKnapp) == HIGH) {
     if (gangerTrykket == 0){
      sistTrykket = tid;
      gangerTrykket++;
      hvemSinTur = 1;

      if (nyttSpill == true) {
      //Variabler resettes
      hvemSinTurNullVar = false;
      //Spiller 1
      rute1S1 = false;
      rute2S1 = false;
      rute3S1 = false;
      rute4S1 = false;
      rute5S1 = false;
      rute6S1 = false;
      rute7S1 = false;
      rute8S1 = false;
      rute9S1 = false;
      spiller1Print = true;
      //Spiller 2
      rute1S2 = false;
      rute2S2 = false;
      rute3S2 = false;
      rute4S2 = false;
      rute5S2 = false;
      rute6S2 = false;
      rute7S2 = false;
      rute8S2 = false;
      rute9S2 = false;
      spiller2Print = false;
      Serial.println("Nytt spill startet.");
      }
    }
     if (sistTrykket + 500 < tid) {
      sistTrykket = tid;
      gangerTrykket++;
      hvemSinTur = 1;
      //Variabler resettes
      if (nyttSpill == true) {
      hvemSinTurNullVar = false;
      //Spiller 1
      rute1S1 = false;
      rute2S1 = false;
      rute3S1 = false;
      rute4S1 = false;
      rute5S1 = false;
      rute6S1 = false;
      rute7S1 = false;
      rute8S1 = false;
      rute9S1 = false;
      spiller1Print = true;
      //Spiller 2
      rute1S2 = false;
      rute2S2 = false;
      rute3S2 = false;
      rute4S2 = false;
      rute5S2 = false;
      rute6S2 = false;
      rute7S2 = false;
      rute8S2 = false;
      rute9S2 = false;
      spiller2Print = false;
      Serial.println("Nytt spill startet.");
      }
    }
  }
  }

  //Nar det er spiller 1 sin tur
  while (hvemSinTur == 1) {
    tid = millis();
    if (spiller1Print == true) {
      
      //Vi sender data til LCD arduinoen
      dataSomSendes = 1;
      Wire.beginTransmission(9);
      Wire.write(dataSomSendes);
      Wire.endTransmission();
      
      Serial.println("Spiller 1 sin tur.");
      spiller1Print = false;
    }

    
  //Sjekker om en knapp blir trykket og oppdaterer ruten.
  if (digitalRead(knapp1) == HIGH) {
    rute1S1 = true;
  }
    if (digitalRead(knapp2) == HIGH) {
    rute2S1 = true;
  }
    if (digitalRead(knapp3) == HIGH) {
    rute3S1 = true;
  }
    if (digitalRead(knapp4) == HIGH) {
    rute4S1 = true;
  }
    if (digitalRead(knapp5) == HIGH) {
    rute5S1 = true;
  }
    if (digitalRead(knapp6) == HIGH) {
    rute6S1 = true;
  }
    if (digitalRead(knapp7) == HIGH) {
    rute7S1 = true;
  }
    if (digitalRead(knapp8) == HIGH) {
    rute8S1 = true;
  }
    if (digitalRead(knapp9) == HIGH) {
    rute9S1 = true;
  }

  //Sjekker om 3 paa rad.
  if (rute1S1 == true && rute2S1 == true && rute3S1 == true ||
      rute4S1 == true && rute5S1 == true && rute6S1 == true ||
      rute7S1 == true && rute8S1 == true && rute9S1 == true ||
      rute1S1 == true && rute4S1 == true && rute7S1 == true ||
      rute2S1 == true && rute5S1 == true && rute8S1 == true ||
      rute3S1 == true && rute6S1 == true && rute9S1 == true ||
      rute1S1 == true && rute5S1 == true && rute9S1 == true ||
      rute3S1 == true && rute5S1 == true && rute7S1 == true) {
        //Hvis 3 paa rad printes dette
        Serial.println("Spiller 1 har 3 paa rad");

        //Vi sender data til LCD arduinoen
        dataSomSendes = 3;
        Wire.beginTransmission(9);
        Wire.write(dataSomSendes);
        Wire.endTransmission();
        
        hvemSinTurNullVar = true;
        hvemSinTur = 0;
  }

  //Bytt-spiller knapp med debounce
  if (digitalRead(byttSpillerKnapp) == HIGH) {
     if (gangerTrykket == 0) {
      sistTrykket = tid;
      gangerTrykket++;
      spiller2Print = true;
      spiller1Print = false;
      hvemSinTur = 2;
    }
     if (sistTrykket + 500 < tid) {
      sistTrykket = tid;
      gangerTrykket++;
      spiller2Print = true;
      spiller1Print = false;
      hvemSinTur = 2;
    }
  }
  }

  //Spiller 2 sin tur
  while (hvemSinTur == 2) {
    tid = millis();
    
      if (spiller2Print == true) {

        //Vi sender data til LCD arduinoen
        dataSomSendes = 2;
        Wire.beginTransmission(9);
        Wire.write(dataSomSendes);
        Wire.endTransmission();
        
        Serial.println("Spiller 2 sin tur.");
        spiller2Print = false;
    }
    
  //Sjekker om en knapp blir trykket og oppdaterer ruten.
  if (digitalRead(knapp1) == HIGH) {
    rute1S2 = true;
  }
    if (digitalRead(knapp2) == HIGH) {
    rute2S2 = true;
  }
    if (digitalRead(knapp3) == HIGH) {
    rute3S2 = true;
  }
    if (digitalRead(knapp4) == HIGH) {
    rute4S2 = true;
  }
    if (digitalRead(knapp5) == HIGH) {
    rute5S2 = true;
  }
    if (digitalRead(knapp6) == HIGH) {
    rute6S2 = true;
  }
    if (digitalRead(knapp7) == HIGH) {
    rute7S2 = true;
  }
    if (digitalRead(knapp8) == HIGH) {
    rute8S2 = true;
  }
    if (digitalRead(knapp9) == HIGH) {
    rute9S2 = true;
  }

  //Sjekker om 3 paa rad.
  if (rute1S2 == true && rute2S2 == true && rute3S2 == true ||
      rute4S2 == true && rute5S2 == true && rute6S2 == true ||
      rute7S2 == true && rute8S2 == true && rute9S2 == true ||
      rute1S2 == true && rute4S2 == true && rute7S2 == true ||
      rute2S2 == true && rute5S2 == true && rute8S2 == true ||
      rute3S2 == true && rute6S2 == true && rute9S2 == true ||
      rute1S2 == true && rute5S2 == true && rute9S2 == true ||
      rute3S2 == true && rute5S2 == true && rute7S2 == true) {
        //Hvis 3 paa rad printes dette
        Serial.println("Spiller 2 har 3 paa rad");

        //Vi sender data til LCD arduinoen
        dataSomSendes = 4;
        Wire.beginTransmission(9);
        Wire.write(dataSomSendes);
        Wire.endTransmission();
        
        hvemSinTurNullVar = true;
        hvemSinTur = 0;
  }

  //Bytt-spiller knapp med debounce
  if (digitalRead(byttSpillerKnapp) == HIGH) {
    if (gangerTrykket == 0) {
      sistTrykket = tid;
      gangerTrykket++;
      spiller1Print = true;
      spiller2Print = false;
      hvemSinTur = 1;
    }
    if (sistTrykket + 500 < tid) {
      sistTrykket = tid;
      gangerTrykket++;
      spiller1Print = true;
      spiller2Print = false;
      hvemSinTur = 1;
    }
  }
  }
}
