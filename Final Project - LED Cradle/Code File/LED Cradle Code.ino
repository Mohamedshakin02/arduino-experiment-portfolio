#include <Servo.h>


// Pins
const int servoPin = 3;
const int buttonPin = 2;


// LED pins
const int ledPins[] = {5, 6, 9, 10, 11};


Servo myServo;


// States
bool running = false;
bool lastButtonState = LOW;
bool justStopped = false;


// Positions (UPDATED RANGE)
int centerPos = 90;
int leftPos = 60;
int rightPos = 120;


void setup() {
  pinMode(buttonPin, INPUT);


  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }


  myServo.attach(servoPin);
  myServo.write(centerPos);


  allOff();
}


void loop() {


  bool buttonState = digitalRead(buttonPin);


  // Toggle button
  if (buttonState == HIGH && lastButtonState == LOW) {
    running = !running;


    if (!running) {
      justStopped = true;
    }


    delay(200);
  }


  lastButtonState = buttonState;


  // STOP HANDLER
  if (justStopped) {
    moveSmooth(centerPos);
    allOff();
    justStopped = false;
    return;
  }


  // FULL STOP
  if (!running) {
    moveSmooth(centerPos);
    allOff();
    return;
  }


  // RUN MODE


  // center
  moveSmooth(centerPos);
  lightOnly(2);
  delay(200);


  // left sweep
  for (int i = 2; i >= 0; i--) {
    if (!running) return;


    int pos = map(i, 2, 0, centerPos, leftPos);
    moveSmooth(pos);
    lightOnly(i);
    delay(180);
  }


  // back center
  for (int i = 0; i <= 2; i++) {
    if (!running) return;


    int pos = map(i, 0, 2, leftPos, centerPos);
    moveSmooth(pos);
    lightOnly(i);
    delay(180);
  }


  // right sweep
  for (int i = 2; i <= 4; i++) {
    if (!running) return;


    int pos = map(i, 2, 4, centerPos, rightPos);
    moveSmooth(pos);
    lightOnly(i);
    delay(180);
  }


  // back center
  for (int i = 4; i >= 2; i--) {
    if (!running) return;


    int pos = map(i, 4, 2, rightPos, centerPos);
    moveSmooth(pos);
    lightOnly(i);
    delay(180);
  }
}


// SMOOTH SERVO MOVEMENT
void moveSmooth(int target) {
  int current = myServo.read();


  if (current < target) {
    for (int i = current; i <= target; i++) {
      myServo.write(i);
      delay(5);
    }
  } else {
    for (int i = current; i >= target; i--) {
      myServo.write(i);
      delay(5);
    }
  }
}


// ONLY ONE LED ON
void lightOnly(int index) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[index], HIGH);
}


// ALL OFF
void allOff() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
