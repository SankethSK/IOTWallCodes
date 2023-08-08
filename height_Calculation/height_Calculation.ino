#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int triggerPin = 2;  // Trigger pin of the USS
const int echoPin = 3;     // Echo pin of the USS
const float referenceHeight = 7.0;  // Height of the sensor from the ground in feet

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initial setup...");

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Trigger the USS to send a pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure the time it takes for the pulse to return
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in inches
  float distanceInches = duration * 0.0133 / 2.0;

  // Convert distance to feet
  float distanceFeet = distanceInches / 12.0;

  // Calculate person's height
  float personHeight = referenceHeight - distanceFeet;

  // Clear the display
  display.clearDisplay();

  // Print the calculated values on OLED
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distanceFeet, 2);
  display.println(" ft");

  display.print("Person's Height: ");
  display.print(personHeight, 2);
  display.println(" ft");

  display.display();

  // Print the calculated values on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceFeet, 2);
  Serial.print(" feet\t");
  Serial.print("Person's Height: ");
  Serial.print(personHeight, 2);
  Serial.println(" feet");

  delay(1000); // Delay before the next measurement
}
