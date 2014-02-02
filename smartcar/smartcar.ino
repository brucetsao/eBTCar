/*
  Motoduino : Arduino with motors driver
  
   author: http://motoduino.com - Feb. 2012
*/
#include <Servo.h>

Servo servoHor;          // Define left servo
Servo servoVer;         // Define right servo
const int Motor_E1 = 5; // digital pin 5 of Arduino (PWM)    
const int Motor_E2 = 6;  // digital pin 6 of Arduino (PWM)  
const int Motor_M1 = 7;     // digital pin 7 of Arduino
const int Motor_M2 = 8;    // digital pin 8 of Arduino
char val;  // variable to receive data from the serial port(bluetooth)

int servoHorPos, servoVerPos;

void setup()  
{
  // Start serial communication at 57600
  Serial.begin(9600); 
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);

  servoHor.attach(10);  // Set left servo to digital pin 10
  servoVer.attach(9);  // Set right servo to digital pin 9
  servoHorPos = servoVerPos = 90;
}

void loop()
{
  if(Serial.available())
  {
    val = Serial.read();
    switch(val)
    {
       case 'f':   // car forward
                forward(0, 255);
                break;
      case 'b':   // car backward
                backward(0, 255);
                break;
      case 'l':   // car turn left
                left(0, 255);
                break;
      case 'r':   // car turn right
                right(0, 255);
                break;
      case 's':   // car stop
                motorstop(0, 0);
                break;
      case 'w':   // ServoVer Forward
                servoHorPos = servoHorPos - 10;
                servoForward(servoHorPos);
                break;
      case 'x':   // ServoVer Backward
                servoHorPos = servoHorPos + 10;
                servoBackward(servoHorPos);
                break;
      case 'y':   // ServoHor turn left
                servoVerPos = servoVerPos + 10;
                servoLeft(servoVerPos);
                break;
      case 'z':   // ServoHor turn right
                servoVerPos = servoVerPos - 10;
                servoRight(servoVerPos);
                break;
      case 'o':   // ServoHor & ServoVer Original Position
                stopRobot();
                break;
    }    
    
  }

}

// Motion routines for forward, reverse, turns, and stop
void servoBackward(int deg) {
  Serial.println("servoBackward!");
  if(deg < 10)
     deg = 10;
  servoVer.write(deg);
}

void servoForward(int deg) {
  Serial.println("servoForward!");
  if(deg > 160)
     deg = 160;
  servoVer.write(deg);
}

void servoLeft(int deg) {
  if(deg < 10)
     deg = 10;
  servoHor.write(deg);
  Serial.println("servoLeft!");
}
void servoRight(int deg) {
    if(deg > 160)
     deg = 160;
  servoHor.write(deg);
  Serial.println("servoRight!");
}

void stopRobot() {
  servoHor.write(90);
  servoVer.write(90);
}

void motorstop(byte flag, byte motorspeed)
{
  Serial.println("Stop!");
  digitalWrite( Motor_E1, motorspeed);
  digitalWrite( Motor_E2, motorspeed);

}

void forward(byte flag, byte motorspeed)
{
  Serial.println("Forward!");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
  
}

void backward(byte flag, byte motorspeed)
{
  Serial.println("Backward!");

  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
   
}

void right(byte flag, byte motorspeed)
{
  Serial.println("Turn Right! ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, 0);
  
}

void left(byte flag, byte motorspeed)
{
  Serial.println("Turn Left!");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, motorspeed);
  
}

