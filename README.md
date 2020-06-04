# Real PKE Meter #

*This project is currently under development.  All components have been individually tested, however the final prototype has not been completed yet*

The goal of this project is to create a working PKE Meter (Ghostbusters) which is similar to the original's design however offers the below features:

## Current Status ##
**6/3/20** - Have all main components working via script and am printing revised case so all components fit correctly. Just updated the Fritzing diagram as well as Arduino IDE script in repo.  Will upload STLs for case once finished, assembled, and tested.  Also decided to replace pair of buttons with a rotary encoder with push-button for more flexibility.  Pending tasks are below:

- Fine-tune EMF detection in script
- Integrate rotary encoder with push-button + menu options (mute, adjust sensitivity, etc)
- Finish updating case
Will post full build guide and files once finished.

**3/10/20** - I've tested individual components using source code which I combined into the final code (Real-PKE-Meter.ino).  All that's left is to test individual components using final code, program OLED display as desired, then fit into model.  Model files are currently copies of [CountDeMonet's project](https://github.com/CountDeMonet/Arduino_PKE_Meter), but will probably have to modify due to added components.

## Features ##
- EMF Meter (LED Wings raise on stronger signal)
- Temperature & Humidity Readings
- Buzzer reflecting signal strength
- OLED display showing exact EMF reading, temperature, & humidity

Included *(& below)* is the initial breadboard layout which I'm currently testing.  The only addition I'm currently considering is a rocker switch to adjust sensitivity, however may try to add that via OLED screen.
![](https://github.com/BzowK/RealPKEMeter/blob/master/Fritzing/Real-PKE-Meter_bb.png)

## Parts ##
*Links to exact parts used will be posted once prototype is complete*

- x1 Arduino Nano
- x1 DHT22 Sensor
- x1 SG90S Servo
- x14 3mm LEDs (20ma)
- x1 Piezo Speaker
- x1 0.96" OLED Display
- x9 330ohm Resistors
- x2 1M Resistors
- x1 Rotary Encoder /w Push Button
- x1 SPDT Toggle Switch
- x1 Powerboost 500
- x1 18650 Battery
- 3D printed parts
- Wiring
- Custom PCB *(Optional - Will post if one is made)*

## Credit ##
This project is inspired by CountDeMonet's [Arduino_PKE_Meter](https://github.com/CountDeMonet/Arduino_PKE_Meter) which includes an OLED and LED wings, however was designed as a toy as all feedback is pre-programmed to occur with button presses and does not include sensors.



