#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_P1 A0
#define TRIG_P2 A1 
#define ECHO_P1 A2
#define ECHO_P2 A3 
#define MAX_DISTANCE 25
#define MAX_SPEED 250 // sets speed of DC  motors

boolean goesForward=false;
int distanceR = 100;
int distanceL = 100;
int speedSet = 0;

AF_DCMotor motor1(8, MOTOR12_1KHZ); 
AF_DCMotor motor2(9, MOTOR12_1KHZ);

Servo servoL;
Servo servoR;

NewPing sonar1(TRIG_P1, ECHO_P1, MAX_DISTANCE); 
NewPing sonar2(TRIG_P2, ECHO_P2, MAX_DISTANCE); 

void setup()
{
//pinMode(motor1, OUTPUT);
//pinMode(motor2, OUTPUT);
//pinMode(TRIG_P1, OUTPUT); 
//pinMode(ECHO_P1, INPUT);
//pinMode(TRIG_P2, OUTPUT); 
//pinMode(ECHO_P2, INPUT);
//Serial.begin(9600);
//while (! Serial);
servoL.attach(11);  
servoR.attach(12);
servoL.write(115); 
servoR.write(115);
delay(2000);
distanceL = readPing(sonar1);
distanceR = readPing(sonar2);
delay(100);
distanceL = readPing(sonar1);
distanceR = readPing(sonar2);
delay(100);
}

void loop()
{
// int distanceR = 0;
// int distanceL =  0;
// delay(40);
 
 if(distanceL || distanceR <=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  ////////look side/////////
  servoL.write(170); 
  servoR.write(50); 
  delay(500);
  distanceL = readPing(sonar1);
  distanceR = readPing(sonar2);
  delay(100);
  servoR.write(115); 
  servoL.write(115);
  delay(200);
  /////////////////////////
  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else if(distanceR<=distanceL)
  {
    turnLeft();
    moveStop();
  }
 }
 else
 {
  moveForward();
 }
 
distanceL = readPing(sonar1);
distanceR = readPing(sonar2);
delay(100);
}

int readPing(NewPing sonar) { 
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
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);   
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD); 
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);   
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);  
  
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}  
