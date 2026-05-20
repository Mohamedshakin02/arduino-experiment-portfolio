#define RAIN_SENSOR_PIN  A0   // Arduino pin connected to the OUTPUT pin of rain sensor
#define LED_PIN          7   // Arduino pin connected to LED's pin
int rain_state      = LOW; // current  state of rain sensor's pin
int prev_rain_state = LOW; // previous state of rain sensor's pin


void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(RAIN_SENSOR_PIN, INPUT); // set arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);          // set arduino pin to output mode
}


void loop() {
  int rain_state = digitalRead(RAIN_SENSOR_PIN);


  if (rain_state == LOW) {   // LOW = rain detected
    Serial.println("Rain detected!");
    digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println("No rain");
    digitalWrite(LED_PIN, LOW);
  }


  delay(500);
}
