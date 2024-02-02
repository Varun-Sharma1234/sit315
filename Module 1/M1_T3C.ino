const int temperaturePin = A0;
const int lightPin = A1;
const int motionPin = 2;  // Pin for motion sensor input
const int buzzerPin = 9;
const int ledPin = 7;    // Pin for controlling the LED
const int buttonPin = 3;  // Button pin for interrupt
const float temperatureThreshold = 20.0;
const int lightThreshold = 500; // Example threshold for light sensor

volatile bool sensorCheckFlag = false;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(motionPin), motionInterrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(motionPin), motionInterrupt2, FALLING);
}

void loop() {
  if (sensorCheckFlag) {
    checkSensors();
    sensorCheckFlag = false;
  }
}

void buttonInterrupt() {
  sensorCheckFlag = true;
}

void motionInterrupt() {

  digitalWrite(ledPin, HIGH);  // Turn on the LED when motion is detected
 
}

void checkSensors() {
  checkTemperature();
  checkLight();
}

void checkTemperature() {
  int temperatureSensorValue = analogRead(temperaturePin);
  float temperatureVoltage = temperatureSensorValue * 5.0 / 1023.0;
  float temperatureCelsius = (temperatureVoltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  if (temperatureCelsius > temperatureThreshold) {
    tone(buzzerPin, 1000);
    Serial.println("High temperature! Buzzer activated.");
  } else {
    noTone(buzzerPin);
  }
}

void checkLight() {
  int lightSensorValue = analogRead(lightPin);

  Serial.print("Light: ");
  Serial.println(lightSensorValue);

  if (lightSensorValue < lightThreshold) {
    tone(buzzerPin, 1500);
    Serial.println("Low light! Buzzer activated.");
  } else {
    noTone(buzzerPin);
  }
}
