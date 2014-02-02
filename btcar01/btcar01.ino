/*
  Motoduino : Arduino with motors driver
  
   Author: Brucetsao modified from Motoduino website @ http://motoduino.com - Feb. 2012
*/
const int Motor_E2 = 5; // digital pin 5 of Arduino (PWM)    
const int Motor_E1 = 6;  // digital pin 6 of Arduino (PWM)  
const int Motor_M2 = 7;     // digital pin 7 of Arduino
const int Motor_M1 = 8;    // digital pin 8 of Arduino
char val;  // variable to receive data from the serial port(bluetooth)

void setup()  
{
  // Start serial communication at 57600
  Serial.begin(57600); 
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);
  Serial.println("Start here");
  
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
    }    
    
  }

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
  Serial.println("New Turn Right! ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, LOW);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
  
}

void left(byte flag, byte motorspeed)
{
  Serial.println("New   Turn Left!");

  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
  
}

