---
layout: post
title:  "Orange Radio"
category: Projects
image:  orange.jpg
tags:   raspberrypi 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
The Orange Radio is a Raspberry Pi Radio made from an Orange Miniamp
<!--more-->

[<img src='https://img.youtube.com/vi/rGPyn7Ue5Fc/0.jpg'>](https://www.youtube.com/watch?v=rGPyn7Ue5Fc){:target="_blank" rel="noopener"}

For this project, I chose the __Orange CR6S Amp__ for the enclosure, this amp is quite cheap and has a f***** english retro style. Of course, you can build your own 3D printed enclosure, or take an old Radio...

## Hardware ##
The __Raspberry Pi Zero__ makes the perfect match for the project's brain. The Zero is a super-small, hackable, and ultra-low-cost computer, with mini-HDMI, micro-B OTG USB, and the same 40-pin GPIO as its bigger brothers.

Unfortunately it has no builtin audio output, so I stacked a Primoroni __PHAT DAC__ to add audio capabilities.
This pHAT provides a super affordable high-quality DAC for the Raspberry Pi. It pumps out 24-bits at 192KHz from the Raspberry Pi's I2S interface on its 2x20 pin GPIO header.

![Potentiometer]({{ site.url }}/assets/{{ folder }}/Images/Potentiometer.jpg)

Since the pHat has no hardware volume control, and as Volumio doesn't like Specific ALSA Tuning (Software Mix), I added a Dual __Logarithmic Potentiometer__ to control the audio output from Left and Right Channels.

An __Adafruit 3W Amp__ will amplify the PHAT DAC signal, this MAX08357 I2S Amp Breakout is able to deliver 3.2 Watts of power into a 4 ohm impedance speaker (5V power @ 10% THD). 
Inside the miniature chip is a class D controller, able to run from 2.7V-5.5VDC.

## Software ##
![Volumio]({{ site.url }}/assets/{{ folder }}/Images/Volumio_Interface.jpg)

I tested several Software Solutions (Raspbian + VLC, RuneOS, Mopidy, Volumio, etc ...) and I think __Volumio__ is the best choice for this kind of project (Even if not perfect).
I Chose this OS mostly because it could handle NAS Shares but also Web Radios, Local Files and Spotify.

Moreover, the web application is good enough to run on android (An app exists but useless). 
Just create a shortcut on your home screen and that's it.

Volumio supports the PhatDac Out of the Box.

## Parts ##
* 1 x Orange CR6S
* 1 x Raspberry Pi Zero W
* 1 x Pimoroni Phat Dac
* 1 x Adafruit 3W Amp
* 1 x SD Card + Volumio OS
* 1 x Protoboard
* 1 x Dual Logarithmic Potentiometer 50k
* 1 x UBEC 5V converter
* 2 x LEDs
* 1 x Momentary Switch
* 1 x Power Switch
* 1 x Power Input Socket
* 1 x 12V or 9V Power Supply
* Wires

## Power Supply ##
I used a protoboard to wire the power circuit. First, the incoming current goes through the power switch, which allows to turn on/off the circuit. Then, A UBEC 5V converter creates a stable 5V output from the incoming power (9V, 12V).

![ProtoBoard]({{ site.url }}/assets/{{ folder }}/Images/ProtoBoard.jpg)

The Raspberry Pi is powered via the USB Power port, whereas the 3W Amp is directly soldered on the board.

## Audio ##
The easiest way to wire the Phat Dac is to use the pinout dedicated to RCA. The smaller hole is the signal, the smaller one is the ground. As said previously, if you don't use the Software Mixer (not adviced with Volumio), you'll need potentiometers to control the output volume :

![Schematic]({{ site.url }}/assets/{{ folder }}/Fritzing/Schematic_Amp.png)

I used a dual portentiometer, which combines the 2 potentiometers in one, this way you can control Left and Right Volume in the same time.

## LEDs and Button ##
![Radio]({{ site.url }}/assets/{{ folder }}/Fritzing/Radio2.png)

I also added Two LEDs and 1 Button :

* __BUTTON 1__ : Shutdown the Raspberry Pi Operating System. I used the Volumio plugin : __GPIO Buttons__ and configured Pin 17 to shutdown the PI. It is possible to dedicate a button to Play/Pause function as well.
* __LED 1__ : Indicates if the Raspberry Pi Operating System is started or not. I used the __UART tx Pin__ which stops sending 3.3v when the RPI is in shutdown mode. You'll just need to enable UART in /boot/config.txt by adding : 
> `enable_uart=1` or in some cases `dtoverlay=pi3-disable-bt`
* __LED 2__ : Indicates if the Volumio Application is Started and Ready. For this I made a __Python Script__ to check if the web interface is ready (Check Web_URL_Checker).

![Schematic]({{ site.url }}/assets/{{ folder }}/Fritzing/Schematic_Led.png)