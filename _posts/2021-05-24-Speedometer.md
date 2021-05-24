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

![Speedometer]({{ site.url }}/assets/{{ folder }}/Images/Speedometer.jpg)

I connected the bike sensor (Hall effect) to the Arduino Esplora, on a port supporting interrupts.
The `#define WHEEL` constant needs to be tweaked, as it is the wheel circumference, used to caculate the traveled distance.

The activity data is saved on the SDcard every 10 seconds.
At the end, I import all data in a Database with a dedicated script (Out of scope).

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}
