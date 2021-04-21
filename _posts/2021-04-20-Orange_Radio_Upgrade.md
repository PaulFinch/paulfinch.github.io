---
layout: post
title:  "Orange Radio Upgrade"
date:   2021-04-20 11:00:00 +0200
image:  orange.jpg
tags:   raspberrypi 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
The Orange Radio is a project I made from an Orange Miniamp (Have a look to the Project page)

I decided to rework the project:
1. I used Volumio for a long time, but the whole system is quite heavy and not very customizable.
I noticed that I was only interested in the Spotify Connect feature, so I dumped Volumio for a (lighter) Spotify Connect daemon.

1. I also wanted the ability to play/pause the songs, but I had just 1 button (dedicated for shutdown).
So i decided to add 1 more button to afford more flexibility.

## Upgrade 1: Software ##
At first, I used **Raspotify** which is great. The only problem is: It does not implement the MPRIS standard dbus interface, which could be interesting if you want to control the Spotify playback.
Therefore, I switched for **Spotifyd** which does implement it.

You can retrieve the Spotifyd binary from the [Github](https://github.com/Spotifyd/spotifyd/releases) release page.
The MPRIS feature is not included in the slim binary, so the full binary would be required. 
Unfortunatly, this binary is not available for **armv6** (Raspberry pi Zero), **slim** is available but **full** is not. 

So ... you need to ... compile it.

Hopefully, the [documentation](https://github.com/Spotifyd/spotifyd#compiling-from-source) is pretty straight forward.
It took 5-6 hours on raspberry pi zero. I tried to cross-compile it from my PC, did not work.

Once you have the binary, just create a systemd daemon for it.
BUT, MPRIS needs a dbus interface, which is usually started with desktop environment.
On the headless rasberry pi operating system, no session dbus is available, so I needed to create one:

I created a dbus socket unit and a dbus service to provide a session dbus.
I pointed the Spotifyd service unit to this dbus address via the environment variable:
```
DBUS_SESSION_BUS_ADDRESS=unix:path=/var/run/dbus/my_bus_socket
```

I also created a dedicated python daemon (GPIO.py) to manage leds and buttons.
I pointed the GPIO service unit to the dbus address. 

In order to control the spotifyd playback (via MPRIS), I used the **playerctl** software, which points to the dbus environment variable as well.

For more details, check the Files section.

## Upgrade 2: Buttons ##
* __BUTTON 1__ : Play/Pause (GPIO17)
* __BUTTON 2__ : Next Song (GPIO5) (Pressing both buttons initiates the system shutdown)

I also rewired the buttons to 3V (with resistors). When the circuit is opened, the pin is **DOWN**, when the circuit is closed (button pushed), the pin is **HIGH**.

Tip: Sometimes, you could be tempted to avoid adding resistors (like I did), just don't. 

![Schematic]({{ site.baseurl }}/assets/{{ folder }}/Fritzing/Schematic_Led.png)

## Code ##
see files [here](https://github.com/PaulFinch/paulfinch.github.io/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}