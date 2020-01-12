
#include <LiquidCrystal.h>
#include <Servo.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// These constants won't change. They're used to give names
// to the pins used:
const int analogInPin = A5; // Analog input pin that the Sensor is attached to
int sensorValue = 0; // value read from the Soil Moisture 
Servo arm;
int servopos = 0;



#define DHT11_PIN 7

void setup() {
  arm.attach(9);
// set up the LCD's number of columns and rows:
Serial.begin(9600);
lcd.begin(16, 2);
delay(100);
} 
void loop() {
  
lcd.clear();
lcd.print("Soil Moisture:");// print the results to the LCD Display:
sensorValue = analogRead(analogInPin);// read the analog in value:
lcd.setCursor(0, 1);
lcd.println(sensorValue);
Serial.println(sensorValue);
// wait 300 milliseconds before the next loop for the 
//analog-to-digital converter to settle after the last reading:
delay(300);
if (sensorValue < 600) {
  arm.write(200);
  delay (100);
}
if (sensorValue > 600){
    arm.write(90);
    delay(100);
  }
}
