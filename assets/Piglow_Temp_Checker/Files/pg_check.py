#!/usr/bin/env python
# -*- coding: utf-8 -*-
# For Libreelec / Needs System Tools addon

import sys
from time import sleep
import subprocess
import signal
import piglow


def signal_handler(signal, frame):
    piglow.all(0)
    sys.exit(0)


def blink_warning():
    for y in range(3):
        piglow.red(64)
        sleep(0.1)
        piglow.orange(64)
        sleep(0.1)
        piglow.yellow(64)
        sleep(0.1)
        piglow.green(64)
        sleep(0.1)
        piglow.blue(64)
        sleep(0.1)
        piglow.white(64)

        piglow.white(0)
        sleep(0.1)
        piglow.blue(0)
        sleep(0.1)
        piglow.green(0)
        sleep(0.1)
        piglow.yellow(0)
        sleep(0.1)
        piglow.orange(0)
        sleep(0.1)
        piglow.red(0)
        sleep(0.2)
    piglow.all(0)


def blink_OK():
    for y in range(1):
        for x in range(0, 64, 8):
            piglow.green(x)
            sleep(0.05)
        for x in range(64, -1, -8):
            piglow.green(x)
            sleep(0.05)
    piglow.all(0)

signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

piglow.auto_update = True
piglow.clear_on_exit = True

blink_warning()

while True:
    piglow.all(0)
    temperature = float(subprocess.check_output(["cat", "/sys/class/thermal/thermal_zone0/temp"])) / 1000

    if temperature > 70:
        blink_warning()
        for x in range(0, 128, 8):
            piglow.red(x)
            sleep(0.05)
    elif temperature > 60:
        blink_warning()
        for x in range(0, 128, 8):
            piglow.orange(x)
            sleep(0.05)
    else:
        blink_OK()
    sleep(60)
