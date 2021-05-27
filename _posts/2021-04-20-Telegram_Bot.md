---
layout: post
title:  "Telegram Bot"
category: projects
tags:   python 
---
{% capture folder %}
{{ page.title | replace: " ", "_" }}
{% endcapture %}

## Introduction ##
This is a script I made to create a Telegram Bot. This one gives random text or random picture on demand.
<!--more-->

The telegram-bot Library is required, install it first (I recommand using virtualenv):

`pip install python-telegram-bot --upgrade`

## Create the Bot ##
There's a bot dedicated to create new bots. Just talk to **BotFather** and ask him to create a Bot: `/newbot`
Follow the few next steps, once you've created the Bot you'll receive your authorization TOKEN.

You also need to configure the Bot commands:
- `/send_text`
- `/send_picture`
- `/ping`

## Configure the Script ##
* Replace **YOUR_BOT_TOKEN** with the Authorization token provided by the BotFather.
* Create directory **/Resources/Texts/** with various text files.
* Create directory **/Resources/Photos/** folder with various pictures.
* Create directory **/Resources/Memes/** folder with various memes.

Memes files are regex compatible, example:
```
apple.jpg               _will match apple_
ho+u+se.jpg             _will match house, houuuuuuuuse and hooooooouse_
h(a|o)t.jpg             _will match hat or hot_
```

## Run the Script ##
Run the script : 

`python Bot.py`

In Telegram, talk to the Bot or invite him in a chat room, the Bot will respond to these key commands :

`/send_text`
`/send_picture`
`/ping`

The Bot will also post a Meme when a Meme file is matched with a conversation word.

## Run as a Service ##
To run this script as a service, check Resource : `Run_as_a_Service`

## Code ##
see files [here](https://github.com/{{ site.repository }}/tree/main/assets/{{ folder }}/Files){:target="_blank" rel="noopener"}
