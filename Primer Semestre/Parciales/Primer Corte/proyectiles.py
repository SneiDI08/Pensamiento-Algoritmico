a:int=120
b:int=100
c:int=80
print("Mago de Aetheria, has entrado en una pelea contra unos enemigos")
d=int(input("¿A qué distancia se encuentra tu enemigo?\n"))
print("Elige un hechizo para combatir")
print("1. Hechizo de fuego (120m/s)")
print("2. Hechizo de hielo (100m/s)")
print("3. Hechizo de veneno (80m/s)")

e=int(input())
if e== 1:
    print("Has elegido el hechizo de fuego")
    print("Disparando el hechizo de fuego")
    x=d/a
    print (f"El hechizo de fuego ha impactado en {x} segundos")
elif e == 2:
    print("Has elegido el hechizo de hielo")
    print("Disparando el hechizo de hielo")
    x=d/b
    print(f"El hechizo de hielo ha impactado en {x} segundos")
elif e == 3:
    print("Has elegido el hechizo de veneno")
    print("Disparando el hechizo de veneno")
    x=d/c
    print(f"El hechizo de veneno ha impactado en {x} segundos")
else:
    print("Elige un hechizo válido")
