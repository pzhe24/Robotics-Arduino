// Parallel Parking

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
#define carSpeed 110
#define turnSpeed 150
#define parkSpeed 80

int midDistance = 0, leftDistance =0;
int setDist = 25;
int parkDist = 10;
bool hasRun = false;
int state = 0;


void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(RR, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(LR, HIGH);
}
void forward2(){
  analogWrite(ENA, parkSpeed);
  analogWrite(ENB, parkSpeed);
  digitalWrite(RR, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(LR, HIGH);
}

void back(){
  analogWrite(ENA, parkSpeed);
  analogWrite(ENB, parkSpeed);
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

void findPark(){
  myservo.write(180);
  leftDistance = Distance_test();
  Serial.print("Distance: ");
  Serial.println(leftDistance);
  if(leftDistance <setDist +5){
    forward();
  }else{
    stop();
  }
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


void setup() {
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(10,INPUT);
  pinMode(2,INPUT);
  stop();

  myservo.write(180);
  delay(200);
  leftDistance = Distance_test();
  delay(200);
  Serial.println(leftDistance);
  if(leftDistance < (setDist+10)){
    forward();
    Serial.println("going forward");
    delay(1000);
  }
  leftDistance = Distance_test();

  if(leftDistance < (setDist+10)){
    forward();
    Serial.println("going forward2");
    delay(500);
  }
  leftDistance = Distance_test();

  if(leftDistance < (setDist+10)){
    forward();
    Serial.println("going forward3");
    delay(300);
  }
  stop();
  Serial.println("stopping");

  left();
  delay(600);
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(hasRun == false){
  while(leftTracker == 0 && rightTracker == 0){
    forward2();
  }
  hasRun = true;
  }
  if(state ==0 ){
  if(leftTracker == 1){
    forward2();
    if(rightTracker == 1){
    forward();
    delay(280);
    stop();
    delay(300);
    right();
    state = 1;
  }
  }
  
  }

  if(state == 1){
  myservo.write(90);
  delay(525);
  midDistance = Distance_test();
  if(midDistance >= 12){
    forward2();
  }
  else{
    stop();
  }
  }
/*
if(midDistance > parkDist){
    forward2();
    delay(50);
  }if(midDistance <= parkDist){
    right();
    delay(200);
    back();
    delay(50);
    myservo.write(90);
    delay(200);
    parkMidDist = Distance_test();
    if(parkMidDist < parkDist){
      if(rightTracker == 1){
    left();
    delay(50);
  }
  if(leftTracker == 1){
    right();
    delay(50);
  }
  if(midTracker == 1){
    stop();
  }
    }
  }

*/



  
  /*
if(hasRun == false){
    forward();
    delay(850);
    left();
    delay(250);
    forward2();
    delay(1300);
    hasRun = true;
}

  myservo.write(40);
  delay(100);
  midDistance = Distance_test();
  delay(200);

 
  if(midDistance > parkDist){
    forward2();
    delay(50);
  }if(midDistance <= parkDist){
    right();
    delay(200);
    back();
    delay(50);
    myservo.write(90);
    delay(200);
    parkMidDist = Distance_test();
    if(parkMidDist < parkDist){
      stop();
    }
  }
  
  if(rightTracker == 1){
    left();
    delay(50);
  }
  if(leftTracker == 1){
    right();
    delay(50);
  }
  if(midTracker == 1){
    stop();
  }
*/
  
  /*
 myservo.write(180);
 delay(200);
 rightDistance = Distance_test();
 if(rightDistance > setDist +5){
  forward();
 }else{
  stop();
  hasRun = true;
 }

 

 if(hasRun == true){
 left();
 delay(300);
 forward();
 delay(500);
 hasRun = false;
 hasRun2 = true;
 }
if(hasRun2 == true){
 
 myservo.write(50);
 delay(200);
 midDistance = Distance_test();

  if(midDistance > parkDist){
    forward2();

    if(rightTracker == 1){
      left();
      delay(50);
    }
    else{
      right();
      delay(50);
    }
    stop();
  }else{
    hasRun2 = false; 
  }
}
*/

  /*
  if(midDistance == setDist){
    setDist = 0;
    stop();
    right();
    delay(50);
    myservo.write(120);
    delay(100);
    back();
    delay(80);

    if(rightTracker == HIGH){
      left();
    }else{
      right();
    }
  }

  if(midDistance = setDist+5){
    stop();
  }
  */





  

}
