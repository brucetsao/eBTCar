/*
  Mega 2560 with L298N , Bluetooth HC-05
 
 Author: Brucetsao 
 */
#define Motorspeed 230
#define Motorspeed2 150
#define Stopspeed 0 

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

#define Trsensor1 30 
#define Trsensor2 31 
#define Trsensor3 32 
#define Trsensor4 33 

int Sensorval1 = 0 ;  // variable to receive data from the Track_Sensor 
int Sensorval2 = 0 ;  // variable to receive data from the Track_Sensor 
int Sensorval3 = 0 ;  // variable to receive data from the Track_Sensor 
int Sensorval4 = 0 ;  // variable to receive data from the Track_Sensor 

void setup()  
{
  // Start serial communication at 9600 bps
  Serial.begin(9600); 
  Serial1.begin(9600); 
  //L298N use
  pinMode(Motor_1A, OUTPUT);
  pinMode(Motor_1B, OUTPUT);
  pinMode(Motor_2A, OUTPUT);
  pinMode(Motor_2B, OUTPUT);
   //  Track Sensor use
  pinMode(Trsensor1, INPUT);
  pinMode(Trsensor2, INPUT);
  pinMode(Trsensor3, INPUT);
  pinMode(Trsensor4, INPUT);
  Serial.println("Start here");

}

void loop()
{
   Sensorval1 = digitalRead(Trsensor1) ;
   Sensorval2 = digitalRead(Trsensor2) ;
   Sensorval3 = digitalRead(Trsensor3) ;
   Sensorval4 = digitalRead(Trsensor4) ;
   Serial.print("----------------");
   Serial.print(Sensorval1);
   Serial.print("--");
   Serial.print(Sensorval2);
   Serial.print("--");
   Serial.print(Sensorval3);
   Serial.print("--");
   Serial.print(Sensorval4);
   Serial.println("----------------");

     Motorforward(Motorspeed);
    Serial.println("Forward");
    
if ((Sensorval1 == 1 || Sensorval3== 1 ) && (Sensorval2 == 0 && Sensorval4== 0 ))
{
    while ((Sensorval1 == 1 || Sensorval3== 1 ) && (Sensorval2 == 0 && Sensorval4== 0 )) {
    //    Serial.println("turn left");
      Motorleft(Motorspeed2);
     Sensorval1 = digitalRead(Trsensor1) ;
     Sensorval2 = digitalRead(Trsensor2) ;
     Sensorval3 = digitalRead(Trsensor3) ;
     Sensorval4 = digitalRead(Trsensor4) ;
         Serial.println("Left");
      delay(20);    
    }
   //   Motorstop(Motorspeed) ;
   //   delay(150);
 } 

if ((Sensorval2 == 1 || Sensorval4== 1 ) && (Sensorval1 == 0 && Sensorval3== 0 ))
{
    while ((Sensorval2 == 1 || Sensorval4== 1 ) && (Sensorval1 == 0 && Sensorval3== 0 )) {

    //    Serial.println("turn righ");
       Motorright(Motorspeed2);
       Sensorval1 = digitalRead(Trsensor1) ;
       Sensorval2 = digitalRead(Trsensor2) ;
       Sensorval3 = digitalRead(Trsensor3) ;
       Sensorval4 = digitalRead(Trsensor4) ;  
               Serial.println("Right");
      delay(20);    
     }
  //     Motorstop(Motorspeed) ;
}
      delay(20);    

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


