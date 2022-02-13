# Bevasarlas megoldas

# Moho elv alapjan erdemes valasztani a gyumolcsleveket, eloszor megveszunk a
# legolcsobbol annyit amennyit csak tudunk, aztan a masodik legolcsobbol es
# vegul a harmadikbol.

a = int(input())
b = int(input())
c = int(input())
# Ha nincs osszesen 10 doboz, akkor a megoldas -1.
if (a + b + c < 10):
    print(-1)
# Ha van legalabb 10 almale, akkor csak azt veszunk.
elif (a >= 10):
    print(10 * 300)
# Egyebkent megvesszuk az osszes almalevet, es ha baracklevel egyutt megvan
# a 10 doboz, akkor azokkal egeszitjuk ki.
elif (a + b >= 10):
    print(a * 300 + (10 - a) * 350)
# Ha nem eleg az alma + barack, akkor mindet megvesszuk es a maradekot
# pedig cseresznyebol, amennyi kell a 10 dobozhoz.
else:
    print(a * 300 + b * 350 + (10 - a - b) * 400)
