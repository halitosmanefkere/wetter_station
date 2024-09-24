## Weather Station - Arduino Weather Monitoring System

This project implements an **Arduino-based weather station** capable of measuring **wind speed**, **temperature**, and **humidity**. 
The results are displayed on a **1602 LCD** with I2C interface.

### Features

- **Wind Speed Measurement**: Displays wind speed in km/h and classifies the speed with categories such as "Light", "Medium", "Strong", etc.
- **Temperature and Humidity Measurement**: Displays current temperature in Celsius (°C) and humidity as a percentage (%).
- **Pin Input Feature**: Custom pin input for extending the functionality or adding extra sensors.

### Pinout Connections

If you want to recreate this weather station, here are the required components and their corresponding pin connections:

#### 1. **Arduino Uno** or a compatible board
#### 2. **DHT11 Sensor** (for temperature and humidity)
   - **Signal Pin**: Connect to **Pin 2** on Arduino
   - **VCC**: 5V on Arduino
   - **GND**: GND on Arduino

#### 3. **Anemometer** (for wind speed measurement)
   - **Signal Pin**: Connect to **Pin 3** on Arduino
   - **VCC**: 5V on Arduino
   - **GND**: GND on Arduino

#### 4. **1602 I2C LCD Display** (for displaying the data)
   - **SDA**: Connect to **A4** (SDA pin) on Arduino
   - **SCL**: Connect to **A5** (SCL pin) on Arduino
   - **VCC**: 5V on Arduino
   - **GND**: GND on Arduino

#### 5. **Pin Input Feature**
   - **Pin 4**: Reserved for custom input. You can use this pin for additional features, like a button or another sensor.

### Installation Instructions

1. **Wire the Components**: Connect the components according to the pinout diagram above.
2. **Upload the Code**: Open the `weather_station.ino` file in your Arduino IDE. Ensure you have the necessary libraries installed (DHT and LCD libraries).
3. **Power Up the Arduino**: Once the wiring is done and the code is uploaded, power the Arduino board. You should see the **wind speed**, **temperature**, and **humidity** displayed on the LCD.
4. **Test the Setup**: Use a fan or natural wind to test the wind speed, and check the other values on the LCD.

### Customization

The pin input feature can be customized based on your project needs. You can attach additional sensors or buttons to **Pin 4** to add more functionality to the system.

### Demonstration

Here’s a demonstration of the project in action:

- [Demo](https://youtu.be/DbQ6XrFmaJk)


### Special Thanks

Thanks to the **AEQ-WEB Blog** by **Alex & And**, whose tutorial helped guide me through this project. You can find their blog here: [AEQ-WEB Blog](https://www.aeq-web.com).
