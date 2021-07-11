## Intro
Controlling cheap bldc (CMC_24H) with integrated encoder using a BGC 3.2 (brushless gimbal controller) and SimpleFOC.

## Origin
CMC_24H series BLDC motors (used in printers and other appliances) are available widely for very low price (due to mass production), it also has an included optical encoder making them great for hobby robotics projects. However, the standard control board that comes with the motor does not provide any method for torque control. 

Using SimpleFOC, we can use cheap commercially available boards such as the BGC 3.2, which only costs CAD $15 and can control two motors at the same time. SimpleFOC will then give us the ability of force control. 
The BGC is supposedly rated for 10A (although unclear if it is 5A per motor or 10A per motor, the mosfets seems to be able to handle 10A per motor, but it is untested). We can assume at least 5A per motor to be conservative. 
However, since the CMC_24H is rated for 0.7A, we can well cover its current needs. 

The total price is only $20 or $25 for two motors. 
| Item  | Price (CAD) |
|-------|-------------|
| BGC   |          15 |
| Motor |           5 |
| TOTAL |          20 |

## Steps
>Flash Arduino Onto BGC 3.2
There are many ways to burn the Arduino bootloader on an ATMEL chip, but the simplest method is just to use the USBAsp. They cost a few bucks and the flashing is fairly reliable. 
 - Connect all the pins (SPI)
 - Under Arduino IDE, select USBAsp, then click flash bootloader
*Make sure that you use wires that are not excessively long - this can cause the bits to be read wrong by the USBAsp

> Soldering..
Soldering can be a bit annoying but all you need to do is to take the motor apart, then expose the three phase wires. Desolder them from the circuit board (since we do not want to use the integrated circuit for control), and then solder new wires to them. These will be your three phase wires. 

> Programming
The FOC programming is quite simple, since the SimpleFOC library has already taken care of that for us! 
Simply upload the code using a usb cable, and it is done. If you want to do it yourself, the parameters for the 24H motor is below. 

If you have never used SimpleFOC, go to their website to get started. 

Motor Parameter: 
Poles = 14

Encoder Paramter:
PPR (pulses per revolution) = 100
CPR (counts per revolution, ppr*4) = 400 

Motor Pins on the BGC: 
Motor 1: 3, 5, 6 (in order)
Motor 2: 9, 10, 11

For any other motor, you can also run the example script in the SimpleFOC Github to figure out your poles (with the encoder already configured): 
https://github.com/simplefoc/Arduino-FOC/tree/master/examples/utils/calibration/find_pole_pair_number

> Wiring Motor
With the BGC 3.2, there are two analog pins already with headers, A0 and A1. We can directly connect the A and B terminals of the encoder to those pins. 
Motor wiring is the same as you would with any other BLDC, simply connect the three phase wires to each of pins on the BGC. 

**Pictures will be added later on

