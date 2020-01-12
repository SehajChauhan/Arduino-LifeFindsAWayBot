#include <AFMotor.h>
unsigned long start = 0;
unsigned long ennd;

int holderL;
int holderR;
boolean inloop = false;

AF_DCMotor motorL1(1);
AF_DCMotor motorL2(2);
AF_DCMotor motorR1(3);
AF_DCMotor motorR2(4);

// this is the led
int lightL = 9;
int lightR = 8;
//this is the photoR
int PHl = A0;
int PHr = A1;
//echo pins
const int trigPin = A2;
const int echoPin = A3;
//just variabales
int vR = 0;
int vL = 0;
// defines variables
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  vL = analogRead(PHl);
  vR = analogRead(PHr);

  holderL = vL;
  holderR = vR;

}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor

  //Serial.print("Distance: ");
  //Serial.println(distance);

  // make sure it doesnt hit a wall infront
  if (distance < 20) {
    spin();
  }

  // reading the 2 light sencers
  vL = analogRead(PHl);
  vR = analogRead(PHr);
  //this is it the varibles to make a range to see if the light doesnt change from the being
  boolean lRange = vL + 5 >= holderL && holderL >= vL - 5;
  boolean rRange = vR + 5 >= holderR && holderR >= vR - 5;
  Serial.println(lRange);
  Serial.println(rRange);

  // this makes sure the is lights doesnt change or did find light after 30sec it
  //rotats and looks for light
  while (lRange && rRange) {
    lRange = vL + 5 > holderL > vL - 5;
    rRange = vR + 5 > holderL > vR - 5;
    ennd = millis();
    Serial.println(ennd - start);
    // my timer
    if ((ennd - start) > 30000) {
      spin();
      look();
      //re-set timer
      start = millis();
      break;
    }
  }

  // follow the light
  float readL = map(vL, 890, 900, 0, 400);
  float readR = map(vR, 875, 900, 0, 400);

  readL = constrain(readL, 0, 400);
  readR = constrain(readR, 0, 400);
  motorL1.run(BACKWARD);
  motorL2.run(BACKWARD);
  motorR1.run(FORWARD);
  motorR2.run(FORWARD);

  motorL1.setSpeed(readR);
  motorL2.setSpeed(readR);
  motorR1.setSpeed(readL);
  motorR2.setSpeed(readL);

  // re-ser timer if car moves
  if (readR > 0 || readL > 0) {
    start = millis();
  }
  delay(30);
}

//spin around method
void spin() {
  Serial.println("spin: ");
  motorL1.run(BACKWARD);
  motorL2.run(BACKWARD);
  motorL1.setSpeed(255);
  motorL2.setSpeed(255);
  motorR1.run(BACKWARD);
  motorR2.run(BACKWARD);
  motorR1.setSpeed(255);
  motorR2.setSpeed(255);
  delay(2000);
}

//moves forward for 1sec looking for light
void look() {
  motorL1.run(BACKWARD);
  motorL2.run(BACKWARD);
  motorL1.setSpeed(255);
  motorL2.setSpeed(255);
  motorR1.run(FORWARD);
  motorR2.run(FORWARD);
  motorR1.setSpeed(255);
  motorR2.setSpeed(255);
  delay(1000);
}
