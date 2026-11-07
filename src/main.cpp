#include <Arduino.h>

// Note: Do not attempt to power the ultra sonic distance sensor from the Arduino.  Use a seperate 5v power source.
// Note: The ultra sonic distance sensor must be powered up for this to work.

#define USONIC_NUMER_OF_PINS  4 // The number of pins on the ultrasonic distance sensor.

#if USONIC_NUMER_OF_PINS == 4
  #define USONIC_TRIGGER_PIN  7
  #define USONIC_ECHO_PIN   8
#elif USONIC_NUMER_OF_PINS == 3
  #define USONIC_TRIGGER_PIN  7
  #define USONIC_ECHO_PIN   7
#endif

long getCmDistanceFromSensor(void);

void setup() {
  // Initialize serial communication at 57600 bits per second
  Serial.begin(57600);
  #if USONIC_NUMER_OF_PINS == 4
    pinMode(USONIC_TRIGGER_PIN, OUTPUT);
    pinMode(USONIC_ECHO_PIN, INPUT);
  #elif USONIC_NUMER_OF_PINS == 3
    pinMode(USONIC_ECHO_PIN, INPUT);
  #endif

  Serial.print("Setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  long distanceCm = getCmDistanceFromSensor();
  Serial.print(" distance (cm): ");
  Serial.println(distanceCm);
  delay(1000);
}

long getCmDistanceFromSensor(void) {
  #if USONIC_NUMER_OF_PINS == 4
    digitalWrite(USONIC_TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(USONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(USONIC_TRIGGER_PIN, LOW);
  #elif USONIC_NUMER_OF_PINS == 3
    // 1. Send a short LOW pulse to ensure a clean HIGH pulse
    pinMode(USONIC_ECHO_PIN, OUTPUT);
    digitalWrite(USONIC_ECHO_PIN, LOW);
    delayMicroseconds(2);

    // 2. Trigger the sensor by sending a HIGH pulse for 5 to 10 microseconds
    digitalWrite(USONIC_ECHO_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(USONIC_ECHO_PIN, LOW);

    // 3. Switch the same pin to INPUT to read the returning pulse
    pinMode(USONIC_ECHO_PIN, INPUT);
 #endif 

    long duration = pulseIn(USONIC_ECHO_PIN, HIGH);
    long distanceCm = duration * 0.034 / 2;
    return distanceCm;
}
