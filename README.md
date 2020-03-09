# Real PKE Meter #

*This project is currently under development*

The goal of this project is to create a working PKE Meter (Ghostbusters) which is similar to the original's design however offers the below features:

## Current Status ##
3/10/20 - I have all parts assembled on breadboard, model printed, plus separate code which successfully operates individual components.  All that's left is combining code into single script then trying to fit everything into model.  Model files are currently from [CountDeMonet's project](https://github.com/CountDeMonet/Arduino_PKE_Meter), but may have to modify eventually.

## Features ##
- EMF Meter (LED Wings raise on stronger signal)
- Temperature & Humidity Readings
- Buzzer reflecting signal strength
- OLED display showing exact EMF reading, temperature, & humidity

Included (& below) is the initial breadboard layout which I'm currently testing.  The only addition I'm currently considering is a rocker switch to adjust sensitivity, however may try to add that via OLED screen.
![](https://github.com/BzowK/RealPKEMeter/blob/master/Fritzing/Real-PKE-Meter_bb.png)

## Parts ##
*Links to exact parts used will be posted once prototype is complete*

- Arduino Nano
- DHT22 Sensor
- Servo *(I used an SG90S)*
- x14 3mm LEDs
- Piezo Speaker
- 0.96" OLED Display
- x8 100ohm Resistors
- x2 Buttons (Push)
- x2 Toggle Switches (For Power / Sound)
- 5V Power Source (I am currently testing with rechargeable battery + Powerboost 500)
- 3D Printer *(I use an Ender 3 Pro with PLA)*

## Credit ##
This project is inspired by CountDeMonet's [Arduino_PKE_Meter](https://github.com/CountDeMonet/Arduino_PKE_Meter) which includes an OLED and LED wings, however was designed as a toy as all feedback is pre-programmed to occur with button presses and does not include sensors.



