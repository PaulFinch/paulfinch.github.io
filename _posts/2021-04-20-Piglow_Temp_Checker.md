---
layout: post
title:  "Piglow Temp Checker"
date:   2021-04-20 12:00:00 +0200
tags:   raspberrypi 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
This is a little script I made to check Raspberry Pi's Temperature with Pimoroni's Piglow.
<!--more-->

Temperature is checked every 60 seconds via : `/sys/class/thermal/thermal_zone0/temp`
When Temperature is OK (<=60), Green lights glow for a second.
When Temperature is critical (>60), LED cycles notify the situation, then orange or red lights stay on (depending on the temperature)

## Prerequisites ##
* Pimoroni Piglow [Link]('https://shop.pimoroni.com/products/piglow')
* File : piglow.py (or pip install piglow)</li>
* File : sn3218.py (or pip install sn3218)</li>

## Run as a Service ##
To run this script as a service, check Resource : `Run_as_a_Service`

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}