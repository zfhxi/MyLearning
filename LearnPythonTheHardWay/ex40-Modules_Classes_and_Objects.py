"""
#import ex40_mystuff
ex40_mystuff.apple()
print(ex40_mystuff.tangerine)
"""
# from ex40_mystuff import MyStuff
from ex40_mystuff import *

thing = MyStuff()
thing.apple()
print(thing.tangerine)

happy_bday = Song(["Happy birthday to you",
                   "I don't want to get sued",
                   "So I'll stop right there"])

bulls_on_parade = Song(["They rally around tha family",
                        "With pockets full of shells"])

happy_bday.sing_me_a_song()
bulls_on_parade.sing_me_a_song()