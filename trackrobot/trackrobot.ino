///////////////////////////////////////////////
// 程式說明: 紅外線循線自走車(機器人)
// 作者: Dennis Chen 2013
// Email: sinocgtchen@gmail.com
/////////////////////////////////////////////

///三路紅外線感測器與Motoduino的腳位對應
const int SLeftLeft = 9;      //左感測器輸入腳
const int SMiddle = 10;     //中間感測器輸入腳
const int SRightRight = 11;     //右感測器輸入腳

// 馬達與motoduino的腳位對應
const int Motor_E2 = 5; // 控制馬達2轉速 digital pin 5 of Arduino (PWM)    
const int Motor_E1 = 6;  // 控制馬達1轉速 digital pin 6 of Arduino (PWM)  
const int Motor_M1 = 7;     // 控制馬達1正反轉 digital pin 7 of Arduino
const int Motor_M2 = 8;    // 控制馬達2正反轉 digital pin 8 of Arduino

// 感測器狀態值
byte byteSensorStatus=0;

void setup() {
   //set up serial communications
   Serial.begin(57600);

  // 輸出入接腳初始設定
  pinMode(SLeftLeft, INPUT);
  pinMode(SMiddle, INPUT);
  pinMode(SRightRight, INPUT);
  
  pinMode(Motor_M1, OUTPUT);  // 設定 Motor_M1為輸出腳位
  pinMode(Motor_M2, OUTPUT);  // 設定 Motor_M2為輸出腳位
}

//////////// 主程式 ////////
void loop(){
  int nIRStatus;  

  //清除感測器狀態值
  byteSensorStatus = 0;
  // 讀取左感測器狀態值
  nIRStatus = digitalRead(SLeftLeft);
  if(nIRStatus == 1)
     byteSensorStatus = (byteSensorStatus | (0x01 << 2));
     
  // 讀取中間感測器狀態值   
  nIRStatus = digitalRead(SMiddle);
  if(nIRStatus == 1)
     byteSensorStatus = (byteSensorStatus | (0x01 << 1));
     
    // 讀取右邊感測器狀態值   
  nIRStatus = digitalRead(SRightRight);
  if(nIRStatus == 1)
     byteSensorStatus = (byteSensorStatus | 0x01);

   drivemotor(byteSensorStatus);
}
///////////////////////////

void drivemotor(byte nStatus)
{
  switch(nStatus)
  { // 　　感測器 黑色:1  　白色:0
    case 7: // SL:1 SM:1 SR:1  //黑黑黑
            motorstop(0, 0);
            break;
    case 6: // SL:1 SM:1 SR:0  //黑黑白
            left(0, 255);
            break;
    case 5: // SL:1 SM:0 SR:1  //黑白黑
            motorstop(0, 255);
            break;
    case 4: // SL:1 SM:0 SR:0  //黑白白
            left(0, 255);
            break;
    case 3: // SL:0 SM:1 SR:1 // 白黑黑
             right(0, 255);
             break;
    case 2: // SL:0 SM:1 SR:0  // 白黑白
             forward(0, 255);
             break;
    case 1: // SL:0 SM:0 SR:1  // 白白黑
             right(0, 255);
             break;
    case 0: // SL:0 SM:0 SR:0  //白白白
             forward(0, 255);
  }
 
}

void motorstop(byte flag, byte motorspeed)
{
  Serial.println("停止!");
  
  digitalWrite( Motor_E1, motorspeed);
  digitalWrite( Motor_E2, motorspeed);

}

void forward(byte flag, byte motorspeed)
{
  Serial.println("前進!");
    
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
}

void backward(byte flag, byte motorspeed)
{
  Serial.println("後退!");
  
  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);
  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);

}

void right(byte flag, byte motorspeed)
{
  Serial.println("右轉!");  
  
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, motorspeed);
}

void left(byte flag, byte motorspeed)
{
  Serial.println("左轉!");  
  
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, 0);

}
