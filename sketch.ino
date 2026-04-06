#define LED_PIN 25
#define POT_PIN 34

int sensorValue = 0;
int threshold = 2000;
String command = "AUTO";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  sensorValue = analogRead(POT_PIN);

  int percent = map(sensorValue, 0, 4095, 0, 100);

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Load: ");
  Serial.print(percent);
  Serial.println("%");

  if (Serial.available()) {
    command = Serial.readString();
    command.trim();
  }

  if (command == "ON") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Motor ON (Manual)");

  } else if (command == "OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Motor OFF (Manual)");

  } else {

    if (sensorValue > threshold) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("AUTO: Motor ON");
    } else {
      digitalWrite(LED_PIN, LOW);
      Serial.println("AUTO: Motor OFF");
    }
  }

  delay(500);
}