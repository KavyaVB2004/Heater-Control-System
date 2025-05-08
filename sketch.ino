#include <DHT.h>

#define DHTPIN 5            // DHT22 connected to GPIO 5
#define DHTTYPE DHT22        // DHT22 sensor type
#define LED_PIN 13           // LED on GPIO 13 (represents heater)
#define BUZZER_PIN 15        // Buzzer on GPIO 15

DHT dht(DHTPIN, DHTTYPE);    // Initialize DHT sensor

// Function prototype
void temperatureTask(void *parameter);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);    // Set LED pin as output
  pinMode(BUZZER_PIN, OUTPUT); // Set Buzzer pin as output

  // Start the FreeRTOS task
  xTaskCreatePinnedToCore(
    temperatureTask,   // Function to execute
    "TempTask",        // Task name
    4096,              // Stack size
    NULL,              // Parameters
    1,                 // Priority
    NULL,              // Task handle
    1                  // Run on Core 1
  );
}

void loop() {
  // Nothing here - handled by FreeRTOS
}

void temperatureTask(void *parameter) {
  while (true) {
    float temp = dht.readTemperature();

    if (isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.println(temp);
      
      if (temp > 35.0) {  // Overheat state
        Serial.println("State: Overheat");
        digitalWrite(LED_PIN, LOW);   // Turn off the heater (LED)
        tone(BUZZER_PIN, 1000);       // Sound buzzer for overheat
      } else if (temp < 25.0) {  // Heating state
        Serial.println("State: Heating");
        digitalWrite(LED_PIN, HIGH);  // Turn on the heater (LED)
        noTone(BUZZER_PIN);           // Turn off the buzzer
      } else {  // Idle state
        Serial.println("State: Idle");
        digitalWrite(LED_PIN, LOW);   // Turn off the heater (LED)
        noTone(BUZZER_PIN);           // Turn off the buzzer
      }
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);  // Wait 2 seconds before next reading
  }
}
