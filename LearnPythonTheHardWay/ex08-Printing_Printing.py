formatter1 = "{} {} {} {}"
formatter2 = "{}-{}-{}-{}"

print(formatter1.format(1,2,3,4),end = ' ')
print(formatter2.format("one","two",'three','four'))
print(formatter2.format(True,False,True,False))
print(formatter2.format(formatter1,formatter1,formatter1,formatter1))
print(formatter1.format(
    "Try your",
    "Own text here",
    "Maybe a poem",
    "Or a song about fear"
),end=' ')
