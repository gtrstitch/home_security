/*--------------------------------
Arduino Based Home Security Monitor
Author - Gtr_Stitch
June 20, 2013
NOTE - This sketch assumes you have the latest DS1307 Library installed.
--------------------------------*/

#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>

LiquidCrystal lcd(5,6,7,9,10,11);
RTC_DS1307 RTC;

const int pir = 2;
const int reed = 3;
const int led = 12;
const int piez = 8;


void setup(){
  RTC.begin();
  Wire.begin();
  lcd.begin(16, 2);
  
  /* This snippet of code sets up the RTC with time on your computer.
  Uncomment it, upload the sketch, comment it back out again then upload once more. */
  RTC.adjust(DateTime(__DATE__, __TIME__)); 
  
  pinMode(reed, INPUT);  
  pinMode(pir, INPUT);  
  pinMode(led, OUTPUT);  
  pinMode(piez, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("--INITIALIZING--");
  lcd.setCursor(0,1);
  lcd.print(" Please Wait...  ");
  delay(5000); //Give the PIR time to calibrate
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   *ACTIVE*   ");
  delay(2000);
}

void indicator_pir(){
  digitalWrite(led, HIGH);
  tone(piez, 300);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

void indicator_reed(){
  digitalWrite(led, HIGH);
  tone(piez, 600);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

void trip_pir(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("     MOTION     ");
  indicator_pir();
}

void trip_reed(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   BREACH DOOR");
  indicator_reed();
}

void loop(){
  
  int reed = digitalRead(3);
  int pir = digitalRead(2);
  if ( reed == HIGH){
    trip_reed();
  }
  
  else if ( pir == HIGH){
    trip_pir();
  }
  
  else {
    noTone(piez);
  DateTime now = RTC.now();
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  delay(1000);
  }
}


