import os
import re
import sys
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
from Bot_helpers import *

SCRIPTPATH = os.path.dirname(os.path.realpath(__file__))
TOKEN = "REPLACE_WITH_YOUR_TOKEN"

def randomtext(update, context):
    TXTDIR = SCRIPTPATH + "/Resources/Texts/"
    if os.path.isdir(TXTDIR):
        mytext = getrandomline(getrandomtext(TXTDIR))
        update.message.reply_text(text=mytext, parse_mode='HTML')

def ping(update, context):
    update.message.reply_text(text="pong", parse_mode='HTML')

def randommedia(update, context):
    MEDIADIR = SCRIPTPATH + "/Resources/Photos/"
    if os.path.isdir(MEDIADIR):
        myfile = getrandommedia(MEDIADIR)
        myfile_clean = os.path.dirname(str(myfile)).replace(MEDIADIR, "")
        if myfile.lower().endswith('.jpg'):
            update.effective_message.reply_photo(open(myfile, 'rb'))
        elif myfile.lower().endswith('.gif'):
            update.effective_message.reply_document(open(myfile, 'rb'))
        elif myfile.lower().endswith(('.mp4', '.avi')):
            update.effective_message.reply_video(open(myfile, 'rb'))

def checkwords(update, context):
    MEMEDIR = SCRIPTPATH + "/Resources/Memes/"
    wordlist = re.sub("[^\w]", " ", update.effective_message.text.lower()).split()
    for word in wordlist:
        for meme in getmemes(MEMEDIR):
            regex = re.compile(r'^{}$'.format(meme[0]))
            if regex.search(word):
                update.effective_message.reply_photo(open(meme[1], 'rb'))
                return

if __name__ == '__main__':

    updater = Updater(TOKEN, use_context=True)
    dp = updater.dispatcher
    dp.add_handler(CommandHandler("random_text", randomtext))
    dp.add_handler(CommandHandler("random_picture", randommedia))
    dp.add_handler(CommandHandler("ping", ping))
    dp.add_handler(MessageHandler(Filters.text & ~Filters.command, checkwords))

    updater.start_polling()
    updater.idle()

    sys.exit(0)
