//Real PKE Meter
//Revised 6/2/20 - BzowK

//ToDo
// Add menu options to adjust sound & sensitivity

// Pin Assignments
// vin/gnd - to power
// 5v/gnd - to rail
// A0 - Probe / Antenna
// A4 - SDA on Display
// A5 - SLC on Display
// D2 - LED pair #1
// D3 - LED pair #2
// D4 - LED pair #3
// D5 - LED pair #4
// D6 - LED pair #5
// D7 - LED pair #6
// D8 - LED pair #7
// D9 - Button 1
// D10 - Button 2
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

Servo servo;

DHT dht(DHTPIN, DHTTYPE);

int senseLimit = 15; int probePin = 0; int val = 0;
int speakerPin = 12;

const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int LED6 = 7;
const int LED7 = 8;

int buzzer = 12;
int buzzerTone = 0;

unsigned long previousMillis = 0; const long interval = 1000;

int readings[NUMREADINGS];
int index = 0;
int total = 0;
int average = 0;
int currentVal = 0;

void setup() {
  // Init Serial
  Serial.begin(9600);

  // Init DHT
  dht.begin();
  
  // Init Servo
  servo.attach(11);
  servo.write(110);
    
  // Init LEDs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  // Init Speaker
  pinMode(speakerPin, OUTPUT);

  // Init OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  }

void loop() {
  delay(200);
// EMF Probe
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

 servoControl();

// Speaker
  if (average > 0)
  tone(speakerPin, val / 3);
  else
  noTone(speakerPin);

//read temperature and humidity
  float f = dht.readTemperature(true);
  float h = dht.readHumidity();
  if (isnan(h) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(22, 5);
  
// Display static text
  display.println("Real PKE Meter");

// display temperature
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("Temperature: ");
  display.print(f);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.print("F");

  // display humidity
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
