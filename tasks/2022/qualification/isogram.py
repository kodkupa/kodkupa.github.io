'''
Adott sor kvázi-izogram, ha a benne leggyakrabban előforduló betű gyakorisága legfeljebb 2 (vagy egyáltalán nem fordult benne elő betű).
A gyakoriságok számontartásához használhatunk például tömböt vagy szótárat (C++ nyelven std::map vagy std::unordered_map).
Fontos, hogy csak a betűkkel foglalkozzunk, az egyéb karaktereket hagyjuk figyelmen kívül.
'''

from collections import defaultdict

n = int(input())

def quasi_isogram(line):
    chars = defaultdict(lambda: 0)
    for c in filter(lambda c: c.isalpha(), line.lower()):
        chars[c] += 1
    return 1 if len(chars) == 0 or max(chars.values()) <= 2 else 0

print(sum([quasi_isogram(input()) for _ in range(n)]))