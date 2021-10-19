
int transmitterPin = 3;
int recieverPin = 2;

<<<<<<< HEAD
int buzzerPin = A0;

int redLedPin = 5;
int blueLedPin = 6;
int greenLedPin = 7;

long duration;
long cm;

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

=======
int buzzerPin = 4;

int redLedPin = 13;
int blueLedPin = 12;
int greenLedPin = 11;

long duration;
long cm;
>>>>>>> 996dac376084f7fafdc7d2b5215107236b24ac3e

void setup() {

  Serial.begin(9600);

<<<<<<< HEAD
// OR use this initializer (uncomment) if using a 1.14" 240x135 TFT:
  tft.init(135, 240);           // Init ST7789 240x135

=======
>>>>>>> 996dac376084f7fafdc7d2b5215107236b24ac3e
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

<<<<<<< HEAD
void testdrawtext(char *text, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

=======
>>>>>>> 996dac376084f7fafdc7d2b5215107236b24ac3e
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
<<<<<<< HEAD
    testdrawtext("OK", ST77XX_GREEN);
    digitalWrite(buzzerPin, LOW);
  } else {
    Serial.println("--------!WARNING!");
    ledLightColor(255, 0, 0);
    testdrawtext("INTRUDER", ST77XX_RED);
=======
  } else {
    Serial.println("--------!WARNING!");
    ledLightColor(255, 0, 0);
>>>>>>> 996dac376084f7fafdc7d2b5215107236b24ac3e
    digitalWrite(buzzerPin, HIGH);
  }

  Serial.print(cm);
  Serial.print("cm");
  Serial.println(); //Format prints
  delay(1000);
}
