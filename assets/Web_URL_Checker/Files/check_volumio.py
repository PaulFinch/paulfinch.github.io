#!/usr/bin/python
# -*- coding: utf-8 -*-
# sudo apt-get install python-rpi.gpio

import os
import sys, traceback
import urllib
import getopt
import subprocess
import signal
import time
import RPi.GPIO as GPIO

url = "http://127.0.0.1:3000/playback"
pin = 22

def signal_handler(signal, frame):
	#print "Bye"
	GPIO.output(pin, GPIO.LOW)
	sys.exit(0)

def change_status(state):
	#print "New State: " + str(state)
	if state:
		GPIO.output(pin, GPIO.HIGH)
	else:
		GPIO.output(pin, GPIO.LOW)

def main(argv):
	status = False
	old_status = False

	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(pin, GPIO.OUT)
	GPIO.output(pin, GPIO.LOW)

	signal.signal(signal.SIGINT, signal_handler)
	signal.signal(signal.SIGTERM, signal_handler)

	while 1:
		try:
			code = urllib.urlopen(url).getcode()
			if code == 200:
				status = True
			else:
				status = False
		except IOError:
			status = False

		if old_status != status:
			change_status(status)
			old_status = status

		if status == True:
			time.sleep( 60 )
		else:
			time.sleep( 10 )
	GPIO.output(pin, GPIO.LOW)
	sys.exit(0)

if __name__ == "__main__":
    main(sys.argv[1:])

