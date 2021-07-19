#include <Servo.h>  
#include <NewPing.h>
// connect motor controller pins to Arduino digital pins
// motor one
int enA = 7;
int in1 = 6;
int in2 = 5;
// motor two
int enB = 2;
int in3 = 4;
int in4 = 3;
// Turn speed
int ts = 170;
// Turn period
int tp = 250;
// No turn driving speed, motor A
int ntA = 130;
// No turn driving speed, motor B
int ntB = 155;



// Sonar1 setup
// defines pins numbers
const int trigPin = 10;
const int echoPin = 11;
// defines variables
long duration;
int distance;

// Sonar2 setup
// defines pins numbers
const int trig2Pin = 12;
const int echo2Pin = 13;
// defines variables
long duration2;
int distance2;

Servo servo_motor1; //our servo name
Servo servo_motor2; //our servo name

void setup()
{
// set all the motor control pins to outputs
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(trig2Pin, OUTPUT); // Sets the trig2Pin as an Output
pinMode(echo2Pin, INPUT); // Sets the echo2Pin as an Input
  servo_motor1.attach(8); //our servo pin
  servo_motor2.attach(9); //our servo pin

Serial.begin(9600); // Starts the serial communication
}

void loop()
{
// Find distance Sonar….
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distance);

// Find distance Sonar2….
// Clears the trigPin
digitalWrite(trig2Pin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig2Pin, HIGH);
delayMicroseconds(10);
digitalWrite(trig2Pin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echo2Pin, HIGH);
// Calculating the distance
distance2= duration2*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance2: ");
Serial.println(distance2);

//driving the robot
if (distance < 20 || distance2 < 20) { 
  stopMotors(); 
  delay (500); 
  servo_motor1.write(0);
  servo_motor2.write(180);
  delay (500); 
  servo_motor1.write(90);
  servo_motor2.write(90);
  delay (500); 
  return distance;
  if (distance < distance2) { 
    turnRight(); delay (1000); 
    } if (distance > distance2){ 
      turnLeft();
      delay (1000);
}

if (distance == distance2)
{ revers();
delay (1000);
}
}

if (distance > 20) forward();

}

void revers()
{
// turn on motor A
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
// set speed to ntA ***No turn driving speed, motor A***
analogWrite(enA, ntA);
// turn on motor B
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
// set speed to ntB ***No turn driving speed, motor B***
analogWrite(enB, ntB);
// digitalWrite(in4, LOW);
}
void forward()
{
// turn on motor A
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
// set speed to ntA ***No turn driving speed, motor A***
analogWrite(enA, ntA);
// turn on motor B
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
// set speed to ntB ***No turn driving speed, motor B***
analogWrite(enB, ntB);
// digitalWrite(in4, LOW);
}
void turnRight()
{
// turn on motor A
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
// set speed to ts ***Turn Speed***
analogWrite(enA, ts);
// turn on motor B
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
// set speed to ts ***Turn Speed***
analogWrite(enB, ts);
// Turn period
delay(tp);
// Stop motors
digitalWrite(in1, LOW);
digitalWrite(in4, LOW);
}
void turnLeft()
{
// turn on motor A
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
// set speed to ts ***Turn Speed***
analogWrite(enA, ts);
// turn on motor B
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
// set speed to ts ***Turn Speed***
analogWrite(enB, ts);
//Turn period
delay(tp);
// Stop motors
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
}
void stopMotors()
{
// Stop motors
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}
