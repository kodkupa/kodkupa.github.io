#!/usr/bin/env python3

import sys

def main():
    data = list(map(int, sys.stdin.read().split()))
    t = data[0]
    idx = 1
    out_lines = []

    for _ in range(t):
        n = data[idx]
        idx += 1
        points = data[idx:idx + n]
        idx += n

        max_games = 0

        # Try every possible warmup length: 0..n
        for start in range(n + 1):
            score1 = score2 = 0
            games = 0

            # Competitive points start from index 'start'
            for p in points[start:]:
                if p == 1:
                    score1 += 1
                else:
                    score2 += 1

                # Check if someone wins the game
                if score1 >= 4 and score1 - score2 >= 2:
                    games += 1
                    score1 = score2 = 0
                elif score2 >= 4 and score2 - score1 >= 2:
                    games += 1
                    score1 = score2 = 0

            if games > max_games:
                max_games = games

        out_lines.append(str(max_games))

    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()

