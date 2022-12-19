import random
import os

def getrandomline(inputfile):
    if os.path.isfile(inputfile):
        rlines = open(inputfile).read().splitlines()
        for i in range(5):
            r = random.random()
            random.shuffle(rlines, lambda: r)
        return random.choice(rlines)

def getrandomtext(inputdir):
    if os.path.isdir(inputdir):
        rfiles = [os.path.join(root, name)
            for root, dirs, files in os.walk(inputdir)
                for name in files
                    if name.endswith(".txt")]
        for i in range(5):
            r = random.random()
            random.shuffle(rfiles, lambda: r)
        return random.choice(rfiles)

def getrandommedia(inputdir):
    if os.path.isdir(inputdir):
        rfiles = [os.path.join(root, name)
            for root, dirs, files in os.walk(inputdir)
                for name in files
                    if name.endswith((".jpg", ".gif", ".mp4", ".avi"))]
        for i in range(5):
            r = random.random()
            random.shuffle(rfiles, lambda: r)
        return random.choice(rfiles)

def getmemes(inputdir):
    if os.path.isdir(inputdir):
        mymemes = [os.path.join(root, name)
            for root, dirs, files in os.walk(inputdir)
                for name in files
                    if name.endswith((".jpg"))]
        memes = []
        for mymeme in mymemes:
            meme_clean = str(mymeme)
            meme_clean = meme_clean.replace(inputdir, "")
            meme_clean = meme_clean.replace(".jpg", "")
            memes.append((meme_clean, mymeme))
        return memes
