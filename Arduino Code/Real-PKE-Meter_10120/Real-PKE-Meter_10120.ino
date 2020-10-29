//Real PKE Meter
//Revised 10/1/20 - BzowK

//ToDo
// Add menu options to adjust sound & sensitivity

// Pin Assignments
// vin/gnd - to power
// 5v/gnd - to rail
// A0 - Probe / Antenna
// A4 - SDA on Display
// A5 - SLC on Display
// A7 - Rotary Switch
// D2 - Rotary CLK
// D3 - Rotary DT
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

//Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <DHT.h>
#define DHTPIN 13     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22     // DHT 22
#define NUMREADINGS 15
#define OLED_RESET 10
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Init Servo
Servo servo;

// Init DHT
DHT dht(DHTPIN, DHTTYPE);

// Rotary Encoder Module connections
volatile boolean TurnDetected;
const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=3;    // Reading DT signal
//const int PinSwitch=4;

// Init EMF
int senseLimit = 15; int probePin = 0; int val = 0; int conval = 0;
unsigned long previousMillis = 0; const long interval = 1000;
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int average = 0;
int currentVal = 0;

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

void setup() {
// Setup Serial
  Serial.begin(115200);

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
  attachInterrupt (0,rotarydetect,CHANGE);
  }
  
void loop() {
  delay(1000);
  
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
    if (val > 1000) {digitalWrite(LED7, HIGH); tone(buzzer, 1000);} else {digitalWrite(LED7, LOW); noTone(buzzer);conval = val;}
   }
  Serial.print("val: ");
  Serial.println(val);
  Serial.print("conval: ");
  Serial.println(conval);

// Loop Servo
    int servoVal = map(conval, 0, 1023, 110, 40);
    servo.write(servoVal);
    Serial.print("ServoVal: ");
    Serial.println(servoVal);

// Loop Speaker
  if (average > 0)
  tone(speakerPin, conval / 3);
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
  display.print(conval);
  display.display();

// Loop Rotary Encoder + Button
  if (TurnDetected)  { // rotary has been moved
      TurnDetected = false;  // do NOT repeat IF loop until new rotation detected 
      Serial.print("CLK Pin: ");
      Serial.println(digitalRead(PinCLK));
      Serial.print("DT Pin: ");
      Serial.println(digitalRead(PinDT));
      delay(5);
  }
}

void rotarydetect ()  {
  TurnDetected = true;  // set variable to true
}


 
