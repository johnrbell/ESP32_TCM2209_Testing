#include <Arduino.h>


const int dirPin = 14;
const int stepPin = 15;
const int enPin = 27;

const int limit_ext = 25; //extend limit -  0 == short to ground
const int limit_ret = 33; //retract limit -  0 == short to ground

int direction = 1; // 0 = extend

void setup()
{
  Serial.begin(115200); delay(1000);
  Serial.println("welcome to flavortown. 🍌");

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(limit_ext, INPUT_PULLUP); //watch for limit shorting to ground
  pinMode(limit_ret, INPUT_PULLUP); //watch for limit shorting to ground

  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, direction);
}

void readLimits(){
  Serial.println("-");
  Serial.println(digitalRead(limit_ext));
  Serial.println(digitalRead(limit_ret));
}

void loop()
{
  // Serial.println("--------------");
  // Serial.print("Limit A Val: ");
  // Serial.println(digitalRead(limit_ext));
  // Serial.print("Limit B Val: ");
  // Serial.println(digitalRead(limit_ret));

  //send a... few pulses. 
  // for (int i=0; i<50000; i++){  
    // if(i % 100 == 0)
    // {
    //      Serial.println(i);
    // }    


    
    //actual pulse. 
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(75);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(75);    
  // }
    if (digitalRead(limit_ext)==0){       //if extend limit is hit
      Serial.print("Extend Limit Hit");
      delayMicroseconds(1000);
      digitalWrite(dirPin, 1);          //retract  
    } else if(digitalRead(limit_ret)==0){ //if retract limit is hit
      Serial.print("Retract Limit Hit");
      delayMicroseconds(1000);
      digitalWrite(dirPin, 0);          //extend
    }   

  // Swap Direction 💡
  // direction = (digitalRead(dirPin)==1) ? 0 : 1;
  // digitalWrite(dirPin, direction);
}