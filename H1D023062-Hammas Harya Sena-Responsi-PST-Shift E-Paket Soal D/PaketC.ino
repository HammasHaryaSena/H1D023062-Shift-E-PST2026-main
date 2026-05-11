#include <Servo.h>

Servo myservo; 

const int servoPin = 9;  
const int ledPin1 = 4;
const int ledPin2 = 5;
const int btnUp = 3;     

bool State = HIGH;
int timeDelay = 1000; 

void setup() {
  myservo.attach(servoPin);

  Serial.begin(9600);
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
}

void loop() {

  bool State = digitalRead(btnUp);
  if(State == HIGH)
  {
    digitalWrite(ledPin1, HIGH); 
    digitalWrite(ledPin2, HIGH); 
    myservo.write(90);
    delay(timeDelay); 
  }
  Else if(State == LOW){
    // Matikan LED 
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin2, LOW); 
    myservo.write(0);
    delay(timeDelay); 
  }
  delay(100);
}
