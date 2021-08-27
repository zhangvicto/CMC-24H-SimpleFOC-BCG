![Intro Pic](/img/intro.jpg)
## Intro
Controlling cheap brushless DC motors (Nidec CMC_24H) with integrated encoder using a BGC 3.2 (brushless gimbal controller) and SimpleFOC.

## Why?
CMC_24H series BLDC motors, which are used in printers and many other home appliances are widely available for low prices due to mass production. They also have an integrated optical encoder making them great for hobby robotics projects. However, the standard control board that comes with the motor does not provide any method for torque control. 
![pic of circuit board](/img/circuit.jpg)
 
Using SimpleFOC, we can use FOC (force-oriented-control) on cheap commercially available controller boards such as the BGC 3.2, which only costs CAD $15, and is able to control two BLDC motors. ![bcg](/img/bcg.jpg)

The BGC is supposedly rated for 10A (although unclear if it is 5A per motor or 10A per motor, the MOSFET's seem to be able to handle 10A per motor, but it is untested). 5A per motor is assumed to be conservative. This means that it is capable of controlling most of the motors supported by SimpleFOC (max 5A due to the algorithm, < 5A is safe).
Since the CMC_24H is rated for 0.7A, we can well cover its current needs. 

The total price is only $20 or $25 for two motors. 
| Item       | Price (CAD) | Link                                                  |
|------------|-------------|-------------------------------------------------------|
| BGC        |         $15 | https://www.aliexpress.com/item/32458535720.html      |
| BLDC Motor |          $5 | https://www.aliexpress.com/item/1005001686327895.html |
| Total      |         $20 | -                                                     |

## Steps

### Soldering..
Soldering can be a bit annoying but all you need to do is to take the motor apart, then expose the three phase wires. ![pic of phase wires](/img/phase.jpg) Desolder them from the circuit board (since we do not want to use the integrated circuit for control), and then solder dupont wires to them. ![pic of dupont connectors](/img/dupont.jpg)

You may also want to solder on the header for the SPI pins for the next step.
 ![spi pins location](/img/spi-header.jpg)

### Flash Arduino for BGC 3.2 with USBasp
> There are many ways to burn the Arduino bootloader on an ATMEL chip, but the simplest method is just to use the USBasp. They cost a few bucks and the flashing is fairly reliable. If you have an Arduino lying around you can use that as well following the numerous tutorials online.
 - Connect all the pins (SPI)
 ![diagram of usbasp](/img/usbasp.jpg)
 - In the Arduino IDE go to Tools -> Programmer -> select USBasp, then click "Burn Bootloader"
*Make sure that you use wires that are not excessively long - this can cause the USBasp to read bits wrong

### Programming
The FOC programming is quite simple, since the SimpleFOC library has already taken care of that for us! If you have never used SimpleFOC, go to their website to get started. https://simplefoc.com

Simply upload the code using a USB cable, and it is done. If you want to code it yourself, the parameters for the 24H motor are below:
| Motor Parameter | Encoder Paramter      |
|-----------------|-----------------------|
| Pole Pairs = 24 | PPR = 100 (CPR = 400) |

BGC Motor Pins:
| Motor 1 |  Motor 2  |
|:-------:|:---------:|
| 3, 5, 6 | 9, 10, 11 |

For any other motor, you can also run the example script in the SimpleFOC Github to find out your BLDC's pole pairs (with the encoder already configured): 
https://github.com/simplefoc/Arduino-FOC/tree/master/examples/utils/calibration/find_pole_pair_number

### Wiring Motor
With the BGC 3.2, there are two analog pins already with headers, A0 and A1. We can directly connect the A and B terminals of the encoder to those pins. A2 and A3 are also available but you will need to solder on a header to use those for a second motor.

Motor wiring is the same as you would with any other BLDC, simply connect the three phase wires to each of pins on the BGC. 
