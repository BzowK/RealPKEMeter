# Real PKE Meter #

*This project is currently under development*

The goal of this project is to create a "working" PKE Meter (Ghostbusters) which is similar to the original's design however offers the below features:
## Features ##
- EMF Meter (LED Wings raise on stronger signal)
- Temperature & Humidity Readings
- Buzzer reflecting signal strength
- OLED display showing exact EMF reading, temperature, & humidity

Included *(& below)* is the initial breadboard layout which I'm currently testing.  The only addition I'm currently considering is a rocker switch to adjust sensitivity, however may try to add that via OLED screen.
![](https://github.com/BzowK/RealPKEMeter/blob/master/Fritzing/Real-PKE-Meter_bb.png)

## Current Status - 10/29/20 ##
**10/29/20** - Finished prototype #1.  Didn't have time to get everything working the way I wanted, so finished it without a couple of features and with a couple of modifications so i could finish testing.  Below are lists of modifications made to finish first prototype plus changes planned for prototype #2 after testing...

**1st Prototype Modifications**

- Scaled model up 115% to ensure components & wiring fit *(Including modifying wings to use 5mm LEDs)*
- Optimized LED wiring
- Disabled rotary encoder
- Did not add menu / option selection on OLED
- Added physical switch to mute piezo speaker (since no menu option)
- Added 18650 battery case in handle

**Notes**

- The 1st prototype was printed in white I had abundance of then spray painted so apologies for rough look.  2nd prototype will use filament in correct color instead 
- *The "Model/Modified" folder contains the 115% models with 5mm LEDs.  For model parts not included in this folder, load the "Model/Original" version in slicer and scale up 115%*


**Changes Currently Being Considered for Prototype #2**

*The #1 thing I've learned from the prototype is that despite the EMF code working as desired when testing on a breadboard without other components attached but same code, I get nowhere near the same result when assembled in prototype.  I'm assuming this is from interference from other components & power lines due to lack of shielding on antenna cable.*

- Find and implement shielding solution for EMF antenna 
- Integrate rotary encoder plus menu system to control audio, EMF sensitivity, scan rate, etc.
- LED animation - *Example: Have them scan top to bottom slowly and get faster depending on signal strength*
- Add external USB port for charging and/or Arduino programming
- Considering alternative power source with smaller footprint

## Old Updates ##
**6/3/20** - Have all main components working via script and am printing revised case so all components fit correctly. Just updated the Fritzing diagram as well as Arduino IDE script in repo.  Will upload STLs for case once finished, assembled, and tested.  Also decided to replace pair of buttons with a rotary encoder with push-button for more flexibility.  Pending tasks are below:

- Fine-tune EMF detection in script
- Integrate rotary encoder with push-button + menu options (mute, adjust sensitivity, etc)
- Finish updating case
Will post full build guide and files once finished.

**3/10/20** - I've tested individual components using source code which I combined into the final code (Real-PKE-Meter.ino).  All that's left is to test individual components using final code, program OLED display as desired, then fit into model.  Model files are currently copies of [CountDeMonet's project](https://github.com/CountDeMonet/Arduino_PKE_Meter), but will probably have to modify due to added components.

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

***The build guide will be updated in detail after finishing 2nd prototype***

## Credit ##
This project is inspired by CountDeMonet's [Arduino_PKE_Meter](https://github.com/CountDeMonet/Arduino_PKE_Meter) which includes an OLED and LED wings, however was designed as a toy as all feedback is pre-programmed to occur with button presses and does not include sensors.



