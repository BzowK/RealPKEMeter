//Real PKE Meter
//Revised 6/4/20 - BzowK

//ToDo
// Add menu options to adjust sound & sensitivity

// Pin Assignments
// vin/gnd - to power
// 5v/gnd - to rail
// A0 - Probe / Antenna
// A4 - SDA on Display
// A5 - SLC on Display
// D1 - Rotary Encoder (Knob)
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

// Define Variables
  #define DHTPIN 13
  #define DHTTYPE DHT22
  #define NUMREADINGS 15
  #define OLED_RESET 10
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64

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

// Init Rotoary Encoder + Button
  int encoderPin1 = 2;
  int encoderPin2 = 3;
  int encoderSwitchPin = 1;
  volatile int lastEncoded = 0;
  volatile long encoderValue = 0;
  long lastencoderValue = 0;
  int lastMSB = 0;
  int lastLSB = 0;

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
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  pinMode(encoderSwitchPin, INPUT);
  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);
  digitalWrite(encoderSwitchPin, HIGH);
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
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
  //Do stuff here
  if(digitalRead(encoderSwitchPin)){
  //button is not being pushed
  }else{
  //button is being pushed
  }
  Serial.println(encoderValue);
  delay(1000); //just here to slow down the output, and show it will work even during a delay

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

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++; if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --; lastEncoded = encoded; //store this value for next time }
 }