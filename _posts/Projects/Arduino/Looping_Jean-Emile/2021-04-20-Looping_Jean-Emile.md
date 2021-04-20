---
layout: post
title:  "Looping Jean-Emile"
date:   2021-04-20 10:00:00 +0200
image: jean-emile.jpg
tags:   arduino
---
## Introduction ##
In Loopin' Louie, a battery-powered motor placed in the center of the table rotates a boom with a little plastic plane. Four radial arms lead out to the players' barns and the chickens they're trying to protect. Each barn has a little lever, which is used to knock the rotating plane away from your chickens and hopefully into someone else's. When only one player has chickens remaining, he or she wins the game.

I couldn't help myself to hack it with 2 awesome modes: 
* __Manual__ : Change the rotation speed manually with the potentiometer
* __Auto__ : Randomly change the rotation speed, including reverse ^^

<p align='center'><img src='https://raw.githubusercontent.com/PaulFinch/paulfinch.github.io/master/_posts/Projects/Arduino/Looping_Jean-Emile/Images/Looping.jpg' width='500'></p>

[Video](https://www.youtube.com/watch?v=b-XIl642PzY){:target="_blank" rel="noopener"}

## Hardware ##
<p align='center'><img src='https://raw.githubusercontent.com/PaulFinch/paulfinch.github.io/master/_posts/Projects/Arduino/Looping_Jean-Emile/Images/L293D.png' width='250'></p>

The Dual H-Bridge L293D contains two full H-bridges (four half H-bridges). That means you can drive four solenoids, two DC motors bi-directionally, or one stepper motor. The perfect Chip to control the motor's speed.

Those chips are good for under 600 mA since that's the limit of this chip. They do handle a peak of 1.2A but that's just for a short amount of time. They run at 5V logic, Good for motor voltages from 4.5V up to 36V. The motor voltage is separate from the logic voltage. [Datasheet](https://www.sparkfun.com/datasheets/IC/SN754410.pdf){:target="_blank" rel="noopener"}

<p align='center'><img src='https://raw.githubusercontent.com/PaulFinch/paulfinch.github.io/master/_posts/Projects/Arduino/Looping_Jean-Emile/Images/Voltmeter.jpg' width='250'></p>

To monitor the speed, I used a 5V analog voltmeter. This analog panel meter measures DC voltage from 0-5 volts with 2.5% accuracy.

### Parts ###
* 1 x Looping Louie
* 1 x L293D
* 1 x 5V Analog Voltmeter
* 2 x LEDs
* 2 x Switches
* 1 x Arduino Uno
* 1 x Protoboard
* 1 x Potentiometer
* 1 x Power Input Socket
* 1 x 9V Power Supply
* Wires

## Wiring ##
<p align='center'><img src='https://raw.githubusercontent.com/PaulFinch/paulfinch.github.io/master/_posts/Projects/Arduino/Looping_Jean-Emile/Fritzing/Schematic.png' width='500'></p>

* __The Power Switch__ : Classic on/off switch which closes the circuit (9V Input)
* __The "Mode" Switch__ : Classic switch which closes the circuit from the dedicated Pin. It allows to select the Automatic or Manual Mode. No need for resistor here as I use the internal Pull Up (INPUT_PULLUP)</p>
* __LEDs__ : Connected to the dedicated Pins (Resistor needed)
* __The Pot__ : The Potentiometer allows to control the speed in Manual Mode. The Arduino reads the value from an Analog Pin
* __The Monitor__ : The Monitor displays the value from the dedicated Pin (0 to 5V)

## Enclosure ##
I also designed a [PVC Enclosure](https://github.com/PaulFinch/paulfinch.github.io/blob/master/_posts/Projects/Arduino/Looping_Jean-Emile/Enclosure/Enclosure.svg){:target="_blank" rel="noopener"} made via [Ponoko Services](https://www.ponoko.com){:target="_blank" rel="noopener"}.

## Code ##
see files [here](https://github.com/PaulFinch/paulfinch.github.io/tree/main/_posts/Projects/Arduino/Looping_Jean-Emile/Files){:target="_blank" rel="noopener"}

```
{% include_relative Files/Looping.ino %}
```