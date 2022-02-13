#!/usr/bin/env python3

# Szozat megoldas

# Ha n hosszu a szo es mar k karakter fix akkor az elso nem fix karakter
# (26-k)-felekeppen valaszthato, a masodik (26-k-1)-felekeppen, majd
# (26-k-2)-felekeppen stb. Tehat a valasz (26-k)*(26-k-1)*...*(26-(n-1)) (mivel
# n-k karaktert kell lefixalnunk es (n-1)-(k)+1=n-k)

N = int(input())
L = input().split()

missing = L.count("_")
found = N - missing

ans = 1
for i in range(missing):
  ans *= 26 - found - i

print(ans)
