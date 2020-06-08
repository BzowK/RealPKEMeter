//Real PKE Meter
//Revised 6/6/20 - BDK

// Current State
// Still has old display + menu sample

//ToDo
// Test Encoder
// Add menu with following options
// - Mute / unmute
// - Adjust EMF sensitivity
// - 

// Pin Assignments
// vin/gnd - to power
// 5v/gnd - to rail
// A0 - Probe / Antenna
// A4 - SDA on Display
// A5 - SLC on Display
// D1 - Rotary Encoder (Knob) (TX1)
// D2 - Rotary Encoder
// D3 - Rotary Encoder
// D4 - LED pair #1
// D5 - LED pair #2
// D6 - LED pair #3
// D7 - LED pair #4
// D8 - LED pair #5
// D9 - LED pair #6
// D10 - LED pair #7
// D11 - Servo Signal
// D12 - Piezo Buzzer
// D13 - DHT22

// Define Libraries
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <Servo.h>
  #include <DHT.h>
  #include <Wire.h>

// Define Variables
  #define DHTPIN 13
  #define DHTTYPE DHT22
  #define NUMREADINGS 15
  #define OLED_RESET 10
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define encoder0PinA  2 // D2
  #define encoder0PinB  3 // D3
  #define encoderButton 1 // TX1

// Init Init Rotoary Encoder + Button
  volatile unsigned int encoder0Pos = 0;
  int valA;
  int valB;
  int valC;
  byte clk;
  byte menuCount = 1;
  byte dir = 0;
  bool runState = false;
  
// Init OLED
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Init Servo
  Servo servo;

// Init DHT22
  DHT dht(DHTPIN, DHTTYPE);

// Init LEDs
  const int LED1 = 4;
  const int LED2 = 5;
  const int LED3 = 6;
  const int LED4 = 7;
  const int LED5 = 8;
  const int LED6 = 9;
  const int LED7 = 10;

// Init Speaker
  int speakerPin = 12;
  int buzzer = 12;
  int buzzerTone = 0;

// Init EMF
  int senseLimit = 15; int probePin = 0; int val = 0;
  unsigned long previousMillis = 0; const long interval = 1000;
  int readings[NUMREADINGS];
  int index = 0;
  int total = 0;
  int average = 0;
  int currentVal = 0;

void setup() {
// Setup Serial
  Serial.begin(9600);

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
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

//Setup Rotary Encoder + Button
  attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH); // turn on pull-up resistor
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH); // turn on pull-up resistor
  pinMode(encoderButton, INPUT);
  digitalWrite(encoderButton, HIGH); // turn on pull-up resistor
}
  
void loop() {
//  delay(200);
  
// Loop EMF Probe
  val = analogRead(probePin);
  if(val >= 1){
  val = constrain(val, 1, senseLimit); val = map(val, 1, senseLimit, 1, 1023);
  total -= readings[index]; readings[index] = val; total += readings[index]; index = (index + 1);
  if (index >= NUMREADINGS) index = 0;
  average = total / NUMREADINGS;
  if (val > 100) {digitalWrite(LED1, HIGH);} else {digitalWrite(LED1, LOW);}
  if (val > 250) {digitalWrite(LED2, HIGH);} else {digitalWrite(LED2, LOW);}
  if (val > 400) {digitalWrite(LED3, HIGH);} else {digitalWrite(LED3, LOW);}
  if (val > 550) {digitalWrite(LED4, HIGH);} else {digitalWrite(LED4, LOW);}
  if (val > 700) {digitalWrite(LED5, HIGH);} else {digitalWrite(LED5, LOW);}
  if (val > 850) {digitalWrite(LED6, HIGH);} else {digitalWrite(LED6, LOW);}
  if (val > 1000) {digitalWrite(LED7, HIGH); tone(buzzer, 1000);} else {digitalWrite(LED7, LOW); noTone(buzzer);}
  Serial.println("val: ");
  Serial.println(val);  
  }

// Loop Servo
  servoControl();

// Loop Speaker
  if (average > 0)
  tone(speakerPin, val / 3);
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
  
// Loop Rotary Encoder + Button
  clk = digitalRead(encoderButton);
  menuCheck();
  staticMenu();

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
  display.print(val);
  display.display();
 }

void servoControl(){
  int servoVal = map(val, 0, 1023, 110, 40);
  servo.write(servoVal);
  Serial.println("ServoVal: ");
  Serial.println(servoVal); 
 }

void staticMenu() {
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(10, 0);
  display.println("yyRobotic");
  //---------------------------------
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Value A:");
  display.setCursor(60, 20);
  display.println(valA);

  display.setCursor(10, 30);
  display.println("Value B:");
  display.setCursor(60, 30);
  display.println(valB);

  display.setCursor(10, 40);
  display.println("Value C:");
  display.setCursor(60, 40);
  display.println(valC);

  display.setCursor(10, 50);
  display.println("Start:");
  display.setCursor(45, 50);
  if (encoder0Pos > 5 && menuCount == 4) {
    display.println("Run!");
    runState = true;
  } else {
    display.println("Idle");
    runState = false;
  }
  display.setCursor(2, (menuCount * 10) + 10);
  display.println(">");

  display.display();
}

void menuCheck() {
  if (clk == LOW && menuCount < 5) {
    menuCount++;
    encoder0Pos = 0;
  }
  if (clk == LOW && menuCount >= 5) {
    menuCount = 1;
  }

  if (menuCount == 1) {
    valA = encoder0Pos;
  }
  if (menuCount == 2) {
    valB = encoder0Pos;
  }
  if (menuCount == 3) {
    valC = encoder0Pos;
  }
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
