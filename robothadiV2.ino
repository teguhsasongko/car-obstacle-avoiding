#include <Servo.h> //Servo motor library
#include <NewPing.h> //Ultrasonic sensor function library

const int LeftForward = 5;// L298N control pins
const int LeftBackward = 5;
const int RightForward = 4;
const int RightBackward = 3;

#define trig_pin 10 //sensor pins - analog input 1
#define echo_pin 11 //analog input 2
#define trig_pin2 12 //sensor pins - analog input 1
#define echo_pin2 13 //analog input 2
#define maximum_distance 200

boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //servo name
Servo servo_motor2; //servo name
void setup(){
  pinMode(RightForward, OUTPUT);
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBackward, OUTPUT);
  pinMode(RightBackward, OUTPUT);
  servo_motor.attach(8); //servo pin
  servo_motor2.attach(9); //servo pin
  servo_motor.write(115);
  servo_motor2.write(50);
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

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
   if (distance <= 20){
    moveStop(); // obstacle probably on the route forward, so stop
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    Serial.println("distance = " + distanceRight); 

    if (distance >= distanceLeft){
      turnRight(); // calculate in which direction the obstacle is more far
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  servo_motor2.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  servo_motor2.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  servo_motor2.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  servo_motor2.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  digitalWrite(RightForward, LOW);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightBackward, LOW);
  digitalWrite(LeftBackward, LOW);
}

void moveForward(){
  if(!goesForward){
    goesForward=true;
    digitalWrite(LeftForward, HIGH);
    digitalWrite(RightForward, HIGH);
    digitalWrite(LeftBackward, LOW);
    digitalWrite(RightBackward, LOW); 
  }
}

void moveBackward(){
  goesForward=false;
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightBackward, HIGH);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightForward, LOW);
}

void turnRight(){
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightBackward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightForward, LOW);
  delay(500);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightBackward, LOW);
}

void turnLeft(){
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightBackward, LOW);
  delay(500);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightBackward, LOW);
}
