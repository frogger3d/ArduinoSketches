    From: http://learn.adafruit.com/adafruit-motor-shield/using-dc-motors  
    8-wheel robot development, using DC Motors with Adafruit motorshield 
    demonstration of possibilities
    December 12 2013
	
motor-shield libs and sketches:
http://learn.adafruit.com/adafruit-motor-shield/downloads

LIBRARIES:
----------
Arduino Stepper/Servo software library with microstepping support.
To install, click on Downloads in the middle of the page, select Download as zip and uncompress the folder.
Rename the folder to AFmotor (check that the renamed folder contains the .cpp and .h files) and install into the Arduinosketches/libraries folder. For information how to use and install libraries, see our tutorial! This version now works with with the Mega. Public domain!

AccelStepper library with AFMotor support. This library allows for advanced stepper control including accelleration and decelleration, and concurrent stepper control! You still need AFmotor above!
To install, click on Download in the middle of the page, select Download as zip and uncompress the folder.
Rename the folder to AccelStepper (check that the renamed folder contains the .cpp and .h files) and install into the Arduinosketches/libraries folder. For information how to use and install libraries, see our tutorial!

SKETCH:
-------
driving a DC motor in forward and backward directions:
> http://learn.adafruit.com/adafruit-motor-shield/using-dc-motors
http://arduino.cc/en/Tutorial/DueMotorShieldDC 

My project:
-----------
Motor movement: DC_Motor/Adafruit02, use Motor 3 and Motor 4 => Timer0
Ultrasonic sensor: NewPing library, uses Timer2

Timers:
-------
The ATmega328P has three timers known as Timer 0, Timer 1, and Timer 2.  The ATmega168P/328P chip has three PWM timers, controlling 6 PWM outputs. Many Arduino functions uses timers, for example the time functions: delay(), millis() and micros(), the PWM functions analogWrite(), the tone() and the noTone() function, even the Servo library uses timers and interrupts.

The Arduino uses Timer 0 internally for the millis() and delay() functions, so be warned that changing the frequency of this timer will cause those functions to be erroneous. Using the PWM outputs is safe if you don't change the frequency, though. 

PWM frequencies on Timer 0, pins 5 and 6, Arduino Uno

the pins used by the timers on Arduino UNO are:
- PWM Pins 5 and 6: controlled by Timer0  - dc motor 3 and 4!
- PWM Pins 9 and 10: controlled by Timer1 - servomotor
- PWM Pins 11 and 3: controlled by Timer2  - dc motor 1 and 2

Timer0 is an 8-bit timer, it can hold a maximum value of 255. It is used by delay() and millis(), so there are consequences when messing with it.

Timer1 is a 16-bit timer, it can hold a maximum of 65535 (an unsigned 16-bit integer). The Arduino Servo library uses this timer
Timer2 is an 8-bit timer used by the Arduino tone() function.


    AdaFruit MotorShield
    ----------------------------------
    Digital:
    0 - 
    1 - 
    2 - 
    3 -  PWM2B
    4 -  DIR_CLK
    5 -  PWM0B
    6 -  PWM0A
    7 -  DIR_EN
    
    8 -  DIR_SER
    9 -  PWM1A
    10 - PWM1B
    11 - PWM2A
    12 - DIR_LATCH
    13 - 
    
    Analog
    0 - 
    1 - 
    2 - 
    3 - 
    4 - 
    5 - 
    ------------------------------------
    