---
layout: post
title:  "Orange Radio Upgrade2"
category: projects
image:  orange.jpg
tags:   raspberrypi 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
The Orange Radio is a project I made from an Orange Miniamp (Have a look to the Project page)
<!--more-->

A new Spotifyd release (0.3.4) implemented more mpris features, allowing the Control script to be simplified.

## Upgrade 1: Hardware ##
I switched from Raspberry pi Zero 1 to Raspberry pi Zero 2.
The **armhf-full** is directly available, no more need to compile the **armv6** version with MPRIS feature.

## Upgrade 2: GPIO Script ##
The script now listens to specific **PropertiesChanged** dbus events (which is now implemented in Spotifyd), so no more need to poll the status every n seconds.

By the way, the new version implements a random dbus name, so I had to find the correct dbus instance with a specific regex:
```
"^org\.mpris\.MediaPlayer2\.spotifyd\.instance[0-9]+$"
```

The new Spotifyd version now implements MPRIS on **System** dbus.
Therefore, the dedicated user dbus socket I created is no more required.

But, you need to allow Spotifyd to access the **System** dbus, by creating a specific file in: `/usr/share/dbus-1/system.d/`, with those directives:

```
<?xml version="1.0"?><!--*-nxml-*-->
<!DOCTYPE busconfig PUBLIC
 "-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN"
 "http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd">
<busconfig>
        <policy context="default">
                <allow own_prefix="org.mpris.MediaPlayer2"/>
                <allow send_interface="org.mpris.MediaPlayer2.Player"/>
                <allow send_interface="org.freedesktop.DBus.Introspectable"/>
        </policy>
</busconfig>
```

For more details, check the Files section.

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}
