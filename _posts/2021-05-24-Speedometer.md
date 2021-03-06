---
layout: post
title:  "Bike Speedometer"
category: projects
image: speedometer.jpg
tags: arduino 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
This Bike Speedometer tracks my cycling activies. It was made from a Arduino Esplora.
<!--more-->

[<img src='https://img.youtube.com/vi/MkDkZQN_Pis/0.jpg'>](https://www.youtube.com/watch?v=MkDkZQN_Pis){:target="_blank" rel="noopener"}

## Details ##

- The Arduino Esplora is connected to the bike sensor (Hall effect), to a port supporting interrupts.
Everytime the magnet, on the wheel, goes near by the bike sensor, a signal is sent to the interrupt, invoking the `StepIncrement()` function.

- **Timer1:** Every seconds, the program recalculates the traveled distance from the steps count.
For this, the `#define WHEEL` constant needs to be set as the wheel circumference.

- **Timer2:** Every 10 seconds, the program recalculates the current and average speed from the distance traveled.
The display mode is toggled from AVG to NOW and elapsed time to remaining time (60 Minutes).
If a SDcard is connected, the activity data is saved in a file. The name of the file is generated from a number stored in the EEPROM, and incremented at initialization (the filename is displayed at boot).
The blue LED blinks once. 

- **Every loops:** Controls are read and the display is refreshed.

## Display ##

![Speedometer]({{ site.url }}/assets/{{ folder }}/Images/Speedometer2.jpg)

### NOW PANEL ###
- Speed (km/h)
- Step speed (steps/minute)
- Distance (m)
- Difficulty

### AVG PANEL ###
- Average Speed (km/h)
- Average Step speed (steps/minute)
- Elapsed Time / Remaining Time
- Difficulty

**Red Spot:** The Red spot indicates that a SDcard was detected.

## Controls ##

- **BUTTON LEFT:**	Toggle Display (NOW / AVG)
- **BUTTON RIGHT:**	Toggle Time Display (Elapsed / Remaining)
- **BUTTON BOTTOM:**	Reset Counters
- **BUTTON TOP:**	Start / Pause
- **SLIDER:**		Set Difficulty

**LED:** The Red LED indicates PAUSE status. The Green LED indicates RUNNING status.

![Speedometer]({{ site.url }}/assets/{{ folder }}/Images/Speedometer.jpg)

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}
