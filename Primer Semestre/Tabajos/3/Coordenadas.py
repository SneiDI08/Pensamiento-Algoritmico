matriz_coordenadas = []
caras = []
a = 0
b = 0
al = 0

while True:
    print("\n############################")
    print("#####        MENÚ      #####")
    print("############################")
    print("1. Ingresar vértices")
    print("2. Ingresar caras")
    print("3. Mostrar matrices")
    print("4. Salir")
    opcion = input("Seleccione una opción: ")
    if opcion == "1":
        a = int(input("Cuántos vértices quieres: "))
        matriz_coordenadas = []
        
        print("\n################################")
        print("##### Ingrese las coordenadas #####")
        print("################################\n")

        for i in range(a): 
            print(f"Vértice {i+1}")
            x = int(input(f"Ingrese x para el punto {i+1}: "))
            y = int(input(f"Ingrese y para el punto {i+1}: "))
            z = int(input(f"Ingrese z para el punto {i+1}: "))
            matriz_coordenadas.append([x, y, z])
            
        al = int(len(matriz_coordenadas))
    elif opcion == "2":
        if al < 3:
            print("\nPrimero debes ingresar los vértices, al menos 3.")

        else:
            b = int(input("¿Cuántas caras quieres conectar?: "))
            while b > a:
                print("Error: No puedes tener más caras que vértices.")
                b = int(input("¿Cuántas caras quieres conectar?: "))
            
            caras = []
            print("\n################################")
            print("##### Ingrese las caras #####")
            print("################################\n")

            for i in range(b):
                print(f"Cara {i+1}")
                c = int(input(f"¿Cuántos vértices tiene la cara {i+1}?: "))

                while c < 3 or c > a:
                    print("Error: Una cara debe tener al menos 3 vértices y no puede exceder los existentes.")
                    c = int(input(f"¿Cuántos vértices tiene la cara {i+1}?: "))

                cara = []
                for j in range(c):
                    v = int(input(f"Ingrese el índice del vértice {j+1} para la cara {i+1} (1 - {a}): "))
                    while v < 1 or v > a:
                        print(f"Error: El vértice debe estar entre 1 y {a}.")
                        v = int(input(f"Ingrese el índice del vértice {j+1} para la cara {i+1} (1 - {a}): "))
                    cara.append(v)

                caras.append(cara)  
    
    elif opcion == "3":
        if a == 0:
            print("\nNo hay datos ingresados aún.")
        else:
            print("\n#### Matriz de coordenadas ####\n")
            for i, coordenada in enumerate(matriz_coordenadas, 1):
                print(f"Vértice {i}: x = {coordenada[0]}, y = {coordenada[1]}, z = {coordenada[2]}")

            print("\n#### Caras ####\n")
            for i, cara in enumerate(caras, 1):
                print(f"Cara {i}: {cara}")
    
    elif opcion == "4":
        print("\nSaliendo del programa...")
        break
    
    else:
        print("\nOpción no válida, intenta de nuevo.")
