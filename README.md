# Real PKE Meter #

*This project is currently under development.  All components have been individually tested, however the final prototype has not been completed yet*

The goal of this project is to create a working PKE Meter (Ghostbusters) which is similar to the original's design however offers the below features:

## Current Status ##
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
- x1 Servo *(I used an SG90S)*
- x14 3mm LEDs
- x1 Piezo Speaker
- x1 0.96" OLED Display
- x8 100ohm Resistors
- x2 Buttons (Push)
- x2 Toggle Switches (For Power / Sound)
- 5V Power Source (I am currently testing with rechargeable battery + Powerboost 500)
- 3D Printer *(I use an Ender 3 Pro with PLA)*
- Wiring
- Custom PCB *(Optional - Will post if one is made)*

## Credit ##
This project is inspired by CountDeMonet's [Arduino_PKE_Meter](https://github.com/CountDeMonet/Arduino_PKE_Meter) which includes an OLED and LED wings, however was designed as a toy as all feedback is pre-programmed to occur with button presses and does not include sensors.



