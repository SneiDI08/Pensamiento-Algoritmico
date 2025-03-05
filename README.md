# **Pensamiento Algorítmico**

Trabajos de Python y C++  

## **PRIMER PARCIAL PRIMER SEMESTRE - Proyectiles en Aetheria**

---

## **1. Introducción**
Este proyecto consiste en una herramienta para calcular el tiempo de impacto de proyectiles en el mundo de Aetheria, un popular MMORPG. Permite a los jugadores seleccionar un tipo de proyectil mágico y calcular su tiempo de impacto según la distancia del enemigo.

## **Instalación**
Para ejecutar el proyecto, sigue estos pasos:
1. Asegúrate de tener Python 3.x o un compilador de C++ instalado comi dev-C++.
3. Descarga visual studio code para poder programar y visualizar el codigo.
4. Asegurate de instalar las extenciones correspondientes de c++y python.


## **Guía de Uso**
1. Ejecuta el programa en Python o C++.
2. Ingresa la distancia al objetivo en metros.
3. Selecciona un tipo de proyectil:
   - **1. Fuego (120 m/s)**
   - **2. Hielo (100 m/s)**
   - **3. Veneno (80 m/s)**
4. El programa calculará y mostrará el tiempo de impacto.

## **Documentación Técnica**
El código está organizado en:
- **Constantes**: Definen las velocidades de los proyectiles.
- **Entrada del usuario**: Solicita distancia y tipo de proyectil.
- **Validación de datos**: Se asegura de que la entrada sea válida.
- **Cálculo del tiempo de impacto**: Se divide la distancia por la velocidad del proyectil.


### **_PROBLEMA_**

En el mundo de Aetheria, un popular MMORPG, los jugadores pueden lanzar diferentes tipos de proyectiles mágicos para derrotar a sus enemigos. Cada tipo de proyectil tiene una velocidad única, lo que afecta el tiempo que tarda en impactar en el objetivo. Tu tarea es ayudar a los jugadores a calcular el tiempo de impacto de sus proyectiles en función de la distancia al objetivo.

Eres un mago en Aetheria y tienes tres tipos de proyectiles mágicos: **Fuego**, **Hielo** y **Veneno**. Cada proyectil tiene una velocidad diferente:

- **Fuego**: 120 metros por segundo.
- **Hielo**: 100 metros por segundo.
- **Veneno**: 80 metros por segundo.

#### Dado el tipo de proyectil y la distancia al objetivo, debes calcular el tiempo que tardará el proyectil en impactar.

---

### **_REQUISITOS FUNCIONALES Y NO FUNCIONALES_**

#### **Requisitos Funcionales**
1. Definir constantes para las velocidades de los diferentes proyectiles.
2. Permitir al usuario seleccionar uno de los tres tipos de proyectiles.
3. Solicitar al usuario que ingrese la distancia al objetivo.
4. Calcular el tiempo de impacto basado en la velocidad del proyectil y la distancia ingresada.
5. Mostrar el tiempo de impacto al usuario.
6. Validar que el usuario solo ingrese números enteros o decimales para la distancia.
7. Validar que el usuario solo seleccione una de las tres opciones de proyectiles.

#### **Requisitos No Funcionales**
1. El programa no debe permitir la entrada de caracteres no numéricos (como letras o símbolos) en la distancia.
2. El programa debe ser claro y fácil de usar, con mensajes descriptivos para el usuario.
3. El código debe seguir las convenciones de estilo PEP 8 para Python y Google C++ Style Guide para C++.

---

### **_CASOS DE USO PRINCIPALES_**

Este programa puede ser utilizado como base para otros programas que requieran la selección de opciones o la toma de decisiones, como:
- Menús de selección en aplicaciones.
- Sistemas de chatbots que ofrecen opciones a los usuarios.
- Juegos que requieren cálculos basados en la elección del usuario.

---

### **_JUSTIFICACIÓN DE LA SOLUCIÓN_**

