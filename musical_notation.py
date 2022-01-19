
tones = 'GFEDCBAgfedcba'
lines = set('FDBgea')

class Note:
    def __init__(self, s):
        self.tone = s[0]
        self.dur = 1 if len(s) == 1 else int(s[1:])

N = int(raw_input().rstrip())

notes = list(map(Note, raw_input().rstrip().split()))
duration = sum(note.dur for note in notes)

staff = [str(t) + ': ' for t in tones]
for n in notes:
    for i,t in enumerate(tones):
        if n.tone == t:
            staff[i] += '*' * n.dur
        else:
            staff[i] += ('-' if t in lines else ' ') * n.dur
        staff[i] += '-' if t in lines else ' '

print('\n'.join(s[:-1] for s in staff))
