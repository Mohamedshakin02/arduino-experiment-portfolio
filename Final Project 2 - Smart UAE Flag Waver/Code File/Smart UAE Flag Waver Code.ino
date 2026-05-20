#include <Servo.h>


const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int SERVO_PIN = 9;


const int DISTANCE_THRESHOLD = 50; // cm


Servo servo;


float duration_us, distance_cm;


void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  servo.attach(SERVO_PIN);
  servo.write(90); // straight position
}


float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  duration_us = pulseIn(ECHO_PIN, HIGH);
  return 0.017 * duration_us;
}


void loop() {
  distance_cm = getDistance();


  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");


  if (distance_cm < DISTANCE_THRESHOLD && distance_cm > 0) {


    Serial.println("Object detected → scanning");


    unsigned long startTime = millis();


    // move left-right for 5 seconds
    while (millis() - startTime < 5000) {
      servo.write(70);   // left
      delay(300);


      servo.write(110);  // right
      delay(300);
    }


    servo.write(90); // center after scanning


  }
  else {
    Serial.println("No object → stay straight");
    servo.write(90); // straight / idle position
  }


  delay(200);
}
