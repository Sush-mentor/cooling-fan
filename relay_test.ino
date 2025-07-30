#include <DHT.h>

#define DHTPIN 2        // Pin where DHT11 data is connected
#define DHTTYPE DHT11   // DHT11 sensor
#define RELAY_PIN 7     // Relay control pin

DHT dht(DHTPIN, DHTTYPE);

const float temperatureThreshold = 28.0; // Temperature threshold in °C

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Motor OFF initially

  Serial.println("Temperature-Controlled Motor with DHT11 Sensor");
}

void loop() {
  delay(2000); // Wait for sensor to stabilize

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if reading is valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("❌ Error reading from DHT sensor!");
    return;
  }

  // Print values
  Serial.print("🌡️ Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("💧 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Motor control based on temperature
  if (temperature > temperatureThreshold) {
    digitalWrite(RELAY_PIN, HIGH); // Turn ON motor
    Serial.println("🔁 Motor: ON (Temperature above 28°C)");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Turn OFF motor
    Serial.println("⏹️ Motor: OFF (Temperature ≤ 28°C)");
  }

  Serial.println("-----------------------------");
}
