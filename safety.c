#include <SoftwareSerial.h>  //including the software serial UART library which will make the digital pins as TX and RX
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <math.h>
#include <Servo.h> 
SoftwareSerial mySerial(2, 3);

SoftwareSerial esp8266(2,3); //Connect the TX pin of ESP8266 to pin 2 of Arduino and RX pin of ESP8266 to pin 3 of Arduino.
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const int trigPin = 6;
const int echoPin = 7;

int servoPin = A4;

const int IR = 5;
const int gas = 3;
const int relay = 4;

//long duration;
//int distanceCm, distanceInch;

long duration,duration1,duration2,duration3;
int distanceCm,distanceCm1,distanceCm2,distanceCm3, distanceInch;
int rxPin = 0;                    // RX PIN 
 int txPin = 1;                    // TX TX
 int byteGPS=-1;
 char linea[300] = "";
 char lat[30] = "";
 char lon[30] = "";

int buttonState1=0;
int buttonState2=0;

int limit;
Servo Servo1;


void txs(unsigned char val)
{
int i;
Serial.write(val);
for(i=0;i<1200;i++);
}


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);   
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(relay, OUTPUT);
Servo1.attach(servoPin);
pinMode(IR, INPUT); 
pinMode(gas, INPUT); 


 Serial.print("AT");
         Serial.write(13);
         Serial.write(10);
                  delay(1000);
            Serial.print("AT+CMGF=1");
         Serial.write(13);
         Serial.write(10);
 
  
}

void gpss()
{ 
  int i;
  
        Serial.print("AT");        
         Serial.write(13);
         Serial.write(10);     delay(1000);     
         Serial.print("AT+CMGS=");
         Serial.write(34);
         Serial.print("9444755530");
         Serial.write(34);
         Serial.write(13);
         Serial.write(10);
         delay(1000);
         Serial.print("Alert!  ");
         Serial.write(13);
         Serial.write(10);
txs(' ');txs(' ');
  txs(lat[0]);
  txs(lat[1]);
  txs(lat[2]);
  txs(lat[3]);
  txs(lat[4]);
  txs(lat[5]);
  txs(lat[6]);
  txs(lat[7]);
   txs(' ');
  txs(' ');txs(' ');
  txs(lon[0]);
  txs(lon[1]);
  txs(lon[2]);
  txs(lon[3]);
  txs(lon[4]);
  txs(lon[5]);
  txs(lon[6]);
  txs(lon[7]); 
         
         Serial.write(26);         
        delay(5000);
while(i<150)
  {
    if (Serial.available() > 0)
    {
        linea[i]=Serial.read();         // Read a byte of the serial port
 i++;
    }
  }
       for (int i=0;i<100;i++){    //  
        //Serial.print(linea[i]);
        if(linea[i]=='G')
          if(linea[i+1]=='P')
            if(linea[i+2]=='R')
              if(linea[i+3]=='M')
                 if(linea[i+4]=='C')
                    {
                      lat[0]=linea[i+19];
                      lat[1]=linea[i+20];
                      lat[2]=linea[i+21];
                      lat[3]=linea[i+22];
                      lat[4]=linea[i+23];
                      lat[5]=linea[i+24];
                      lat[6]=linea[i+25];
                      lat[7]=linea[i+26];

                      lon[0]=linea[i+31];
                      lon[1]=linea[i+32];
                      lon[2]=linea[i+33];
                      lon[3]=linea[i+34];
                      lon[4]=linea[i+35];
                      lon[5]=linea[i+36];
                      lon[6]=linea[i+37];
                      lon[7]=linea[i+38];
                                                    
                    }
            }
 
i=0;
  
  }

void oup()
 {
   Servo1.write(90);
 // delay(1000);
   Servo1.write(0);
 // delay(1000);
 // Serial.println("gueter1!");
   // Serial.println("ford");
 }

   void odown()
   {
  Servo1.write(0);
 // delay(1300);
   Servo1.write(90);
 // delay(1300);
 // Serial.println("guester2!"); 
   }
/*void SendTextMessage1()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(2000);
  mySerial.println("AT+CMGS=\"+916369458646\"\r"); // change to the phone number you using 
  delay(2000);
  mySerial.println("Guarbage Emty" );//the content of the message
  
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(5000);
   mySerial.println("AT+CMGS=\"+916369458646\"\r"); // change to the phone number you using 
  delay(2000);
  mySerial.println("Guarbage Emty" );//the content of the message
  delay(200);
  mySerial.println((char)26);//the message stopping character
  delay(5000);
 // sms_count++;
}*/
  /* void SendTextMessage2()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(2000);
  mySerial.println("AT+CMGS=\"+91\"\r"); // change to the phone number you using 
  delay(2000);
  mySerial.println("Guarbage Full" );//the content of the message
  
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(5000);
   mySerial.println("AT+CMGS=\"+919841287891\"\r"); // change to the phone number you using 
  delay(2000);
  mySerial.println("Guarbage Full" );//the content of the message
  delay(200);
  mySerial.println((char)26);//the message stopping character
  delay(5000);
 // sms_count++;
}
*/
void mot()
{  
  
  buttonState1 = digitalRead(IR);

  if (buttonState1 == HIGH) 
  {
     gpss();
//digitalWrite(ledpin, HIGH);
odown();
//digitalWrite(relay, HIGH);
Serial.print(" open   ");
  }
  else
  {
    //digitalWrite(relay, LOW);
    oup();
    
//digitalWrite(ledpin, LOW);
Serial.print("  close ");
  }
 }


void loop()
{
  mot();
//  mot1();
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;
//lcd.setCursor(10,0); // Sets the location at which subsequent text written to the LCD will be displayed
//lcd.print("Distance: "); // Prints string "Distance" on the LCD
//lcd.print(distanceCm); // Prints the distance value from the sensor
//lcd.print(" cm");
delay(10);
//lcd.setCursor(0,1);
//lcd.print("Distance: ");
//lcd.print(distanceInch);
//lcd.print(" inch");
Serial.print("  Distance1: ");
Serial.println(distanceCm);

//Serial.print("inch: ");
//Serial.println(distanceInch);
 digitalWrite(relay, HIGH);
 if(distanceCm<30)
 {
  digitalWrite(relay, LOW);
 
  //SendTextMessage2();
 // Serial.println("hhh");

  }

  
 /* else if(distanceCm>10)
 {
  
SendTextMessage1();
  
  
  }*/
}





 
