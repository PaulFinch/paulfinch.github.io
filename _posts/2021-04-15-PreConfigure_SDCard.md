---
layout: post
title:  "PreConfigure SDCard"
category: tips
tags:   raspberrypi 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
Preconfigure SD Card for Raspbian
<!--more-->

Once the OS (Raspbian) has been flashed onto the SD card,

To enable SSH access, create an empty file called “ssh”  and put it on the microSD card (on /boot)
To enable WiFi, create a file called “wpa_supplicant.conf” with following content, on the microSD card (on /boot):

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
  ssid="ssid"
  psk="passphrase"
}
```

Replace “ssid” and “passphrase” with the values matching your own wireless network and save the file. Upon first boot, the file will be moved to the correct location on the filesystem.

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}