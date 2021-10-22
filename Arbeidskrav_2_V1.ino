
int transmitterPin = 3;
int recieverPin = 2;

int buzzerPin = A0;

int redLedPin = 5;
int blueLedPin = 7;
int greenLedPin = 6;

long duration;
long cm;

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique18pt7b.h>

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

#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#define countof(a) (sizeof(a) / sizeof(a[0]))

// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


void setup() {

  Serial.begin(9600);

  // OR use this initializer (uncomment) if using a 1.14" 240x135 TFT:
  tft.init(135, 240);           // Init ST7789 240x135

  pinMode(transmitterPin, OUTPUT);
  pinMode(recieverPin, INPUT);


  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  Rtc.Begin();
  RtcDateTime now = Rtc.GetDateTime();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);

}

void loop() {

  rangeIndicator();
  delay(2000);
}

void drawText(char *text, uint16_t color) {
  tft.setRotation(1);
  tft.setFont(&FreeMonoBoldOblique18pt7b);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 25);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void ledLightColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redLedPin, redValue);
  analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
}

void rangeIndicator() {
  RtcDateTime now = Rtc.GetDateTime();
  digitalWrite(transmitterPin, LOW);
  delayMicroseconds(5);
  digitalWrite(transmitterPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(transmitterPin, LOW);

  pinMode(recieverPin, INPUT);
  duration = pulseIn(recieverPin, HIGH);

  char timeStamp[6];

  cm = (duration / 2) / 29.1; //The calculation for centimeters
  if (cm >= 150) {
    ledLightColor(0, 255, 0);
    char bufOk[10];
    char msgOk[3] = "OK";
    timeStamp[6] = printDateTime(now);
    strcat(bufOk, timeStamp);
    strcat(bufOk, " ");
    strcat(bufOk, msgOk);
    drawText(bufOk, ST77XX_GREEN);
    digitalWrite(buzzerPin, LOW);
  } else {
    ledLightColor(255, 0, 0);
    char bufAlert[13];
    char msgAlert[6] = "ALERT";
    timeStamp[6] = printDateTime(now);
    strcat(bufAlert, timeStamp);
    strcat(bufAlert, " ");
    strcat(bufAlert, msgAlert);
    drawText(bufAlert, ST77XX_RED);
    digitalWrite(buzzerPin, HIGH);
  }
  delay(750);
}

char printDateTime(const RtcDateTime& dt)
{
  char datestring[6];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u:%02u"),
             dt.Hour(),
             dt.Minute()
            );
  return datestring;
}
