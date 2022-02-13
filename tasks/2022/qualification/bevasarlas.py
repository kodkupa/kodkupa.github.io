# Bevásárlás megoldás

# Mohó elv alapján érdemes választani a gyümölcsleveket, először megveszünk a
# legolcsóbból annyit amennyit csak tudunk, aztán a második legolcsóbból és
# végül a harmadikból.

a = int(input())
b = int(input())
c = int(input())
# Ha nincs összesen 10 doboz, akkor a megoldás -1.
if (a + b + c < 10):
    print(-1)
# Ha van legalább 10 almalé, akkor csak azt veszünk.
elif (a >= 10):
    print(10 * 300)
# Egyébként megvesszük az összes almalevet, és ha baracklével együtt megvan
# a 10 doboz, akkor azokkal egészítjük ki.
elif (a + b >= 10):
    print(a * 300 + (10 - a) * 350)
# Ha nem elég az alma + barack, akkor mindet megvesszük és a maradékot
# pedig cseresznyéből, amennyi kell a 10 dobozhoz.
else:
    print(a * 300 + b * 350 + (10 - a - b) * 400)
