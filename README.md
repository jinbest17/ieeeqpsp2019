# ieeeqpsp2019

PIR SENSOR:

How we use it:
Detect Motion outside hallway for theft alert (someone trying to pick the lock)

Pin info: gnd, dout, vcc
Input voltage: 3.3v/5v

Bottom two pins connected: In “H” mode the output pin Dout will go high (3.3V) when a person is detected within range and goes low after a particular time (time is set by potentiometer). In this mode the output pin will go high irrespective of whether the person is still present inside the range or has left the area. We are using our module in “H” mode in our project.

Top two pins connected: In “I” mode the output pin Dout will go high (3.3V) when  a person is detected within range and will stay high as long as he/she stays within the limit of the Sensors range. Once the person has left the area the pin will go low after the particular time which can be set using the potentiometer.

References: https://www.circuitmagic.com/arduino/pir-motion-sensor-with-arduino/

LCD Display with i2c breakout: 

How we use it:
User Interaction- Prompt and respond to user's actions

References: How to connect an Lcd Display to an Arduino Uno Tutorial
https://www.youtube.com/watch?v=xVC0X_PE_XE&t=127s
http://www.techydiy.org/how-to-connect-an-i2c-lcd-display-to-an-arduino-uno/

Associated Libraries:
NewLiquidCrystal:
https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
