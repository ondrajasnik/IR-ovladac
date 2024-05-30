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
int currentLED = 0;

int codesSize = sizeof(codes) / sizeof(codes[0]);

String receivedNum(unsigned long irData) {
  for (int i = 0; i < codesSize; i++) {
    if (irData == codes[i]) {
      return String(i);
    }
  }
  return ""; 
}

void setLED(int value) {
  switch (currentLED) {
    case 0:
      Serial.print("Nastavuji Červenou LED: ");
      analogWrite(redLed, value);
      Serial.println(value);
      currentLED = 1;
      break;
    case 1:
      Serial.print("Nastavuji Zelenou LED: ");
      analogWrite(greenLed, value);
      Serial.println(value);
      currentLED = 2;
      break;
    case 2:
      Serial.print("Nastavuji Modrou LED: ");
      analogWrite(blueLed, value);
      Serial.println(value);
      currentLED = 0;
      break;
    default:
      Serial.println("Nesprávný stav LED");
      break;
  }
}

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.begin(9600);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.println("Setup dokončen");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long irData = IrReceiver.decodedIRData.decodedRawData;
    if (irData > 0) {
      if (irData == ENTER) {
        int intNum = stringNum.toInt();
        if (intNum >= 0 && intNum <= 255) {
          setLED(intNum);
          Serial.print("Nastavená hodnota: ");
          Serial.println(intNum);
          stringNum = "";
        } else {
          Serial.println("Mimo rozsah");
          stringNum = "";
        }
      } else {
        stringNum += receivedNum(irData);
        String ledName;
        switch (currentLED) {
          case 0:
            ledName = "Červená";
            break;
          case 1:
            ledName = "Zelená";
            break;
          case 2:
            ledName = "Modrá";
            break;
          default:
            ledName = "Neznámá";
            break;
        }
        Serial.print("LED: ");
        Serial.print(ledName);
        Serial.print(" Aktuální číslo: ");
        Serial.println(stringNum);
      }
    }

    IrReceiver.resume();
  }
}
