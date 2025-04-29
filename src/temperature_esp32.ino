
#include <OneWire.h>
#include <DallasTemperature.h>
#include "thingProperties.h"

// Pin configuration for DS18B20
const int oneWireBus = 26;// Replace with the actual pin your DS18B20 is connected to

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  // Connect DS18B20 sensor
  sensors.begin();
}

void loop() {
  ArduinoCloud.update();
  
  // Read temperature from DS18B20
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  
  temperature = temp;

  Serial.println(temperature);

  // Update the temperature property in the IoT Cloud
  //temperatureProperty = temperature;

  delay(1000); 
  
}
void onTemperatureChange()  {
  // Get the new temperature value from the IoT Cloud
  //float newTemperature = temperature;
  // Display the new temperature value
  Serial.print("Temperature change to: ");
  Serial.println(temperature);
}
