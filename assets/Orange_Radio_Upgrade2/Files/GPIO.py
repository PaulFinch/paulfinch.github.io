#!/usr/bin/env python3

import os
import sys
import time
import signal
import subprocess
import threading
import dbus
import RPi.GPIO as GPIO
import logging
import re
from systemd.journal import JournalHandler
from gi.repository import GLib
from dbus.mainloop.glib import DBusGMainLoop

class GhettoBlaster:

    PIN_BTN1 = 17
    PIN_BTN2 = 5
    PIN_LED1 = 22
    RUN = True
    DELAY_BLINK = 1
    DELAY_EVENT = 1

    STATUS_PLAY = False
    STATUS_DBUS = False

    PATTERN = re.compile("^org\.mpris\.MediaPlayer2\.spotifyd\.instance[0-9]+$")

    def __init__(self):
        signal.signal(signal.SIGINT, self.signal_handler)
        signal.signal(signal.SIGTERM, self.signal_handler)

        self.LOGGER = logging.getLogger(__name__)
        self.LOGGER.addHandler(JournalHandler())
        self.LOGGER.setLevel(logging.INFO)
        self.LOGGER.info("Loading Daemon")

        try:
            dbus_loop = DBusGMainLoop(set_as_default=True)
            self.LOOP = GLib.MainLoop()
            self.BUS = dbus.SystemBus(mainloop=dbus_loop)

            for service in dbus.SystemBus().list_names():
                if self.PATTERN.match(service):
                    self.SERVICE = service

            self.BUS_PROXY = self.BUS.get_object(self.SERVICE, '/org/mpris/MediaPlayer2')
            self.PLAYER = dbus.Interface(self.BUS_PROXY, 'org.mpris.MediaPlayer2.Player')
            self.PLAYER_PROPERTIES = dbus.Interface(self.BUS_PROXY, 'org.freedesktop.DBus.Properties')
            self.RECEIVER = self.BUS.add_signal_receiver(self.update_status, signal_name='PropertiesChanged', path='/org/mpris/MediaPlayer2')
            self.STATUS_DBUS = True
        except dbus.exceptions.DBusException:
            self.LOGGER.error("Error: Dbus")

        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.PIN_LED1, GPIO.OUT)
        GPIO.setup(self.PIN_BTN1, GPIO.IN)
        GPIO.setup(self.PIN_BTN2, GPIO.IN)
        GPIO.add_event_detect(self.PIN_BTN1, GPIO.FALLING, bouncetime=250)
        GPIO.add_event_detect(self.PIN_BTN2, GPIO.FALLING, bouncetime=250)

        self.THREAD_BLINK = threading.Thread(target=self.blink, daemon=True)
        self.THREAD_BLINK.start()
        self.THREAD_EVENTS = threading.Thread(target=self.events, daemon=True)
        self.THREAD_EVENTS.start()

    def run(self):
        self.LOGGER.info("Running Daemon")
        self.update_status()
        while self.RUN:
            self.LOOP.run()
        self.exit(0)

    def exit(self, code):
        self.LOGGER.info("Exit " + str(code))
        self.RUN = False

        self.THREAD_BLINK.join()
        self.THREAD_EVENTS.join()

        if self.STATUS_DBUS:
            self.RECEIVER.remove()
            self.BUS.close()

        GPIO.remove_event_detect(self.PIN_BTN1)
        GPIO.remove_event_detect(self.PIN_BTN2)
        GPIO.output(self.PIN_LED1, GPIO.LOW)
        GPIO.cleanup()
        sys.exit(code)

    def signal_handler(self, signal, frame):
        self.LOGGER.info("Signal detected")
        self.RUN = False
        if self.STATUS_DBUS:
            self.LOOP.quit()

    def blink(self):
        led_status = False
        last_led_status = False

        while self.RUN:
            if self.STATUS_PLAY:
                led_status = not led_status
            else:
                led_status = True

            if led_status != last_led_status:
                if led_status:
                    GPIO.output(self.PIN_LED1, GPIO.HIGH)
                else:
                    GPIO.output(self.PIN_LED1, GPIO.LOW)

            last_led_status = led_status
            time.sleep(self.DELAY_BLINK)

    def events(self):
        while self.RUN:
            event1 = GPIO.event_detected(self.PIN_BTN1)
            event2 = GPIO.event_detected(self.PIN_BTN2)

            if event1 and event2:
                self.control('shutdown')
            if event1 and not event2:
                self.control('next')
            if event2 and not event1:
                self.control('play-pause')

            event1 = False
            event2 = False
            time.sleep(self.DELAY_EVENT)

    def control(self, action):
        self.LOGGER.info("Task [" + str(action) + "]")
        if action == 'shutdown':
            subprocess.Popen('systemctl poweroff', shell=True)
        if action == 'reboot':
            subprocess.Popen('systemctl reboot', shell=True)
        if action == 'play-pause':
            self.PLAYER.PlayPause()
        if action == 'stop':
            self.PLAYER.Stop()
        if action == 'previous':
            self.PLAYER.Previous()
        if action == 'next':
            self.PLAYER.Next()

    def update_status(self, *args):
        if self.STATUS_DBUS:
            if len(args) > 0:
                if 'PlaybackStatus' in args[1]:
                    try:
                        get_status = args[1].get('PlaybackStatus')
                        self.LOGGER.info("Update Status: " + get_status + " (GET)")
                        if get_status == 'Playing':
                            self.STATUS_PLAY = True
                        else:
                            self.STATUS_PLAY = False
                    except:
                        self.LOGGER.error("Error: Get PlaybackStatus")
            else:
                try:
                    poll_status = self.PLAYER_PROPERTIES.Get('org.mpris.MediaPlayer2.Player', 'PlaybackStatus')
                    self.LOGGER.info("Update Status: " + poll_status + " (POLL)")
                    if poll_status == 'Playing':
                        self.STATUS_PLAY = True
                    else:
                        self.STATUS_PLAY = False
                except:
                    self.LOGGER.error("Error: Poll PlaybackStatus")
        else:
            self.STATUS_PLAY = False

if __name__ == '__main__':
    gh = GhettoBlaster()
    gh.run()
