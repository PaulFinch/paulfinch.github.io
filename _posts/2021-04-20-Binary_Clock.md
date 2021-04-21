---
layout: post
title:  "Binary Clock"
date:   2021-04-20 10:00:00 +0200
tags:   javascript
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
A Binary clock made in Javascript.
<!--more-->

## How it Works ##
![Binary_Clock]({{ site.url }}/assets/{{ folder }}/Images/Binary_Clock.jpg)

Each line match a value : 1, 2, 4, 8.

To read the binary clock, add up columns values to obtain the decimal value.

The `Worker` function get the time as 'ddmmyy' and 'hhmmss' numbers. It converts these 2 numbers to binary arrays (get_binaries) and launch the display function (show_binaries).

The `get_binaries` function converts a 6 figures number in an array of 6 arrays. Those arrays are constructed by the get_binary function.

The `get_binary` function converts a figure to a 4 binary values array.

The `show_binaries` function enable or disable radio elements of the form, depending on the returned array provided by the get_binaries function.

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}