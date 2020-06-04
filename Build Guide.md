# Real PKE Meter: Build Guide #

*This guide is currently under development*

## What You'll Need ##
**Parts**

Below are the exact parts I used.  Some may be substituted as desired, but code may need to be altered for them to work properly.

- x1 Arduino Nano *(Without headers preinstalled)*
- x1 DHT22 Sensor
- x1 SG90S Servo
- x14 3mm LEDs (20ma)
- x1 Piezo Speaker
- x1 0.96" OLED Display
- x2 330ohm Resistors
- x2 1M Resistors
- x1 Rotary Encoder /w Push Button
- x1 SPDT Toggle Switch
- x1 Powerboost 500 *(Without headers or ports  preinstalled)*
- x1 18650 Battery
- 3D printed parts
- 24 gauge wiring *(or stripped CAT5/CAT6 cable)*
- 22 gauge wiring *(optional?)*
- Shrink tubing

**Tools**

- 3D Printer *(or can order parts)*
- Soldering iron / solder
- Wire clippers / strippers
- Calipers or other measuring device *(Although I am located in the USA, this guide uses metric)*

## Important Notes ##

- I opted to not use a perfboard or custom PCB, but may design & add one in the future

- It is suggested (although not necessary) to test all components with code on a breadboard prior to assembly - especially if substituting parts.

# Procedure #
## Preparation ##
**1. Print or Order Parts**

**2. Prepare Hardware**

- Test on breadboard prior to assembly *(Optional)*
- Ensure all headers are removed to save space
- For each LED, trim the anode *(longer, positive)* down to ~4mm and trim the cathode *(shorter, negative)* down to ~5mm,  Once done, bend the anode at the base of the LED 90 degrees.  Bend the cathode 180 degrees to form a "U".


**3. Prepare Wiring**

Cut the wire lengths listed below...

*I used 22 gauge for everthing except where noted so that things fit correctly.  Noted colors do not matter & are used to keep straight their intention*

**LEDs**

- Cut x14 150mm *(24 gauge)* wires.  Solder one end of each to the 90 degree bent anode end of each of the 14 LEDs.
- Cut x2 200mm wires.  Strip 60mm off one end leaving that much base wire showing 

**Battery / Power**

 - x1 200mm Red
 -  

Using some of the above wires, solder the noted resistor inline between each noted pair - each resulting in a single cable.

## Assembly ##
**LEDs / Wings**

1. String the wire of each of the 7 LEDs though the upper part of the wing
2. Super glue each LED in place
3. Run the bare end of the 200mm through the wing and thread it through the "U" of each of the LEDs
4. Apply a bit of solder on each of the "U" connections  


