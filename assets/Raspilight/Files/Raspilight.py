#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unicornhat as unicorn
import Image
import time
import sys
import signal
import os
from subprocess import check_output
from cStringIO import StringIO

def signal_handler(signal, frame):
    unicorn.off()
    sys.exit(0)

def unicorn_init():
    # Initialize the Unicorn
    unicorn.set_layout(unicorn.PHAT)
    unicorn.rotation(180)
    unicorn.brightness(0.8)
    unicorn.off()

def unicorn_set(pixels):
    # Light the unicorn LEDs according the pixels list
    unicorn.clear()
    for pixel in pixels:
        unicorn.set_pixel(pixel[0], pixel[1], pixel[2], pixel[3], pixel[4])
    unicorn.show()

def get_colors():
    # Takes a screenshot with raspi2png, then divides it in 8x4 zones
    # For each zone, the screenshot is cropped to this zone, and the dominant color is calculated
    # Each zone/color is appended in the pixels list
    phat = (8, 4)
    pixels = []
    raw = check_output(["./raspi2png", "--width=320", "--height=240", "--stdout"])
    buff = StringIO(raw)
    image = Image.open(buff)
    size = image.size
    slot = (int(size[0] / phat[0]), int(size[1] / phat[1]))
    for y in range(phat[0]):
        for x in range(phat[1]):
            pos = (x * slot[0], y * slot[1])
            cropbox = (pos[0], pos[1], pos[0] + slot[0], pos[1] + slot[1])
            image2 = image.crop(cropbox)
            image2 = image2.convert('P', palette=Image.ADAPTIVE, colors=1)
            image2.putalpha(0)
            colors = image2.getcolors(1)
            maincolor = colors[0]
            r,g,b,a = maincolor[1]
            # Create pixel (with horizontal flip)
            pixel = (phat[0]-x-1, y, r, g, b)
            pixels.append(pixel)
            image2.close()
    image.close()
    return pixels

if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)
    curdir = os.path.dirname(os.path.realpath(__file__))
    os.chdir(curdir)
    unicorn_init()
    while True:
        pixels = get_colors()
        unicorn_set(pixels)
        time.sleep(1)
    unicorn.off()
    sys.exit(0)
