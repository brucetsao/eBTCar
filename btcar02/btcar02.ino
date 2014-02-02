/*
  Mega 2560 with L298N , Bluetooth HC-05
 
 Author: Brucetsao 
 */
const int Motor_PWM1 = 8; // digital pin 5 of Arduino (PWM)    
const int Motor_PWM2 = 9;  // digital pin 6 of Arduino (PWM)  
const int Motor_1A = 24;     // digital pin 7 of Arduino
const int Motor_1B = 25;     // digital pin 7 of Arduino
const int Motor_2A = 26;     // digital pin 7 of Arduino
const int Motor_2B = 27;     // digital pin 7 of Arduino
char val;  // variable to receive data from the serial port(bluetooth)
int val1;  // variable to receive data from the serial port(bluetooth)
//----define control key
#define forwardkey 70  
#define backrwardkey 66
#define leftkey 76
#define rightkey 82 
#define stopkey 68

void setup()  
{
  // Start serial communication at 57600
  Serial.begin(9600); 
  Serial1.begin(9600); 
  pinMode(Motor_1A, OUTPUT);
  pinMode(Motor_1B, OUTPUT);
  pinMode(Motor_2A, OUTPUT);
  pinMode(Motor_2B, OUTPUT);
  Serial.println("Start here");

}

void loop()
{
    
   if(Serial1.available())
   {
   val = Serial1.read();
   val1 = int(val) ;
   Serial.println("-----------");
   Serial.println(val1);
   Serial.println("----------------");

     switch(val1)
     {
       case forwardkey : // car forward
       Motorforward(255);
       break;
       case backrwardkey :   // car backward
       Motorbackward(255);
       break;
       case leftkey :   // car turn left
       Motorleft(255);
       break;
       case rightkey :   // car turn right
       Motorright(255);
       break;
       case stopkey :   // car stop
       Motorstop(0);
       break;
     }    
   }
 
}

void Motorstop(byte motorspeed)
 {
 Serial.println("Stop!");
 RightWheelStop() ;
 LeftWheelStop() ;
 SetSpeed(motorspeed);
 }
void Motorforward(byte motorspeed)
{
  Serial.println("Forward!");

  RightWheelFoward() ;
  LeftWheelFoward() ;
  SetSpeed(motorspeed);
}

void Motorbackward(byte motorspeed)
{
  Serial.println("Backward!");
  RightWheelBackward() ;
  LeftWheelBackward() ;
  SetSpeed(motorspeed);

}
void Motorright(byte motorspeed)
{
  Serial.println("New Turn Right! ");
  LeftWheelFoward() ;
  RightWheelBackward() ;
  SetSpeed(motorspeed);
}

void Motorleft(byte motorspeed)
{
  Serial.println("New Turn Left!");
  RightWheelFoward() ;
  LeftWheelBackward() ;
  SetSpeed(motorspeed);
}

void SetSpeed(byte motorspeed)
{
  analogWrite( Motor_PWM1, motorspeed );
  analogWrite( Motor_PWM2, motorspeed);
}
void RightWheelFoward()
{
  digitalWrite( Motor_1A, HIGH);
  digitalWrite( Motor_1B, LOW);
}
void LeftWheelFoward()
{
  digitalWrite( Motor_2A, HIGH);
  digitalWrite( Motor_2B, LOW);
}


void RightWheelBackward()
{
  digitalWrite( Motor_1A, LOW);
  digitalWrite( Motor_1B, HIGH );
}
void LeftWheelBackward()
{
  digitalWrite( Motor_2A, LOW);
  digitalWrite( Motor_2B, HIGH);
}

void RightWheelStop()
{
  digitalWrite( Motor_1A, LOW);
  digitalWrite( Motor_1B, LOW );
}
void LeftWheelStop()
{
  digitalWrite( Motor_2A, LOW);
  digitalWrite( Motor_2B, LOW);
}


