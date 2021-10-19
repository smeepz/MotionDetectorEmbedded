# MotionDetectorEmbedded

A very basic intruder alarm, utilizing the HC-SR04 ultrasonic sensor.
The code is ready to be uploaded to the arduino as is.

The code is set up to guard an entry, where the opening is atleast 150cm. This can be modified.
If something obstructs the ultrasonic waves, the buzzer will turn on, the RGB-LED will turn red, 
and the TFT-display will say "INTRUDER" in red.
If there is no obstructions, the RGB-LED will remain green and the TFT-display will say "OK"

Parts:
- 1x HC-SR04
- 1x 1.14" TFT-screen from Adafruit
- 1x Generic buzzer
- 1x RGB-LED diode (4 legs)
- 3x 200ohm resistors
- Male to male cables
- 1x Breadboard
- 1x Arduino (The one used is arduino UNO rev. 3)

