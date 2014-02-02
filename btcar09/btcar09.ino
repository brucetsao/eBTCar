/*
  Motoduino : Arduino with motors driver
 
 author: Brucetsao modified from Motoduino website @ http://motoduino.com - Feb. 2012
 */
const int Motor_PWM1 = 8; // digital pin 5 of Arduino (PWM)    
const int Motor_PWM2 = 9;  // digital pin 6 of Arduino (PWM)  
const int Motor_1A = 24;     // digital pin 7 of Arduino
const int Motor_1B = 25;     // digital pin 7 of Arduino
const int Motor_2A = 26;     // digital pin 7 of Arduino
const int Motor_2B = 27;     // digital pin 7 of Arduino
char val;  // variable to receive data from the serial port(bluetooth)
//----define control key
#define forwardkey 'f' 
#define backrwardkey 'b' 
#define leftkey 'l' 
#define rightkey 'r' 
#define stopkey 's' 

#define SLeftPin 30       //左感測器輸入腳
#define SRightPin 31   //右感測器輸入腳
// 感測器狀態值
byte byteSensorStatus=0;
boolean leftsensor;
boolean rightsensor;


void setup()  
{
  // Start serial communication at 57600
  Serial.begin(9600); 
  Serial1.begin(9600); 
  pinMode(Motor_1A, OUTPUT);
  pinMode(Motor_1B, OUTPUT);
  pinMode(Motor_2A, OUTPUT);
  pinMode(Motor_2B, OUTPUT);

// 輸出入接腳初始設定
  pinMode(SLeftPin, INPUT);
  pinMode(SRightPin, INPUT);  


  Serial.println("Start here");

}

void loop()
{
  int nIRStatus;  
    // 讀取左感測器狀態值
  leftsensor = digitalRead(SLeftPin);
    // 讀取右感測器狀態值
  rightsensor = digitalRead(SRightPin);
     //清除感測器狀態值
  byteSensorStatus = 0;
Serial.print("left sensor is :") ;
Serial.println(leftsensor) ;
Serial.print("right sensor is :") ;
Serial.println(rightsensor) ;

/*
   if(Serial1.available())
   {
   val = Serial1.read();
   Serial.println("-----------");
   Serial.println(val);
   Serial.println("----------------");

     switch(val)
     {
       case 'f':   // car forward
       Motorforward(255);
       break;
       case 'b':   // car backward
       Motorbackward(255);
       break;
       case 'l':   // car turn left
       Motorleft(255);
       break;
       case 'r':   // car turn right
       Motorright(255);
       break;
       case 's':   // car stop
       Motorstop(0);
       break;
     }    
   }
 */
 delay(1000);
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


