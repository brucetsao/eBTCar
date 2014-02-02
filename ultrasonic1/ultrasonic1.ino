//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
/*******************************************************
 * This program will test the LCD panel and the buttons
 * Author :BruceTSao 2013.10.31
 * modified from Mark Bramwell, July 2010
 ********************************************************/
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// LiquidCrystal(rs, enable, d4, d5, d6, d7) 
// LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
// LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6
// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
// read the buttons
#define trigPin 11
#define echoPin 12


void setup()
{
   Serial.begin (9600);
  Serial.println("Start here");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2); // start the library
  lcd.setCursor(0,0);
  lcd.print("Detect Distance"); // print a simple message
}
void loop()
{
  lcd.setCursor(0,1); // move to the begining of the second line
  lcd.print(read_ultrasonic()); // print a simple message
  lcd.setCursor(13,1); // move to the begining of the second line
  lcd.print("cm"); // print a simple message

delay(300);

}
//------------------
double read_ultrasonic()
{
  double tmp = 0 ;
  double duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    tmp = -1 ;
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("Out of range");
    Serial.println("--------------");
  }
  else {
        tmp = distance ;
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("read ok...");
    Serial.println("--------------");
  }
 
  return (tmp);
}  




