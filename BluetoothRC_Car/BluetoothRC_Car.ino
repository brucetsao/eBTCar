#include <Servo.h> 
#include <SoftwareSerial.h>

Servo myservo;
SoftwareSerial mySerial(6, 7); // RX, TX
int motorPins[] = {2, 3, 4, 5};
int count = 0;
int count1 = 0;
int count2 = 0;
int delayTime = 5;
String inputString = "";
String inputValue = "";
char inputMode;
boolean stringComplete = false;

void setup() {
  mySerial.begin(9600);
  myservo.attach(8);
  for (count = 0; count < 4; count++) {
    pinMode(motorPins[count], OUTPUT);
  }
  inputString.reserve(200); // reserve 200 bytes for the inputString:
}

void loop() {
  count = 0;
  inputString = "";
  inputValue = "";
  while (mySerial.available()) {
    count++;
    // get the new byte:
    char inChar = (char)mySerial.read();  
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    if (inChar == '\n') {
      stringComplete = true;
      inputMode = inputString[0];
    } else {
      if (count>1) {
        inputValue += inChar;
      }
    }
  }

  if (stringComplete) {
    stringComplete = false;
    int value =  inputValue.toInt();  // convert string to integer
    
    if (inputMode=='S') {
      if (value>=0 && value <=180) {
        myservo.write(value);
        mySerial.println("Turn : "+inputValue); 
      }
    }
    if (inputMode=='D' && value>0) {
      delayTime = (100 - value * 10); // because range of value 0-9
      moveForward();
    }
    if (inputMode=='R' && value>0) {
      delayTime = (100 - value * 10); // because range of value 0-9
      moveBackward();
    }
    if (inputMode=='C' && value==1) {
      // custom key1
    }
    if (inputMode=='C' && value==2) {
      // custom key2
    }
    if (inputMode=='C' && value==3) {
      // custom key3
    }
    if (inputMode=='C' && value==4) {
      // custom key4
    }
  }
}

void moveForward() {
  for (count1 = 0; count1 < 4; count1++) {    
    if ((count2 == 0) || (count2 == 1)) {
      count2 = 16;
    }
    count2>>=1;
    for (count = 3; count >= 0; count--) {
      digitalWrite(motorPins[count], count2>>count&0x01);
    }
    delay(delayTime);
  }
}

void moveBackward() {
  for (count1 = 0; count1 < 4; count1++) {    
    if ((count2 == 0) || (count2 == 1)) {
      count2 = 16;
    }
    count2>>=1;
    for (count = 3; count >= 0; count--) {
      digitalWrite(motorPins[3 - count], count2>>count&0x01);
    }
    delay(delayTime);
  }
}


