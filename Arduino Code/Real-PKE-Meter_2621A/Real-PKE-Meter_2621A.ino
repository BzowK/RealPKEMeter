/*
Real PKE Meter
Revised 2/6/21 - BzowK

New / Fixed:
- Replaced digitalWrite with direct port for faster processing
- Improved EMF detection
- Added rotary encoder /w button support
 
ToDo:
- Add menu options to adjust sound & sensitivity
- OLED Settings Menu
  - Sound On/Off
  - EMF Sensitivity
  - ...

Pin Assignments:
- VIN - 5V
- GND - Ground
- A0 - Probe / Antenna
- A4 - SDA on Display
- A5 - SLC on Display
- D1 - Rotary Button
- D2 - Rotary CLK
- D3 - Rotary DT
- D4 - LED pair #1
- D5 - LED pair #2
- D6 - LED pair #3
- D7 - LED pair #4
- D8 - LED pair #5
- D9 - LED pair #6
- D10 - LED pair #7
- D11 - Servo Signal
- D12 - Piezo Buzzer
- D13 - DHT22
*/

//Libraries
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <Servo.h>
  #include <DHT.h>
  #define DHTPIN 13
  #define DHTTYPE DHT22
  #define NUMREADINGS 15
  #define OLED_RESET 10
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define encoder0PinA  2
  #define encoder0PinB  3
  #define encoderButton 1
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Init Servo
  Servo servo;

// Init DHT22
  DHT dht(DHTPIN, DHTTYPE);

// Init EMF
  int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
  int probePin = 0;
  int val = 0;

// Init EMF Smoothing
  int readings[NUMREADINGS];
  int index = 0;
  int total = 0;
  int average = 0; 
  int turn_time = 100;
  int servoVal = 0;

// Init LED
  const int LED1 = 4;
  const int LED2 = 5;
  const int LED3 = 6;
  const int LED4 = 7;
  const int LED5 = 8;
  const int LED6 = 9;
  const int LED7 = 10;

// Init Buzzer
  int speakerPin = 12;
  int buzzer = 12;
  int buzzerTone = 0;

// Init Rotary Encoder
  byte clk;
  byte dir = 0;
  volatile unsigned int encoder0Pos = 0;

void setup() {

// Setup Serial
  Serial.begin(115200);

// Setup EMF Smoothing 
  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;

// Setup DHT22
  dht.begin();

// Setup Servo
  servo.attach(11);
  servo.write(110);
    
// Setup LEDs
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

// Setup Speaker
  pinMode(speakerPin, OUTPUT);

// Setup OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE); 

 // Setup Rotary Encoder
  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);
  pinMode(encoderButton, INPUT);
  digitalWrite(encoderButton, HIGH);
  attachInterrupt(0, doEncoder, CHANGE);
  }

void loop() {

//Loop EMF
  val = analogRead(probePin);
  if(val >= 1){
    val = constrain(val, 1, senseLimit); 
    val = map(val, 1, senseLimit, 1, 1023); 
    total -= readings[index];
    readings[index] = val;
    total += readings[index];
    index = (index + 1);
    if (index >= NUMREADINGS)
      index = 0;
    average = total / NUMREADINGS;
    servoVal = map(average, 0, 1023, 110, 40);
    turn_time = map(average, 0, 1023, 200, 5);
    
// Loop LEDs
  LEDPattern();

// Loop Servo  
  AdServo();

// Write to Console for Testing & Calibrating
  Serial.println("val:");
  Serial.println(val);
  Serial.println("average:");
  Serial.println(average);
  Serial.print("turn_time: ");
  Serial.println(turn_time);
  Serial.print("ServoVal: ");
  Serial.println(servoVal);
  }

// Loop Speaker
  if (average > 0)
    tone(speakerPin, average / 3);
  else
    noTone(speakerPin);

// Loop DHT22
  float f = dht.readTemperature(true);
  float h = dht.readHumidity();
  if (isnan(h) || isnan(f)) {
  Serial.println("Failed to read from DHT sensor!");
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(22, 5);
  
// Loop OLED
  // Static Title
    display.println("Real PKE Meter");

  // Display Temperature
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print("Temperature: ");
    display.print(f);
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true);
    display.write(167);
    display.print("F");

  // Display Humidity
    display.setTextSize(1);
    display.setCursor(12, 30);
    display.print("Humidity: ");
    display.print(h);
    display.print(" %"); 

  // Display EMF Strength Value
    display.setTextSize(1);
    display.setCursor(15, 40);
    display.print("EMF Strength: ");
    display.print(average);
    display.display();

// Loop Rotary Encoder
  clk = digitalRead(encoderButton);
  }

void LEDPattern () {
  PORTD |= (1 << PD4);
  delay(turn_time);
  PORTD &= ~(1 << PD4);
  delay(turn_time);
  PORTD |= (1 << PD6);
  delay(turn_time);
  PORTD &= ~(1 << PD6);
  delay(turn_time);
  PORTB |= (1 << PB0);
  delay(turn_time);
  PORTB &= ~(1 << PB0);
  delay(turn_time);
  PORTB |= (1 << PB2);
  delay(turn_time);
  PORTB &= ~(1 << PB2);
  delay(turn_time);
  PORTB |= (1 << PB1);
  delay(turn_time);
  PORTB &= ~(1 << PB1);
  delay(turn_time);
  PORTD |= (1 << PD7);
  delay(turn_time);
  PORTD &= ~(1 << PD7);
  delay(turn_time);
  PORTD |= (1 << PD5);
  delay(turn_time);
  PORTD &= ~(1 << PD5);
  }

void AdServo () {
  servo.write(servoVal);
  }

void doEncoder() {
  if (digitalRead(encoder0PinA) == HIGH) {
    if (digitalRead(encoder0PinB) == LOW && encoder0Pos > 0) {
      encoder0Pos = encoder0Pos - 1;
      dir = 0;
    }
    else {
      encoder0Pos = encoder0Pos + 1;
      dir = 1;
    }
  }
  else
  {
    if (digitalRead(encoder0PinB) == LOW ) {
      encoder0Pos = encoder0Pos + 1;
      dir = 1;
    }
    else {
      if (encoder0Pos > 0) {
        encoder0Pos = encoder0Pos - 1;
        dir = 0;
      }
    }
  }
}
