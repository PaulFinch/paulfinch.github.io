---
layout: post
title:  "Raspilight"
date:   2021-04-21 10:00:00 +0200
tags:   raspberrypi
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
This is a script I made to turn the Pimoroni Unicorn Phat to an Ambient Light for the Raspberry Pi.

![Unicorn]({{ site.baseurl }}/assets/{{ folder }}/Images/Unicorn.jpg)

![Mario]({{ site.baseurl }}/assets/{{ folder }}/Images/Mario.jpg)

Basically, the script takes a screenshot with raspi2png [Link]('https://github.com/AndrewFromMelbourne/raspi2png'), then divides it into 4x8 zones.

For each zone, the screenshot is cropped to its coordinates, and the dominant color is then calculated.
This way, a list is built with each LED coordinates / color (RGB). 

For this script, you'll need of course a Primoroni Unicorn Phat [Link]('https://shop.pimoroni.com/products/unicorn-phat') and to install the Unicorn Library with the pimoroni-dashboard or with :
`curl -sS https://get.pimoroni.com/unicornhat | bash`

## Run as a Service ##
To run this script as a service, check Resource :
> `Run_as_a_Service`

## Code ##
see files [here](https://github.com/PaulFinch/paulfinch.github.io/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}