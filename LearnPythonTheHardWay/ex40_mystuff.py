"""
# this goes in mystuff.py
def apple():
    print("I AM APPLES!")

# this is just a variable
tangerine="Living reflection of a dream"
"""


class MyStuff(object):
    def __init__(self):     # There must be two '_'
        self.tangerine = "And now a thousand years between"

    def apple(self):
        print("I AM CLASSY APPLES!")


class Song(object):
    def __init__(self, llyrics):
        self.lyrics = llyrics

    def sing_me_a_song(self):
        for line in self.lyrics:
            print(line)