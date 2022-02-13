'''
Adott sor kvazi-izogram, ha a benne leggyakrabban elofordulo betu gyakorisaga legfeljebb 2 (vagy egyaltalan nem fordult benne elo betu).
A gyakorisagok szamontartasahoz hasznalhatunk peldaul tombot vagy szotarat (C++ nyelven std::map vagy std::unordered_map).
Fontos, hogy csak a betukkel foglalkozzunk, az egyeb karaktereket hagyjuk figyelmen kivul.
'''

from collections import defaultdict

n = int(input())

def quasi_isogram(line):
    chars = defaultdict(lambda: 0)
    for c in filter(lambda c: c.isalpha(), line.lower()):
        chars[c] += 1
    return 1 if len(chars) == 0 or max(chars.values()) <= 2 else 0

print(sum([quasi_isogram(input()) for _ in range(n)]))