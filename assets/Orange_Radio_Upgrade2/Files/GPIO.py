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
    DELAY_STATUS = 60
    DELAY_SVC = 60
    DELAY_MAIN = 10

    STATUS_SVC = False
    STATUS_PLAY = False

    SERVICES = ['Spotifyd.service']

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

            self.SERVICE = 'org.mpris.MediaPlayer2.spotifyd'
            pattern = re.compile("^org\.mpris\.MediaPlayer2\.spotifyd\.instance[0-9]+$")
            for service in dbus.SystemBus().list_names():
                if pattern.match(service):
                    self.SERVICE = service

            self.BUS_PROXY = self.BUS.get_object(self.SERVICE, '/org/mpris/MediaPlayer2')
            self.PLAYER = dbus.Interface(self.BUS_PROXY, 'org.mpris.MediaPlayer2.Player')
            self.PLAYER_PROPERTIES = dbus.Interface(self.BUS_PROXY, 'org.freedesktop.DBus.Properties')
            self.RECEIVER = self.BUS.add_signal_receiver(self.update_status, signal_name='PropertiesChanged', path='/org/mpris/MediaPlayer2')
        except:
            self.LOGGER.error("Error: Dbus")

        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.PIN_LED1, GPIO.OUT)
        GPIO.setup(self.PIN_BTN1, GPIO.IN)
        GPIO.setup(self.PIN_BTN2, GPIO.IN)
        GPIO.add_event_detect(self.PIN_BTN1, GPIO.FALLING, bouncetime=250)
        GPIO.add_event_detect(self.PIN_BTN2, GPIO.FALLING, bouncetime=250)

        self.THREAD_BLINK = threading.Thread(target=self.thread_blink, daemon=True)
        self.THREAD_BLINK.start()
        self.THREAD_EVENTS = threading.Thread(target=self.thread_events, daemon=True)
        self.THREAD_EVENTS.start()
        self.THREAD_STATUS = threading.Thread(target=self.thread_status, daemon=True)
        self.THREAD_STATUS.start()
        self.THREAD_SERVICE = threading.Thread(target=self.thread_service, daemon=True)
        self.THREAD_SERVICE.start()

    def run(self):
        self.LOGGER.info("Running Daemon")
        self.update_status()
        while self.RUN:
            time.sleep(self.DELAY_MAIN)
        self.exit()

    def exit(self):
        self.LOGGER.info("Exit")
        self.RUN = False

        try:
            self.LOOP.quit()
            self.RECEIVER.remove()
            self.BUS.close()
        except:
            self.LOGGER.error("Error: Dbus")

        self.THREAD_BLINK.join()
        self.THREAD_EVENTS.join()
        self.THREAD_STATUS.join()
        self.THREAD_SERVICE.join()

        GPIO.remove_event_detect(self.PIN_BTN1)
        GPIO.remove_event_detect(self.PIN_BTN2)
        GPIO.output(self.PIN_LED1, GPIO.LOW)
        GPIO.cleanup()

    def signal_handler(self, signal, frame):
        self.LOGGER.info("Signal detected")
        self.RUN = False

    def thread_blink(self):
        led_status = False
        last_led_status = False

        while self.RUN:
            if self.STATUS_SVC:
                if self.STATUS_PLAY:
                    led_status = not led_status
                else:
                    led_status = True
            else:
                led_status = False

            if led_status != last_led_status:
                if led_status:
                    GPIO.output(self.PIN_LED1, GPIO.HIGH)
                else:
                    GPIO.output(self.PIN_LED1, GPIO.LOW)

            last_led_status = led_status
            time.sleep(self.DELAY_BLINK)

    def thread_events(self):
        while self.RUN:
            event1 = GPIO.event_detected(self.PIN_BTN1)
            event2 = GPIO.event_detected(self.PIN_BTN2)

            if event1 or event2:
                self.LOGGER.info("Event: B1-" + str(event1) + " B2-" + str(event2))
            
            if event1 and event2:
                self.control('shutdown')
            if event1 and not event2:
                self.control('next')
            if event2 and not event1:
                self.control('play-pause')

            event1 = False
            event2 = False
            time.sleep(self.DELAY_EVENT)

    def thread_status(self):
        while self.RUN:
            try:
                self.LOOP.run()
            except:
                self.update_status()
                time.sleep(self.DELAY_STATUS)

    def thread_service(self):
        while self.RUN:
            self.update_service()
            time.sleep(self.DELAY_STATUS)

    def control(self, action):
        self.LOGGER.info("Task [" + str(action) + "]")
        if action == 'shutdown':
            time.sleep(5)
            subprocess.Popen('systemctl poweroff', shell=True)
        if action == 'reboot':
            time.sleep(5)
            subprocess.Popen('systemctl reboot', shell=True)
        try:
            if action == 'play-pause':
                self.PLAYER.PlayPause()
            if action == 'stop':
                self.PLAYER.Stop()
            if action == 'previous':
                self.PLAYER.Previous()
            if action == 'next':
                self.PLAYER.Next()
        except:
            self.LOGGER.error("Error: Dbus Player")

    def update_service(self):
        service_status = True
        for service in self.SERVICES:
            if int(os.system('systemctl is-active --quiet ' + str(service))) != 0:
                self.LOGGER.error("Error: Service not running (" + str(service) + ")")
                service_status = False

        self.STATUS_SVC = service_status

    def update_status(self, *args):
        if len(args) > 0:
            if 'PlaybackStatus' in args[1]:
                get_status = args[1].get('PlaybackStatus')
                self.LOGGER.info("Update Status: " + get_status + " (GET)")
                if get_status == 'Playing':
                    self.STATUS_PLAY = True
                else:
                    self.STATUS_PLAY = False
            else:
                self.LOGGER.info("Update Status: Other (GET)")
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

if __name__ == '__main__':
    gh = GhettoBlaster()
    gh.run()
    sys.exit()
