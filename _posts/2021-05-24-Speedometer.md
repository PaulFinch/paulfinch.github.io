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

The activity is saved on the SDcard, and then imported in a dedicated Database (Out of scope).

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}
