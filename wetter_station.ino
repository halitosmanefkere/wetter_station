#include <Bonezegei_LCD1602_I2C.h>
#include <DHT.h>

// DHT11 Sensor Setup
#define DHTPIN 2         // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11    // DHT 11
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// Anemometer Setup
const int RecordTime = 3; // Define Measuring Time (Seconds)
const int SensorPin = 3;  // Define Interrupt Pin (Pin 3)
int InterruptCounter;
int WindSpeed;  // Changed to integer to remove decimal places

// LCD Setup
Bonezegei_LCD1602_I2C lcd(0x27); // Initialize LCD with I2C address 0x27

void setup() {
  Serial.begin(9600);    // Initialize Serial Monitor for debugging
  dht.begin();           // Initialize DHT sensor
  lcd.begin();           // Initialize LCD
  lcd.clear();
}

void loop() {
  // Measure Wind Speed
  meassureWindSpeed();
  
  // Debug: Print the wind speed value to the serial monitor
  Serial.print("Gemessene Windgeschwindigkeit: ");
  Serial.print(WindSpeed);
  Serial.println(" km/h");

  // Measure Temperature and Humidity
  float temperature = dht.readTemperature();  // Read temperature in Celsius
  float humidity = dht.readHumidity();        // Read humidity in percentage
  
  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    lcd.setPosition(0, 1);
    lcd.print("Fehler DHT Lesen");
    return;
  }

  // Convert WindSpeed to string (ensure it is properly displayed as numbers)
  char windSpeedStr[6];  // Adjusted to hold a 5-character wind speed
  itoa(WindSpeed, windSpeedStr, 10);  // Convert integer WindSpeed to string

  // Get wind speed category based on WindSpeed in km/h
  String windCategory = kategorisiereWindgeschwindigkeit(WindSpeed);

  // Convert temperature and humidity to strings
  char temperatureStr[6];
  dtostrf(temperature, 4, 1, temperatureStr);  // Convert temperature to string with 1 decimal

  char humidityStr[6];
  dtostrf(humidity, 4, 1, humidityStr);  // Convert humidity to string with 1 decimal
  
  // Display Data on LCD
  lcd.clear();
  
  // Top Left: Wind Speed (in km/h)
  lcd.setPosition(0, 0);
  lcd.print("W: ");
  lcd.print(windSpeedStr);  // Display wind speed as number
  lcd.print(" km/h");    // Add km/h unit to wind speed
  
  // If WindSpeed > 0, display the category
  if (WindSpeed > 0) {
    lcd.setPosition(10, 0);  // Adjust to fit
    lcd.print(windCategory.c_str());
  }
  
  // Bottom Left: Temperature (T: xx°C)
  lcd.setPosition(0, 1);
  lcd.print("T:");
  lcd.print(temperatureStr);  // Temperature in Celsius
  lcd.print((char)223);  // Print degree symbol (°)
  lcd.print("C");
  
  // Bottom Right: Humidity (H: xx%)
  lcd.setPosition(10, 1);  // Adjust to fit
  lcd.print("H:");
  lcd.print(humidityStr);  // Humidity in percentage
  lcd.print("%");
  
  delay(2000);  // Update every 2 seconds
}

// Function to measure wind speed
void meassureWindSpeed() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING);
  delay(1000 * RecordTime);  // Wait for the RecordTime to pass
  detachInterrupt(digitalPinToInterrupt(SensorPin));

  // Calculate wind speed (km/h) and convert to integer (remove decimals)
  WindSpeed = (int)((float)InterruptCounter / (float)RecordTime * 2.4);
  
  // Debug: Print Interrupt Counter value
  Serial.print("Interrupt Counter: ");
  Serial.println(InterruptCounter);
}

// Interrupt handler for the anemometer
void countup() {
  InterruptCounter++;
}

// Function to categorize wind speed using shortened names to fit within 7 characters
String kategorisiereWindgeschwindigkeit(int speed) {
  if (speed < 2) return "Still";  // 0-1 km/h: Calm
  else if (speed < 6) return "Leicht";  // 2-5 km/h: Light Breeze
  else if (speed < 12) return "Leicht+";  // 6-11 km/h: Light+
  else if (speed < 20) return "Mittel";  // 12-19 km/h: Moderate
  else if (speed < 29) return "Mittel+";  // 20-28 km/h: Moderate+
  else if (speed < 39) return "Stark";   // 29-38 km/h: Strong
  else if (speed < 50) return "Stark+";  // 39-49 km/h: Strong+
  else if (speed < 62) return "Sturm";  // 50-61 km/h: Gale
  else if (speed < 75) return "Sturm+";  // 62-74 km/h: Gale+
  else return "Orkan+";  // 75+ km/h: Hurricane+
}
