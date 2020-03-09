/* Real-EMF-Meter
 *  by Ben KELLERMANNKellermann
 *  
 *  Pins
 *  D2 - LED 1&8
 *  D3 - LED 2&9
 *  D4 - LED 3&10
 *  D5 - LED 4&11
 *  D6 - LED 5&12
 *  D7 - LED 6&13
 *  D8 - LED 7&14
 *  D9 - Button 1
 *  D10 - Servo
 *  D11 - DHT22 Data
 *  D12 - Peizo Buzzer
 *  D13 - Button 2
 */

// Init EMF
int antennaPin = A0;
int trimPin = A1;
int speakerPin = 12;
int ledPinStart = 2;
int ledPins = 7;

// Init Servo
#include <Servo.h>
Servo myservo;
int pos = 0;

//Init OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Init DHT22
#include "DHT.h"
#define DHTPIN 11
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
char inChar;
String inString;

void setup () {
  Serial.begin(9600);
 // Setup EMF
  pinMode(antennaPin, INPUT);
  pinMode(trimPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  for (int pin = ledPinStart; pin < ledPinStart + ledPins; pin++) {
    pinMode(pin, OUTPUT);
  }
  // Setup Servo
  myservo.attach(10);

  // Setup OLED


  // Setup DHT
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  dht.begin();

}

void loop() {
 // Loop EMF
 int offsetReading = analogRead(trimPin);
  int antennaReading = analogRead(antennaPin) - offsetReading;
  int result = constrain(antennaReading, 1, 100);
  int resultMap = map(result, 1, 100, 1, 255);
  Serial.print(result);
  Serial.print("-");
  Serial.print(resultMap);
  Serial.print("-");
  int spread = 255 / ledPins;
  int maxPinSet = resultMap / spread;
  Serial.print(maxPinSet);
  Serial.print(" ");
  for (int pin = ledPinStart; pin < ledPinStart + ledPins; pin ++) {
    int validResultMap = spread * (pin - ledPinStart);    
    if (resultMap > validResultMap) 
      digitalWrite(pin, HIGH); 
    else
      digitalWrite(pin, LOW);      
  }
  if (maxPinSet > 0)
    tone(speakerPin, resultMap * 3);
  else
    noTone(speakerPin);

  // Loop Servo
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  // Loop OLED


  // Loop DHT
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
}

 // Extra OLED
 void displayOled() {

  // Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(5, 15);
  display.print("Humidity:");
  display.setCursor(80, 15);
  display.print(h);
  display.print("%");
  display.setCursor(5, 30);
  display.print("Temperature:");
  display.setCursor(80, 30);
  display.print(t);
  display.print((char)247); // degree symbol
  display.print("C");
  display.setCursor(5, 45);
  display.print("Heat Index:");
  display.setCursor(80, 45);
  display.print(hic);
  display.print((char)247); // degree symbol
  display.print("C");
  display.display();

}
