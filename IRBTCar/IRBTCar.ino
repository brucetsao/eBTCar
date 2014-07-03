#include <IRremote.h>
// ---- ddefine IR led use
#define RECV_PIN 12
#define LED_PIN 10
// ---- define for Bluetooth ----
int bt_key = -1;
const int upkey = 70 ;
const int leftkey = 76 ;
const int downkey = 66 ;
const int rightkey = 82 ;
const int bt1 = 68 ;
const int bt2 = 83 ;
const int bt3 = 88 ;
const int bt4 = 79 ;
//------------define car command
const int forwarddirection = 1 ;
const int backdirection = 3 ;
const int leftdirection = 2 ;
const int rightdirection = 4 ;
const int middledirection = 11 ;
const int stopdirection = 12 ;
#define btLED 11
//------define L298N use
const int motor1 = 7;
const int motor2 = 6;
const int motor3 = 5;
const int motor4 = 4;
// ---- ddefine IR led Object use
IRrecv irrecv(RECV_PIN);
decode_results results;
long IR_key = -1;
int CMD = 0 ; // for control car
//=============

//讀取IR Sharp數值
int potPin = 14;                // 宣告類比腳位輸入的PIN腳
int val = 0;                      // 宣告變數Val = 0
int ledPin=11;	//宣告使用Arduino  內建LED的變數

//==============

void setup()
{
Serial.begin(9600); // init serial speed
Serial.println("Program Start here" ); // Show program start status
Serial2.begin(9600);
//  init pin
	pinMode(potPin,INPUT);
	pinMode(ledPin,OUTPUT);	}

initall();
}
void loop() {
/*
IR_key = IRcheck() ; // Check IR Receiver
if ((IR_key == (long)(-1)) or (IR_key == (long)(-2)))
{
// no IR Sender Signal

digitalWrite(LED_PIN,LOW); // IR Led Display off
}
else
{
// Receive IR Sender Signal
digitalWrite(LED_PIN,HIGH); // IR Led Display on
Serial.println(IR_key);
IRControlCar((int)IR_key);
}
*/
//   ir check if blocked
    val = analogRead(potPin); // 用analogRead()這個函式讀取特定腳位的數值到變數val     
Serial.print(val,DEC);  //印出數值在Serial.Monitor
    Serial.print("\t");

    if (val<350)//當範圍內有障礙物時 
    {
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(motor3,LOW);
digitalWrite(motor4,LOW);
delay(300);  
    
   }
//   ir check if blocked
int btdata = 0;
btdata = BTcheck();
// Serial.println(btdata);
if (btdata != 0)
{
Serial.println(btdata);
BTControlCar(btdata);
digitalWrite(btLED,HIGH) ;
}
else
{
// Serial.println("bt data is zeror");
// digitalWrite(btLED,LOW) ;
}
delay(300);
}

void initall()

{
// init IR controller
pinMode(LED_PIN,OUTPUT); // init IR Led Display
irrecv.enableIRIn(); // Start the receiver
digitalWrite(LED_PIN,LOW); // init IR Led Display off
// init Bluetooth controller
pinMode(btLED,OUTPUT);
digitalWrite(btLED,LOW) ;
//----- motor set ----
pinMode(motor1,OUTPUT); // init Car pin for output
pinMode(motor2,OUTPUT); // init Car pin for output
pinMode(motor3,OUTPUT); // init Car pin for output
pinMode(motor4,OUTPUT); // init Car pin for output
carMiddle();
carStop();
}


void BTControlCar(int ctl)
{
switch (ctl)
{
case forwarddirection : // 前進
carForward() ;
break ;
case backdirection : // 後退
carBackward() ;
break ;
case leftdirection : // 向左
carLeft() ;
break ;
case rightdirection : // 向
carRight() ;
break ;
case middledirection : // for button "up" code
carMiddle() ;
break ;
case stopdirection : // for button "up" code
carStop() ;
break ;
}
}
void IRControlCar(int ctl)
{
switch (ctl)
{
case 2 : // Car go forward
carForward() ;
break ;
case 8 : // Car go backward
carBackward() ;
break ;
case 6 : // Car go right
carRight() ;
break ;
case 4 : // Car go left
carLeft() ;
break ;
case 5 : // Car go Stop
carStop() ;
break ;
case 1 : // Car go strait
carMiddle() ;
break ;
}
}
long IRcheck()
{
// irrecv.enableIRIn(); // Start the receiver
long tmp = -2 ;
if (irrecv.decode(&results)) {
// Serial.print("recdeive data is :");
// Serial.println(results.value);
// dump(&results);
tmp = IRencode(&results) ;
irrecv.resume(); // Receive the next value
return (tmp) ;
}
else
{
irrecv.resume(); // Receive the next value
return (tmp);
}
}
long IRencode(decode_results *code)
{
long encodeno = -1 ;
long cc = code->value ;
switch (cc)
{
case 16738455 : // for button "0" code
encodeno = 0 ;
break ;
case 16724175 : // for button "1" code
encodeno = 1 ;
break ;
case 16718055 : // for button "2" code
encodeno = 2 ;
break ;
case 16743045 : // for button "3" code
encodeno = 3 ;
break ;
case 16716015 : // for button "4" code
encodeno = 4 ;
break ;
case 16726215 : // for button "5" code
encodeno = 5 ;
break ;
case 16734885 : // for button "6" code
encodeno = 6 ;
break ;
case 16728765 : // for button "7" code
encodeno = 7 ;
break ;
case 16730805 : // for button "8" code
encodeno = 8 ;
break ;
case 16732845 : // for button "9" code
encodeno = 9 ;
break ;
case 16748655 : // for button "EQ" code for set timer
encodeno = 11 ;
break ;
case 16754775 : // for button "+" code for increase time 30 minutes
encodeno = 12 ;
break ;
case 16769055 : // for button "-" code code for decrease time 30 minutes
encodeno = 13 ;
break ;
case 16736925 : // for button "CH" code code for show 溫度與濕度
encodeno = 20 ;
break ;
default:
encodeno = cc ;
}
return (encodeno) ;
}
int BTcheck()
{
int tmp = 0 ;
int readkey = 0 ;
if (Serial2.available())
{
readkey = Serial2.read() ;
tmp = BTencode(readkey) ;
}
else
{
tmp = 0 ;
}
return (tmp);
}
int BTencode(int cc)
{
//Serial.print("the bt receive data is:");
//Serial.println(cc);
int encodeno = 0 ;
switch (cc)
{
case upkey : // for button "up" code
encodeno = 1 ;
break ;
case leftkey : // for button "left" code
encodeno = 2 ;
break ;
case downkey : // for button "down" code
encodeno = 3 ;
break ;
case rightkey : // for button "right" code
encodeno = 4 ;
break ;
case bt1 : // for button "1" code
encodeno = 11 ;
break ;
case bt2 : // for button "2" code
encodeno = 12 ;
break ;
case bt3 : // for button "3" code
encodeno = 13 ;
break ;
case bt4 : // for button "4" code
encodeno = 14 ;
break ;
default:
encodeno = cc ;
}
return (encodeno) ;
}
void carForward()
{
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
}
void carBackward()
{
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
}
void carRight()
{
digitalWrite(motor3,HIGH);
digitalWrite(motor4,LOW);
}
void carLeft()
{
digitalWrite(motor3,LOW);
digitalWrite(motor4,HIGH);
}
void carMiddle()
{
digitalWrite(motor3,LOW);
digitalWrite(motor4,LOW);
}

void carStop()
{
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
}
