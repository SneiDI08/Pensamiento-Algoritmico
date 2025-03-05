VELOCIDADFUEGO = 120 
VELOCIDADHIELO = 100  
VELOCIDAD_ENENO = 80 

distancia = float(input("¿A qué distancia se encuentra tu enemigo? (en metros): "))

while True:
    print("Elige un hechizo para combatir:")
    print("1. Hechizo de Fuego (120 m/s)")
    print("2. Hechizo de Hielo (100 m/s)")
    print("3. Hechizo de Veneno (80 m/s)")
    
    opcion = int(input("Selecciona una opción (1, 2 o 3): "))
    
    if opcion == 1:
        tiempo = distancia / VELOCIDAD_FUEGO
        print(f"El hechizo de Fuego tardará {tiempo} segundos en impactar.")
        break
    elif opcion == 2:
        tiempo = distancia / VELOCIDAD_HIELO
        print(f"El hechizo de Hielo tardará {tiempo} segundos en impactar.")
        break
    elif opcion == 3:
        tiempo = distancia / VELOCIDAD_VENENO
        print(f"El hechizo de Veneno tardará {tiempo} segundos en impactar.")
        break
    else:
        print("Opción inválida. Por favor, selecciona una opción válida (1, 2 o 3).")
