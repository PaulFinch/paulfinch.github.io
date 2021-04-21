#!/usr/bin/env python
# -*- coding: utf-8 -*-

from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
import random
import os
import datetime
import sys

def send_text(bot, update):
    global mylines

    for i in range(5):
        r = random.random()
        random.shuffle(mylines, lambda: r)
    myline =random.choice(mylines)
    update.message.reply_text(myline)

def send_picture(bot, update):
    global myfiles

    for i in range(5):
        r = random.random()
        random.shuffle(myfiles, lambda: r)
    myfile = random.choice(myfiles)

    if not os.path.isfile(myfile):
        return

    if myfile.lower().endswith('.jpg'):
        update.message.reply_photo(open(myfile, 'rb'))
    elif myfile.lower().endswith('.gif'):
        update.message.reply_document(open(myfile, 'rb'))
    elif myfile.lower().endswith(('.mp4', '.avi')):
        update.message.reply_video(open(myfile, 'rb'))

if __name__ == '__main__':

    scriptpath = "/data/bot/"                                           #Replace with your script location
    if not os.path.isdir(scriptpath):
        sys.exit(1)

    linepath = scriptpath + "text.txt"                                  #The text file that will be used to get sentences from
    if not os.path.isfile(linepath):
        sys.exit(1)
    mylines = open(linepath).read().splitlines()

    filepath = scriptpath + "Pictures/"                                 #The folder to get the pictures from
    if not os.path.isdir(filepath):
        sys.exit(1)
    myfiles = [os.path.join(root, name)
        for root, dirs, files in os.walk(filepath)
            for name in files
                if name.endswith((".jpg", ".gif", ".mp4", ".avi"))]

    updater = Updater("YOUR_BOT_TOKEN")

    dp = updater.dispatcher
    dp.add_handler(CommandHandler("send_text", send_text))              #The send_text command will call the send_text function
    dp.add_handler(CommandHandler("send_picture", send_picture))        #The send_picture command will call the send_picture function

    updater.start_polling()
    updater.idle()