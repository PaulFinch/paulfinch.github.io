---
layout: post
title:  "Run as a Service"
category: tips
tags:   linux raspberrypi
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
How to run a script or executable file as a service
<!--more-->

First, create a service unit by creating this file : 

`/lib/systemd/system/xxx.service` (Most of OS)

Then, enable the service :
* `chmod 644 xxx.service`
* `systemctl enable|disable xxx.service`
* `systemctl start|stop|status xxx.service`

If you modified the service file, issue this command to take modifications in account :
* `systemctl daemon-reload xxx.service`

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}