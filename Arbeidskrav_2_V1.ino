
int pirSensorPin = 4;
int transmitterPin = 3;
int recieverPin = 2;
long duration;
long cm;
int ledPin = 13;
int buzzerPin = 12;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(transmitterPin, OUTPUT);
  
  pinMode(recieverPin, INPUT);
  pinMode(pirSensorPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
}

void loop() {


  rangeIndicator();
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
    digitalWrite(ledPin, LOW);
  } else {
    Serial.println("--------!WARNING!");
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  }

  Serial.print(cm);
  Serial.print("cm");
  Serial.println(); //Format prints
  delay(1000);
}
