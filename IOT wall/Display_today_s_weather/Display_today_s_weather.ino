#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <DHT_U.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 2         // DHT11 data pin
#define DHTTYPE DHT11    // DHT11 sensor type
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temperature = event.temperature;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Temperature: " + String(temperature, 1) + "°C");
  display.display();

  Serial.print("Temperature: ");
  Serial.println(temperature);

  delay(1000);  // Update every 1 second
}
