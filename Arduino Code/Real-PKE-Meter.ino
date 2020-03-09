int antennaPin = A0;
int trimPin = A1;
int speakerPin = 12;
int ledPinStart = 2;
int ledPins = 7;

void setup () {
  Serial.begin(9600);
  // Serial.println("EMF DETECTOR 1.0");

  pinMode(antennaPin, INPUT);
  pinMode(trimPin, INPUT);
  pinMode(speakerPin, OUTPUT);

  for (int pin = ledPinStart; pin < ledPinStart + ledPins; pin++) {
    pinMode(pin, OUTPUT);
    // Serial.print("CONFIG ");
    // Serial.println(pin);
  }
}

void loop() {
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

  /* turn on LEDs */
  for (int pin = ledPinStart; pin < ledPinStart + ledPins; pin ++) {
    int validResultMap = spread * (pin - ledPinStart);    
    if (resultMap > validResultMap) 
      digitalWrite(pin, HIGH); 
    else
      digitalWrite(pin, LOW);      
  }

  /* play audio */
  if (maxPinSet > 0)
    tone(speakerPin, resultMap * 3);
  else
    noTone(speakerPin);
}
