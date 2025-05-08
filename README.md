# Heater Control System with Temperature Monitoring

This project simulates a basic heater control system using an ESP32 microcontroller, a DHT22 temperature sensor, a buzzer for alerting, and an LED as a simulated heater. The system uses **FreeRTOS** to manage tasks in a real-time, multitasking environment. The system reads temperature values and automatically controls the heater (LED) based on preset thresholds for heating, idle, and overheat states.

## Features
- **Temperature Monitoring**: The system continuously reads temperature from a **DHT22** sensor.
- **Heater Control**: The heater is represented by an LED. It turns on or off based on the temperature.
- **Overheat Protection**: If the temperature exceeds a threshold, the system turns off the heater (LED) and triggers a buzzer to signal overheating.
- **FreeRTOS**: The temperature monitoring and control task is handled in a FreeRTOS task, enabling real-time operation.
- **Multitasking**: The system uses **FreeRTOS** to handle periodic sensor readings and control operations without blocking the main loop.

## Hardware Components
- **ESP32** development board (with FreeRTOS support)
- **DHT22** temperature and humidity sensor
- **LED** (simulating the heater)
- **Buzzer** (for overheat alert)
- **Wires** to connect the components

### Pin Configuration
- **DHT22**: Connected to **GPIO 5**
- **LED (Heater)**: Connected to **GPIO 13**
- **Buzzer**: Connected to **GPIO 15**

## Libraries Required
- **DHT sensor library**: Used for reading temperature and humidity data from the DHT22 sensor.
  - Install via Arduino Library Manager or include this line in the code:
    ```cpp
    #include <DHT.h>
    ```
- **FreeRTOS**: Included with the ESP32 platform by default.

## Circuit Diagram
Here’s how the components are connected to the ESP32:

- **DHT22 Pinout**:
  - **VCC** -> 3.3V
  - **GND** -> GND
  - **Data** -> GPIO 5

- **LED Pinout**:
  - **Anode** (long leg) -> GPIO 13 (with a current-limiting resistor, 220Ω)
  - **Cathode** (short leg) -> GND

- **Buzzer Pinout**:
  - **Positive terminal** -> GPIO 15
  - **Negative terminal** -> GND

## Code Explanation
### `setup()` function:
- Initializes **Serial Monitor** for debugging.
- Initializes the **DHT22** sensor.
- Sets up the **LED** and **Buzzer** pins.
- Creates a FreeRTOS task to monitor temperature in real-time.

### `loop()` function:
- No operations in the `loop()` because all tasks are handled in the FreeRTOS task.

### `temperatureTask()` function:
- Reads the temperature from the **DHT22** sensor.
- Based on the temperature value:
  - **Overheat State**: If the temperature exceeds 35°C, the heater (LED) turns off, and the buzzer sounds.
  - **Heating State**: If the temperature is below 25°C, the heater (LED) turns on, and the buzzer is off.
  - **Idle State**: If the temperature is between 25°C and 35°C, both the heater (LED) and buzzer are off.

### FreeRTOS:
- The temperature reading and control logic are handled inside the **FreeRTOS task**, which runs in a loop and delays for 2 seconds before the next reading, ensuring the system is responsive in real-time.

## How to Run
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/yourusername/heater-control-system.git
