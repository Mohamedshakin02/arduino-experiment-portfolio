// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 9 as an output.
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for 500 milliseconds
  digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for 500 milliseconds
}