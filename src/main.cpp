#include <Arduino.h>

const int dirPin = 14;
const int stepPin = 15;
const int enPin = 27;

const int limit_a = 25; //extend limit -  0 == short to ground
const int limit_b = 33; //retract limit -  0 == short to ground

int direction = 0; //extend by default. 

void setup()
{
  Serial.begin(115200); delay(1000);
  Serial.println("welcome to flavortown. 🍌");

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(limit_a, INPUT_PULLUP); //watch for limit shorting to ground
  pinMode(limit_b, INPUT_PULLUP); //watch for limit shorting to ground

  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, direction);
}

void readLimits(){
  Serial.println("-");
  Serial.println(digitalRead(limit_a));
  Serial.println(digitalRead(limit_b));
}

void loop()
{
  // Serial.println("--------------");
  // Serial.print("Limit A Val: ");
  // Serial.println(digitalRead(limit_a));
  // Serial.print("Limit B Val: ");
  // Serial.println(digitalRead(limit_b));

  //send a... few pulses. 
  for (int i=0; i<30000; i++){  
    if (digitalRead(limit_a)==0){       //if extend limit is hit
      Serial.print("Extend Limit Hit");
      digitalWrite(dirPin, 1);          //retract   
    } else if(digitalRead(limit_b)==0){ //if retract limit is hit
      Serial.print("Retract Limit Hit");
      digitalWrite(dirPin, 0);          //extend
    }   
    
    //actual pulse. 
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(50);    
  }

  // Swap Direction if all else... works? 
  direction = (digitalRead(dirPin)==1) ? 0 : 1;
  digitalWrite(dirPin, direction);
}