Para resolver este problema, se implementó una solución que permite al usuario ingresar la distancia al objetivo y seleccionar uno de los tres tipos de proyectiles. Dependiendo de la elección del usuario, el programa calcula el tiempo de impacto dividiendo la distancia por la velocidad del proyectil seleccionado. Se utiliza un bucle `while` para asegurar que el usuario solo seleccione una opción válida (1, 2 o 3).

#### **Pasos de la Solución:**
1. Se da la bienvenida al usuario.
2. El usuario ingresa la distancia al enemigo.
3. El usuario selecciona un tipo de proyectil:
   - **1. Hechizo de Fuego** (velocidad: 120 m/s).
   - **2. Hechizo de Hielo** (velocidad: 100 m/s).
   - **3. Hechizo de Veneno** (velocidad: 80 m/s).
4. El programa calcula el tiempo de impacto dividiendo la distancia por la velocidad del proyectil seleccionado.
5. Se muestra el tiempo de impacto al usuario.
6. Si el usuario selecciona una opción inválida, se le pide que ingrese una opción válida.

#### **Posibles Soluciones Alternativas:**
- Definir la distancia del enemigo desde el inicio y ofrecer opciones de ataque basadas en la distancia (por ejemplo, ataque cuerpo a cuerpo si el enemigo está cerca).
- Implementar un sistema de menú más complejo que incluya más tipos de proyectiles o habilidades.

---

### **_DIAGRAMA DE FLUJO_**

> Aquí se insertará un diagrama de flujo que represente el proceso de selección y cálculo del tiempo de impacto.

---

### **_DOCUMENTACIÓN DEL CÓDIGO_**

#### **Documentación Python**

```python
# Constantes para las velocidades de los proyectiles
VELOCIDAD_FUEGO = 120  # metros por segundo
VELOCIDAD_HIELO = 100  # metros por segundo
VELOCIDAD_VENENO = 80  # metros por segundo

# Solicitar al usuario la distancia al objetivo
distancia = float(input("¿A qué distancia se encuentra tu enemigo? (en metros): "))

# Bucle para asegurar que el usuario seleccione una opción válida
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
```

#### **Documentación C++**

```cpp
#include <iostream>
using namespace std;

int main() {
    const int VELOCIDAD_FUEGO = 120;
    const int VELOCIDAD_HIELO = 100;
    const int VELOCIDAD_VENENO = 80;
    
    double distancia;
    int opcion;
    
    cout << "¿A qué distancia se encuentra tu enemigo? (en metros): ";
    cin >> distancia;
    
    while (true) {
        cout << "Elige un hechizo para combatir:" << endl;
        cout << "1. Hechizo de Fuego (120 m/s)" << endl;
        cout << "2. Hechizo de Hielo (100 m/s)" << endl;
        cout << "3. Hechizo de Veneno (80 m/s)" << endl;
        cin >> opcion;
        
        if (opcion == 1) {
            cout << "El hechizo de Fuego tardará " << distancia / VELOCIDAD_FUEGO << " segundos en impactar." << endl;
            break;
        } else if (opcion == 2) {
            cout << "El hechizo de Hielo tardará " << distancia / VELOCIDAD_HIELO << " segundos en impactar." << endl;
            break;
        } else if (opcion == 3) {
            cout << "El hechizo de Veneno tardará " << distancia / VELOCIDAD_VENENO << " segundos en impactar." << endl;
            break;
        } else {
            cout << "Opción inválida. Por favor, selecciona una opción válida (1, 2 o 3)." << endl;
        }
    }
    return 0;
}
```

---

### **CONCLUSIONES**
conclusion.

### **LICENCIA**
Aqui que pongo :p.

### **CONTRIBUCIONES**
Puedes contribuir a lo que sea con este codigo, es totalmente abiero, puedes hacer comentario, o de paso modificar el codigo en su totalidad.

### **ERRORES COMUNES**
- Entrada no numérica en la distancia.
- Selección inválida de opción (solo 1, 2 o 3 permitidos).
