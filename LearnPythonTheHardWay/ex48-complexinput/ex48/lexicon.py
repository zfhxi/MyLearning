directions = ('north', 'south', 'east', 'west',
              'down', 'up', 'left', 'right', 'back')
verbs = ('go', 'stop', 'kill', 'eat')
stops = ('the', 'in', 'of', 'from', 'at', 'it')
nouns = ('door', 'bear', 'princess', 'cabinet')


def scan(stuff):
        words = stuff.split()
        sentence = []
        for word in words:
            if word in directions:
                sentence.append(('direction', word))
            elif word in verbs:
                sentence.append(('verb', word))
            elif word in stops:
                sentence.append(('stop', word))
            elif word in nouns:
                sentence.append(('noun', word))
            else:
                try:
                    sentence.append(('number', int(word)))
                except ValueError:
                    sentence.append(('error', word))

        return sentence
