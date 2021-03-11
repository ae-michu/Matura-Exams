# deklaracja stałych
iloscDanych = 1000

# deklaracja zmiennych
dane = []
najwiekszaLuka = 0
najmniejszaLuka = 0
dlugoscCiaguTemp = 2
dlugoscCiagu = 0
CiagOstatniaLiczba = 0
CiagOstatniaLiczbaPos = 0
krotnoscLuki = 0
krotnoscLukiTemp = 0
najczestszeLuki = []

# deklaracja pliku danych
plik = open("dane4.txt", "r")

# wczytanie danych do tablicy
for x in range(0, iloscDanych):
    dane.append(int(plik.readline()))
plik.close()

# szukanie najwiekszej i najmniejszej luki
for x in range(0, iloscDanych - 1):
    if abs(dane[x] - dane[x+1]) > najwiekszaLuka:
        najwiekszaLuka = abs(dane[x] - dane[x+1])
najmniejszaLuka = najwiekszaLuka
for x in range(0, iloscDanych - 1):
    if abs(dane[x] - dane[x+1]) < najmniejszaLuka:
        najmniejszaLuka = abs(dane[x] - dane[x+1])

# wypisanie wynikow do zadania 4.1
print("Najmniejsza luka: " + str(najmniejszaLuka))
print("Najwieksza luka: " + str(najwiekszaLuka))

# sprawdzenie dlugosci ciagu oraz ostatniej liczby ciagu
for x in range(0, iloscDanych - 2):
    if abs(dane[x] - dane[x+1]) == abs(dane[x+1] - dane[x+2]):
        dlugoscCiaguTemp += 1
        if dlugoscCiaguTemp > dlugoscCiagu:
            dlugoscCiagu = dlugoscCiaguTemp
            CiagOstatniaLiczba = dane[x+2]
            CiagOstatniaLiczbaPos = x+2
    else:
        dlugoscCiaguTemp = 2

# wypisanie wynikow do zadania 4.2
print("\nNajwieksza dlugosc fragmentu regularnego: " + str(dlugoscCiagu))
print("Poczatek: " + str(dane[CiagOstatniaLiczbaPos - (dlugoscCiagu-1)]))
print("Koniec: " + str(CiagOstatniaLiczba))

# szukanie luki o najwiekszej krotnosci
for x in range(0, iloscDanych - 1):
    x1 = abs(dane[x] - dane[x+1])
    for y in range(0, iloscDanych - 1):
        if abs(dane[y] - dane[y+1]) == x1:
            krotnoscLukiTemp+=1
    if krotnoscLukiTemp > krotnoscLuki:
        krotnoscLuki = krotnoscLukiTemp
    krotnoscLukiTemp = 0

# wypisanie wyniku luki o najwiekszej krotnosci
print("\nKrotnosc najczestszej luki: " + str(krotnoscLuki))

# szukanie luk o krotnosci rownej najwiekszej krotnosci
for x in range(0, iloscDanych - 1):
    krotnoscLukiTemp = 0
    x1 = abs(dane[x] - dane[x+1])
    for y in range(0, iloscDanych - 1):
        if abs(dane[y] - dane[y+1]) == x1:
            krotnoscLukiTemp+=1
    if krotnoscLukiTemp == krotnoscLuki:
        if abs(dane[x] - dane[x+1]) not in najczestszeLuki:
            najczestszeLuki.append(abs(dane[x] - dane[x+1]))

#wypisanie wszystkich luk o najwiekszej krotnosci
print("Wartosc najczestszych luk: ", end='')
for x in range(0, len(najczestszeLuki) - 1):
    print(najczestszeLuki[x], end=", ")
print(najczestszeLuki[len(najczestszeLuki) - 1])