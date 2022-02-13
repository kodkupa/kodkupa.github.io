#!/usr/bin/env python3

# Szózat megoldás

# Ha n hosszú a szó és már k karakter fix akkor az első nem fix karakter
# (26-k)-féleképpen választható, a második (26-k-1)-féleképpen, majd
# (26-k-2)-féleképpen stb. Tehát a válasz (26-k)*(26-k-1)*...*(26-(n-1)) (mivel
# n-k karaktert kell lefixálnunk és (n-1)-(k)+1=n-k)

N = int(input())
L = input().split()

missing = L.count("_")
found = N - missing

ans = 1
for i in range(missing):
  ans *= 26 - found - i

print(ans)
