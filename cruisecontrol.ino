// Cruise Control

#include <Servo.h>
Servo myservo;

int Echo = A4;
int Trig = A5;

#define rightTracker !digitalRead(10)
#define midTracker !digitalRead(4)
#define leftTracker !digitalRead(2)
//speed of left and right motors
#define ENA 5
#define ENB 6
#define RR 7
#define RF 8
#define LF 9
#define LR 11
#define carSpeed 100
#define carSpeed2 70
#define turnSpeed 150

int midDistance = 0;
int setDist = 10;
int lane =2;

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(RR, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(LR, HIGH);
}

void forward2(){
  analogWrite(ENA, carSpeed2);
  analogWrite(ENB, carSpeed2);
  digitalWrite(RR, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(LR, HIGH);
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(RR, LOW);
  digitalWrite(RF, HIGH);
  digitalWrite(LF, HIGH);
  digitalWrite(LR, LOW);
}

void left(){
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(RR, LOW);
  digitalWrite(RF, HIGH);
  digitalWrite(LF, LOW);
  digitalWrite(LR, HIGH);
}

void right(){
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(RR, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(LF, HIGH);
  digitalWrite(LR, LOW); 
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
} 

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

void laneKeep(){
  if(leftTracker == 1){
      right();
      Serial.println("Keep in lane turn right");
      delay(190);

    }if(rightTracker == 1){
      left();
      Serial.println("Keep in lane turn left");
      delay(190);
    }
    if(midTracker == 1){
      right();
      delay(100);
    }
}

void laneChangeLeft(){
    left();
    delay(450);
    forward();
    delay(1000);
    lane = 1;
}

void laneChangeRight(){
    right();
    delay(450);
    forward();
    delay(1000);
    lane = 2;
}

void setup() {
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(10,INPUT);
  pinMode(2,INPUT);
  stop();
}


void loop() {
  // put your main code here, to run repeatedly:

  
  myservo.write(90);
  midDistance = Distance_test();
  Serial.print("Distance: ");
  Serial.println(midDistance);
  

  if(midDistance > 70){
    forward();
    laneKeep();
  }

  if(midDistance <= 50 && midDistance > 14){
    forward2();
    laneKeep();
  }

  if(midDistance <=14){
    /*
    lane = 1;
    left();
    Serial.println("Changing to left lane");
    delay(350);
    forward();
    delay(1000);

     if(leftTracker == 1){
      counter = counter + 1;
      Serial.println(counter);
    }

    if(counter < 2){
      forward();
    }else{
      laneKeep();
    }
    */
  if(lane ==2){
    laneChangeRight();
    left();
    delay(450);
    lane = 1;
  }else{
    laneChangeLeft();
    right();
    delay(400);
    lane = 2;
  }
  
    
  }
    /*
if(counter == 0 ){
      if(leftTracker == 1){
      right();
      Serial.println("Keep in lane turn right");
      delay(50);
      myservo.write(120);
    }
    if(rightTracker == 1){
      left();
      Serial.println("Keep in lane turn left");
      delay(50);
      myservo.write(60);
 }
}
*/
 /*
  if(midDistance <= 12 && lane == 1){
    
    lane = 2;
    right();
    Serial.println("Changing to right lane");
    delay(350);
    forward();
    delay(1000);
    if(rightTracker == 1){
      counter = counter -1;
    }

    if(counter > 0){
      forward();
    }else{
      laneKeep();
    }
    laneChangeRight();
    }
    */
/*
    if(counter == 2){
      if(leftTracker == 1){
      right();
      Serial.println("Keep in lane turn right");
      myservo.write(120);
    }else{
      left();
      Serial.println("Keep in lane turn left");
      myservo.write(60);
    }
    }
    */

}
