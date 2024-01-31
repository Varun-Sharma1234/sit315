const int temperaturePin = A0;
const int buzzerPin = 9;
const int buttonPin = 2; 
const float temperatureThreshold = 20.;

volatile bool temperatureCheckFlag = false;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP); 

 
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
}

void loop() {
  if (temperatureCheckFlag) {
    checkTemperature();
    temperatureCheckFlag = false;
  }
}

void buttonInterrupt() {
  
  temperatureCheckFlag = true;
}

void checkTemperature() {
  int sensorValue = analogRead(temperaturePin);
  float voltage = sensorValue * 5.0 / 1023.0;
  float temperatureCelsius = (voltage - 0.5) * 100.0;

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

