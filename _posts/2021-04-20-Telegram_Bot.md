---
layout: post
title:  "Telegram Bot"
category: Projects
tags:   python 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
This is a script I made to create a Telegram Bot. This one gives random text or random picture on demand.
<!--more-->

The telegram-bot Library is required, install it first:

`pip install python-telegram-bot --upgrade`

## Create the Bot ##
There's a bot dedicated to create new bots. Just talk to BotFather and ask him to create a Bot: `/newbot`
Follow the few next steps, once you've created the Bot you'll receive your authorization token.

## Configure the Script ##
* Replace the __scriptpath__ value with your script location (useful if used as a service).
* Replace __YOUR_BOT_TOKEN__ with the given token (Authorization token provided by the BotFather).
* Create a text file __text.txt__ with different sentences.
* Create a __Pictures__ folder with different pictures.

## Run the Script ##
Run the script : 

`python bot.py`

In Telegram, talk to the bot or invite him in a chat room, the Bot will respond to these key commands :

`/send_text`
`/send_picture`

## Run as a Service ##
To run this script as a service, check Resource : `Run_as_a_Service`

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}