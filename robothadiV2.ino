/* Obstacle Avoiding Robot Using Ultrasonic Sensor and Arduino NANO
 *  Circuit Digest(www.circuitdigest.com)
 */
#include <Servo.h>

int trigPin1 = 10;      // trig pin of HC-SR04 kiri
int echoPin1 = 11;     // Echo pin of HC-SR04 kiri
int trigPin2 = 12;      // trig pin of HC-SR04 kanan
int echoPin2 = 13;     // Echo pin of HC-SR04 kanan

int revleft4 = 4;       //REVerse motion of Left motor
int fwdleft5 = 5;       //ForWarD motion of Left motor
int revright6 = 6;      //REVerse motion of Right motor
int fwdright7 = 7;      //ForWarD motion of Right motor

long duration1, distance1, duration2, distance2;

Servo servoL;
Servo servoR;

void setup() {
  
  delay(random(500,2000));   // delay for random time
  Serial.begin(9600);
  pinMode(revleft4, OUTPUT);      // set Motor pins as output
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT);
  
  pinMode(trigPin1, OUTPUT);         // set trig pin as output
  pinMode(echoPin1, INPUT);          //set echo pin as input to capture reflected waves
  pinMode(trigPin2, OUTPUT);         // set trig pin as output
  pinMode(echoPin2, INPUT);          //set echo pin as input to capture reflected waves

  servoL.attach(8);  
  servoR.attach(9);
  servoL.write(115); 
  servoR.write(115);
  delay(1000);
}

void loop() {

  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin1, HIGH);     // send waves for 10 us
  digitalWrite(trigPin2, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration1 = pulseIn(echoPin1, HIGH); // receive reflected waves 1
  duration2 = pulseIn(echoPin2, HIGH); // receive reflected waves 2
  distance1 = duration1 / 58.2;   // convert to distance 1
  distance2 = duration2 / 58.2;   // convert to distance 2
  delay(10);
  Serial.println("distance 1 = " + distance1);
  Serial.println("distance 2 = " + distance2); 
  delay(10);
    // If you dont get proper movements of your robot then alter the pin numbers
  if(distance1 || distance2 >=20)
 {
    Forward();                                                     
  }

  if (distance1 || distance2 < 20)
  {
    Stop();
    delay(200);
    Backward();
    delay(200);
    Stop();
    delay(200);
    /////////////////////////////////////////
    servoL.write(170); 
    servoR.write(50); 
    delay(500);
    digitalWrite(trigPin1, LOW);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);   
    digitalWrite(trigPin1, HIGH);     // send waves for 10 us
    digitalWrite(trigPin2, HIGH);     // send waves for 10 us
    delayMicroseconds(10);
    duration1 = pulseIn(echoPin1, HIGH); // receive reflected waves 1
    duration2 = pulseIn(echoPin2, HIGH); // receive reflected waves 2
    distance1 = duration1 / 58.2;   // convert to distance 1
    distance2 = duration2 / 58.2;   // convert to distance 2
    delay(10);
    Serial.println("distance 1 = " + distance1);
    Serial.println("distance 2 = " + distance2); 
    delay(200);
    servoR.write(115); 
    servoL.write(115);
    delay(500);
    ////////////////////////////////////////
    
    if(distance1 > distance2){
      TLeft();
      } 
    else if(distance1 < distance2){
      TRight();
      }
      else{
      TRight();  
      }
    delay(500);
  }

}

  void Forward(){
    digitalWrite(fwdright7, HIGH);   // move forward
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);  
  }

  void Backward(){
    digitalWrite(fwdright7, LOW);  //movebackword         
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH); 
  }

  void Stop(){
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
  }

  void TRight(){
    digitalWrite(fwdright7, HIGH);       
    digitalWrite(revright6, LOW);   
    digitalWrite(revleft4, LOW);                                 
    digitalWrite(fwdleft5, LOW); 
    }
    
  void TLeft(){
    digitalWrite(fwdright7, LOW);       
    digitalWrite(revright6, LOW);   
    digitalWrite(revleft4, LOW);                                 
    digitalWrite(fwdleft5, HIGH); 
    }
