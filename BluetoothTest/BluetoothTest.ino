#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX
char state;
int flag = 1;
// LED
int LED1 = 11;
int LED2 = 12;
int LED3 = 13;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Selamat datang!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);  
}

void loop() // run over and overM
{
  if (mySerial.available()) {
      state = mySerial.read(); // read incoming state (Rx)
      mySerial.println(state); // re-send respon (Tx)
      Serial.println(state);   // send to serial/lcd
      flag = 0;  
  }

  if (Serial.available()) {
      state = Serial.read();  // read from internal serial port
      Serial.println(state);  // send to serial/lcd
      mySerial.println(state); // send respon to Tx
      flag = 0;  
  }

  if (flag == 0) {
    if (state == 'L' || state == 'l') {
      digitalWrite(LED1,HIGH);       
    }
    if (state == 'N' || state == 'n') {
      digitalWrite(LED2,HIGH); 
    }
    if (state == 'R' || state == 'r') {
      digitalWrite(LED3,HIGH); 
    }
    if (state == 'D' || state == 'd') {
      digitalWrite(LED2,HIGH); 
    }

    if (state == '1') {
      digitalWrite(LED1,HIGH); 
    }
    if (state == '2') {
      digitalWrite(LED2,HIGH); 
    }
    if (state == '3') {
      digitalWrite(LED3,HIGH); 
    }

    if (state == 'A' || state == 'a') {
      digitalWrite(LED1,HIGH); 
    }
    if (state == 'B' || state == 'b') {
      digitalWrite(LED2,HIGH); 
    }
    if (state == 'C' || state == 'c') {
      digitalWrite(LED3,HIGH); 
    }
    delay(100);
    digitalWrite(LED1,LOW); 
    digitalWrite(LED2,LOW); 
    digitalWrite(LED3,LOW); 
    flag = 1;
  }
  
}

