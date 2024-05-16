#include <Arduino.h>
#include <IRremote.hpp>

#define IR_USE_AVR_TIMER 1
#define IR_RECEIVE_PIN 12
#define ENTER 4127850240 // Kód klávesy ENTER
#define redLed 6
#define greenLed 5
#define blueLed 9

unsigned long codes[] = {
    3910598400, // 0
    4077715200, // 1
    3877175040, // 2
    2707357440, // 3
    4144561920, // 4
    3810328320, // 5
    2774204160, // 6
    3175284480, // 7
    2907897600, // 8
    3041591040, // 9
};

String stringNum = "";
int currentLED = 0; // 0 = red, 1 = green, 2 = blue

int codesSize = sizeof(codes) / sizeof(codes[0]); // Zjištění počtu prvků v poli codes

String receivedNum(unsigned long irData) {
  for (int i = 0; i < codesSize; i++) {
    if (irData == codes[i]) {
      return String(i);
    }
  }
  return ""; // Pokud kód neodpovídá žádnému číslu, vrátí prázdný řetězec
}

void setLED(int value) {
  switch (currentLED) {
    case 0:
      analogWrite(redLed, value);
      Serial.print("Červená LED: ");
      Serial.println(value);
      currentLED = 1; // Přepnutí na další LED
      break;
    case 1:
      analogWrite(greenLed, value);
      Serial.print("Zelená LED: ");
      Serial.println(value);
      currentLED = 2; // Přepnutí na další LED
      break;
    case 2:
      analogWrite(blueLed, value);
      Serial.print("Modrá LED: ");
      Serial.println(value);
      currentLED = 3; // Přepnutí na další LED
      break;
    default:
      Serial.println("Nesprávný stav LED");
      break;
  }
}

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializace přijímače
  Serial.begin(9600); // Inicializace seriové komunikace

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.println("Setup dokončen");
}

void loop() {
  if (IrReceiver.decode()) { // Kontrola, zda přišla data z přijímače
    unsigned long irData = IrReceiver.decodedIRData.decodedRawData; // Uložení kódu z přijímače do irData
    if (irData > 0) { // Kontrola falešných kódů
      Serial.print("Přijatý kód: ");
      Serial.println(irData); // Výpis kódu na seriovou linku
      if (irData == ENTER) { // Pokud je zmáčknut ENTER
        int intNum = stringNum.toInt(); // Přetypování String na int
        if (intNum >= 0 && intNum <= 255) { // Kontrola rozsahu vstupního čísla
          setLED(intNum);
          Serial.print("Nastavená hodnota: ");
          Serial.println(intNum); // Výpis nastavené hodnoty do Serial monitoru
          stringNum = ""; // Vyčištění nastřádaného čísla
        } else {
          Serial.println("Mimo rozsah");
          stringNum = ""; // Vyčištění nastřádaného čísla
        }
      } else { // Funkce pro střádání čísel
        stringNum += receivedNum(irData);
        Serial.print("Aktuální číslo: ");
        Serial.println(stringNum); // Výpis aktuálního nastřádaného čísla do Serial monitoru
      }
    }

    IrReceiver.resume(); // Povolení přijímání dalšího signálu
  }
}