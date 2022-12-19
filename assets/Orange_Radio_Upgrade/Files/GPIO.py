#!/usr/bin/env python3

import os
import sys
import time
import signal
import RPi.GPIO as GPIO

pin_btn1 = 17
pin_btn2 = 5
pin_led = 22

run = True

def signal_handler(signal, frame):
    print("GPIO Daemon: signal detected")
    global run
    run = False

def control(action):
    print("GPIO Task: " + action)
    if action == "shutdown":
        os.system("shutdown -h now")
    if action == "play-pause":
        os.system("playerctl play-pause")
    if action == "next":
        os.system("playerctl next")

def main():
    print("GPIO Daemon: loading")

    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin_led, GPIO.OUT)
    GPIO.setup(pin_btn1, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.setup(pin_btn2, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.add_event_detect(pin_btn1, GPIO.RISING, bouncetime=250)
    GPIO.add_event_detect(pin_btn2, GPIO.RISING, bouncetime=250)
    GPIO.output(pin_led, GPIO.HIGH)

    print("GPIO Daemon: ready")
    while run:
        event1 = GPIO.event_detected(pin_btn1)
        event2 = GPIO.event_detected(pin_btn2)

        if event1 and event2:
            control("shutdown")
        else:
            if event1:
                control("next")
            if event2:
                control("play-pause")

        event1 = False
        event2 = False
        time.sleep(1)

    print("GPIO Daemon: Exit")
    GPIO.output(pin_led, GPIO.LOW)
    GPIO.cleanup()
    sys.exit(0)

if __name__ == "__main__":
    main()
