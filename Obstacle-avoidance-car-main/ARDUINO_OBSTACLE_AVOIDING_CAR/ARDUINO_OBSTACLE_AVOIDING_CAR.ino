//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1   //超声探测器的引脚
#define MAX_DISTANCE 200 
#define MAX_SPEED 250// sets speed of DC  motors
#define MAX_SPEED_OFFSET 245

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_64KHZ); 
//1AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
//AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(10);  
  myservo.write(80); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=15)
 {
  moveStop();
  delay(200);
  moveBackward();
  delay(1000);
  moveStop();
  delay(300);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(20); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(80); 
    return distance;
}

int lookLeft()
{
    myservo.write(160); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(80); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  //motor2.run(RELEASE);
 motor3.run(RELEASE);
  //motor4.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    //motor2.run(FORWARD);
    motor3.run(FORWARD); 
    //motor4.run(FORWARD);     
   for (speedSet = 30; speedSet <= MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    //motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    //motor4.setSpeed(speedSet);
    delay(10);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    //motor2.run(BACKWARD);
   motor3.run(BACKWARD);
   // motor4.run(BACKWARD);  
  for (speedSet = 30; speedSet <=MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    //motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
   //motor4.setSpeed(speedSet);
    delay(10);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  //motor2.run(FORWARD);
 motor3.setSpeed(150);
 motor3.run(BACKWARD); 
  //motor4.run(BACKWARD);     
  delay(5000);
  motor1.run(FORWARD);      
  //motor2.run(FORWARD);
  //motor3.run(FORWARD);
  //motor4.run(FORWARD);      
} 
 
void turnLeft() {
  
 motor1.run(BACKWARD);    
  //motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  //motor4.run(FORWARD);   
  delay(5000);
  //Qmotor1.run(FORWARD);     
  //motor2.run(FORWARD);
  motor3.run(FORWARD);
  //motor4.run(FORWARD);
}  
