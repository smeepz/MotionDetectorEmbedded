
int transmitterPin = 3;
int recieverPin = 2;

int buzzerPin = 4;

int redLedPin = 13;
int blueLedPin = 12;
int greenLedPin = 11;

long duration;
long cm;

void setup() {

  Serial.begin(9600);

  pinMode(transmitterPin, OUTPUT);
  pinMode(recieverPin, INPUT);


  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

}

void loop() {


  rangeIndicator();
}

void ledLightColor(int redValue, int greenValue, int blueValue) {
    analogWrite(redLedPin, redValue);
    analogWrite(greenLedPin, greenValue);
    analogWrite(blueLedPin, blueValue);
}

void rangeIndicator() {

  digitalWrite(transmitterPin, LOW);
  delayMicroseconds(5);
  digitalWrite(transmitterPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(transmitterPin, LOW);

  pinMode(recieverPin, INPUT);
  duration = pulseIn(recieverPin, HIGH);

  cm = (duration / 2) / 29.1; //The calculation for centimeters

  if (cm >= 150) {
    Serial.println("--------OK");
    ledLightColor(0, 255, 0);
  } else {
    Serial.println("--------!WARNING!");
    ledLightColor(255, 0, 0);
    digitalWrite(buzzerPin, HIGH);
  }

  Serial.print(cm);
  Serial.print("cm");
  Serial.println(); //Format prints
  delay(1000);
}
