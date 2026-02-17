#!/usr/bin/env python3
# @check-accepted: *

letter_to_nato = {
    "a": "alpha", "b": "bravo", "c": "charlie", "d": "delta",
    "e": "echo", "f": "foxtrot", "g": "golf", "h": "hotel",
    "i": "india", "j": "juliett", "k": "kilo", "l": "lima",
    "m": "mike", "n": "november", "o": "oscar", "p": "papa",
    "q": "quebec", "r": "romeo", "s": "sierra", "t": "tango",
    "u": "uniform", "v": "victor", "w": "whiskey", "x": "xray",
    "y": "yankee", "z": "zulu"
}

S = input().strip()

decoded = []
i = 0
while i < len(S):
    decoded.append(S[i])
    i += len(letter_to_nato[S[i]])


print("".join(decoded))
