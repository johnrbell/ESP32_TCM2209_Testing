#include <Arduino.h>
#include "FastAccelStepper.h"
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include <SPI.h>

#define LED_PIN 2

const int enPin = 12;
const int stepPin = 14;
const int dirPin = 27;

const int limit_ext = 22; //extend limit -  0 == short to ground
const int limit_ret = 23; //retract limit -  0 == short to ground

int direction = 1; // 0 = extend

void setup()
{
  Serial.begin(115200); delay(1000);
  Serial.println("welcome to flavortown. 🍌");

  pinMode(LED_PIN, OUTPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(limit_ext, INPUT_PULLUP); //watch for limit shorting to ground (blk/wht for extend limit)
  pinMode(limit_ret, INPUT_PULLUP); //watch for limit shorting to ground (red/blu for retract limit)

  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, direction);
}

void loop()
{
  
    //actual pulse. 
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(75);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(75);    
  
    if (digitalRead(limit_ext)==0){       //if extend limit is hit
      Serial.print("Extend Limit Hit");
      delayMicroseconds(4000);
      digitalWrite(dirPin, 1);          //retract  
    } else if(digitalRead(limit_ret)==0){ //if retract limit is hit
      Serial.print("Retract Limit Hit");
      delayMicroseconds(4000);
      digitalWrite(dirPin, 0);          //extend
    }   

  // Swap Direction 💡
  // direction = (digitalRead(dirPin)==1) ? 0 : 1;
  // digitalWrite(dirPin, direction);
}