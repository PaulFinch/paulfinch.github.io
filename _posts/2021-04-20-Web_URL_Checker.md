---
layout: post
title:  "Web URL Checker"
category: Programs
tags:   python 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
This is a little script I made to check if Volumio's Web Interface is ready by lighting up a LED on the Raspberry Pi. This script turns on the Pin 22 if the port 3000 is responding.
<!--more-->

## Run the Script ##
Run the script : 

`sudo python check_volumio.py`

## Run as a Service ##
To run this script as a service, check Resource : 

`Run_as_a_Service`

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}