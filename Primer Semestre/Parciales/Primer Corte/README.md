# **Pensamiento Algorítmico**

Dady Sneider Loaiza Loaiza y Kamila Guzman

## **PRIMER PARCIAL PRIMER SEMESTRE - Proyectiles en Aetheria**

---

## **1. Introducción**
En este proyecto se evidencia el conocimiento de los estudiantes acerca de conceptos básicos de los lenguajes de C++ y Python a través de un problema que permita explorar criterios como el manejo adecuado de variables, constantes, condicionales, bucles, entre otros valores lógicos aprendidos.
El documento presenta los códigos junto con su explicación, la manera correcta de manejarlo y explicación de errores que usualmente suceden a la hora de programar.

## **Instalación en C++**
Para ejecutar el proyecto, sigue estos pasos:
1. Asegúrate de instalar un compilador de C++ en tu computadora, como Dev-C++.
2. En el instalador de Dev-C++, escoge el idioma de tu preferencia y, en tipo de instalación, selecciona "Todos".
3. Configura el entorno a tu gusto; puedes seleccionar tipografías y diferentes estilos.
4. Una vez en el entorno, para empezar a codificar en C++, puedes empezar a escribir el código o puedes abrir el código dejado en el repositorio.

## **Instalación en Python**
Para ejecutar el proyecto, sigue estos pasos:
1. Asegúrate de instalar Python desde su página oficial o desde la Microsoft Store en su última versión.
2. En el instalador, asegúrate de marcar la opción "Disable Path length limit".
3. Descarga Visual Studio Code desde su página oficial.
4. Una vez descargado todo, ve a Visual Studio y descarga la extensión de Python para su correcto funcionamiento.
5. En el explorador, asigna una carpeta donde se guardarán tus programas.
6. Crea un nuevo archivo "Nombre_del_programa.py"; asegúrate de que tu archivo lleve la terminación ".py".
7. Una vez en el entorno, para empezar a codificar en Python, puedes empezar a escribir el código o puedes abrir el código dejado en el repositorio.

## **Guía de Uso**
1. Tanto para C++ como para Python, hay que abrir sus respectivos compiladores de código.
2. Una vez en el compilador, escribimos o abrimos el programa dado.
3. Ejecutamos el código.
4. El programa pedirá al usuario una serie de datos, como la distancia a la que se encuentra el enemigo de ti; lo escribirás solo con números enteros.
5. Una vez establecida la distancia, tendrás que escoger uno de los hechizos otorgados: fuego, hielo y veneno, con 1, 2 y 3 respectivamente.
6. No podrás digitar números o caracteres fuera del alcance del programa; de lo contrario, se cerrará.
7. El programa te dirá el tiempo que tarda el hechizo en impactar al enemigo.
8. El programa se cerrará y podrás ejecutarlo nuevamente.

# **INFORME**

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
### ***Identificación de entradas, procesos y salidas esperadas.***
1. Entrada de Datos
  - Se solicita la distancia al enemigo (double d).
  - Se verifica si la entrada es válida.
  - Se muestra un menú para que el usuario seleccione uno de los tres hechizos disponibles.
2. Procesamiento de Datos
  - Se definen tres constantes (a = 120, b = 100, c = 80), que representan la velocidad de cada hechizo.
  - Según la opción elegida, se divide la distancia entre la velocidad correspondiente para calcular el tiempo de impacto.
  - Se almacena el resultado en x.
3. Salida de Datos
  - Se imprime un mensaje indicando qué hechizo fue seleccionado.
  - Se muestra el tiempo de impacto con dos decimales de precisión.

### **_JUSTIFICACIÓN DE LA SOLUCIÓN_**

Para resolver este problema, se implementó una solución que permite al usuario ingresar la distancia al objetivo y seleccionar uno de los tres tipos de proyectiles. Dependiendo de la elección del usuario, el programa calcula el tiempo de impacto dividiendo la distancia por la velocidad del proyectil seleccionado. Se utiliza un bucle while para asegurar que el usuario solo seleccione una opción válida (1, 2 o 3).

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

- Considero que esta es la mejor manera de hacer el algoritmo, pues está de forma que se pueda definir los valores para operarlos posteriormente y no surjan problemas o no ampliar de manera innecesaria el código. Por ejemplo, si el usuario selecciona el hechizo primero antes que definir la distancia del enemigo, dentro de los condicionales a cada uno de los tres hechizos deberíamos colocar a qué distancia se encuentra el enemigo, ampliando el código de manera innecesaria.

#### **Posibles Soluciones Alternativas:**
Podríamos utilizar "if" para dar opciones de ataque basadas en la distancia (por ejemplo, ataque cuerpo a cuerpo si el enemigo está cerca, si está lejos utilizar ataques con hechizos).
También podríamos implementar un sistema de menú más complejo que incluya más tipos de proyectiles o habilidades, y también evitar algunos errores que se podrían presentar en nuestro programa.

---

### **_DIAGRAMA DE FLUJO_**

> Aquí se insertará un diagrama de flujo que represente el proceso de selección y cálculo del tiempo de impacto.

---

## **Implementación**

#### **Documentación Python**

```python
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
```
---
# **Compilación de código en Linux (C++)**
# **Ejecución del Programa en Python**

Python es un lenguaje de programación interpretado, por lo que no requiere compilación como C++. Para ejecutar código en **Windows, Linux, macOS o iOS**, sigue los siguientes pasos.

---

## **Ejecutar Python en Windows, Linux y macOS**

### **1. Verificar si Python está instalado**
Antes de ejecutar un programa en Python, verifica si tienes Python instalado en tu sistema. Abre una terminal o línea de comandos y escribe:

```sh
python --version
```
o en algunos sistemas:
```sh
python3 --version
```
Si Python no está instalado, puedes descargarlo desde la [página oficial de Python](https://www.python.org/downloads/).

---

### **2. Crear un archivo Python**
Navega hasta el escritorio y crea una carpeta para el proyecto:

```sh
cd ~/Desktop  # Ir al escritorio
mkdir proyectiles  # Crear la carpeta 'proyectiles'
cd proyectiles  # Entrar a la carpeta
```
Crea un archivo con la extensión `.py` usando un editor de texto como `nano` en Linux/macOS o `notepad` en Windows:

```sh
nano proyectiles.py  # Para Linux/macOS
notepad proyectiles.py  # Para Windows
```

Luego, copia y pega el siguiente código dentro del archivo y guarda los cambios.
### **3. Ejecutar el código**
Para ejecutar el programa, usa el siguiente comando:

```sh
python proyectiles.py
```
o si tienes Python 3 instalado:

```sh
python3 proyectiles.py
```

---

## **Ejecutar el Programa en Python en iOS**
En iOS, no se puede ejecutar Python de manera nativa en la terminal, pero existen aplicaciones que permiten ejecutar código Python:

### **1. Usar una aplicación de Python en iOS**
Puedes descargar una de estas aplicaciones desde la App Store:
- [Pythonista 3](https://apps.apple.com/us/app/pythonista-3/id1085978097) (de pago)
- [Pyto](https://apps.apple.com/us/app/pyto-python-ide/id1436650069) (gratis)
- [Carnets - Jupyter](https://apps.apple.com/us/app/carnets/id1450994949) (gratis, basado en Jupyter)

### **2. Crear y ejecutar el código en Python**
#### **Pasos:**
1. Abre la aplicación **Pythonista 3** o **Pyto**.
2. Crea un nuevo archivo y nómbralo `proyectiles.py`.
3. Copia y pega el código Python en el archivo.
4. Guarda los cambios y ejecuta el código presionando el botón de "Play" ▶.

---

---
#### **Documentación C++**

```cpp
#include <iostream>
using namespace std; //El using namespace std se usa para no tener que escribir std:: antes de elementos que pertenecen al espacio de nombres

int main(){
    const int a = 120, b = 100, c = 80 ; //Aqui definimos las variables de velocidad de cada hechizo como usualmente lo hariamos, pero en este caso definimos "cons" lo cual evita que el valor de la variable sea modificada dentro del programa
    int x;
    double d;
    
    cout<<"Mago de Aetheria, has entrado en una pelea contra unos enemigos de la tierra"<<endl;

    cout<<"¿A que distancia se encuentra tu enemigo?"<<endl;
    cout<<"Distancia: ";
    cin>>d;

    if (typeid(d)!=typeid(int)){
        cout<<"No puedes ingresar letras"<<endl;
    } //Este bloque de codigo se usa para evitar errores de codigo y dado el caso cerrar el programa

    else{
    
        int e=0;
        
        while (e<1 || e>3){ //Este bloque de codigo hace que el usuario solo sea incapaz de digitar opciones incorrectas.
    
            cout<<"Elige un hechizo para combatir"<<endl;
            cout<<"1. Hechizo de fuego (Largo alcance)"<<endl;
            cout<<"2. Hechizo de hielo (Largo alcance)"<<endl;
            cout<<"3. Hechizo de veneno (Largo alcance)"<<endl;
    
            cin>>e;
            if(e == 1){
        
                cout<<"Has elegido el hechizo de fuego"<<endl;
                cout<<"Disparando el hechizo de fuego"<<endl;
                x = d/a;
                cout<<"El hechizo de fuego ha demora en impactar al enemigo en "<<x<<" segundos";
            }
            else if(e == 2){
                cout<<"Has elegido el hechizo de hielo"<<endl;
                cout<<"Disparando el hechizo de hielo"<<endl;
                x = d/b;
                cout<<"El hechizo de hielo ha demora en impactar al enemigo en "<<x<< " segundos";
            }
            else if(e == 3){
                cout<<"Has elegido el hechizo de veneno"<<endl;
                cout<<"Disparando el hechizo de veneno"<<endl;
                x = d/c;
                cout<<"El hechizo de veneno ha demora en impactar al enemigo en "<<x<< " segundos";
            }
            else{
                cout<<"Elige un hechizo valido"<<endl;
            }
        }
    }    
  return 0;
}
```
---
# **Compilación de código en Linux (C++)**

Para compilar y ejecutar el código en **Linux**, sigue estos pasos:

## **1. Abrir una terminal**
Puedes abrir la terminal con **`Ctrl + Alt + T`** o desde el menú de aplicaciones.

## **2. Navegar al escritorio y crear una carpeta**
```sh
cd ~/Desktop  # Ir al escritorio
mkdir proyectiles  # Crear una carpeta llamada 'proyectiles'
cd proyectiles  # Entrar a la carpeta
```
Crea un archivo con la terminacion de ".cpp" usando un editor de texto, como nano o notepadqq
```sh
nano proyectiles.cpp
```
Luego, pega el código dentro del archivo y guarda los cambios con enter.
para compilar el programa, usa g++ como la siguiente linea de codigo.
```sh
g++ proyectiles.cpp -o proyectiles
```
verificas el ejecutable con:
```sh
ls -l
```
y ejecutas el programa con:
```sh
./proyectiles
```
---
# **Ejecutar el Programa en C++ en iOS**

iOS no permite ejecutar directamente programas C++, pero puedes usar una aplicación en la nube o un compilador en línea.

## **1. Usar un compilador C++ en línea**
La forma más fácil de ejecutar C++ en iOS es mediante un compilador en línea:

- [JDoodle](https://www.jdoodle.com/c-online-compiler)
- [OnlineGDB](https://www.onlinegdb.com/)
- [Replit](https://replit.com/)

### **Pasos para usar JDoodle:**
1. Abre [JDoodle C++ Online Compiler](https://www.jdoodle.com/c-online-compiler) en Safari o Chrome.
2. Copia y pega el código en el editor.
3. Presiona **Run** y verás la salida del programa en la consola.

---

## **2. Usar una aplicación de C++ en iOS**
Existen algunas aplicaciones en la App Store que permiten compilar y ejecutar código C++ en iOS, como:

- [Cxxdroid (App Store)](https://apps.apple.com/us/app/cxxdroid-c-compiler-ide/id1449933348)  
- [Programming Hub (App Store)](https://apps.apple.com/us/app/programming-hub-learn-to-code/id1083697722)  

### **Pasos:**
1. Instalar **Cxxdroid** desde la App Store.
2. Abrir la aplicación y crear un nuevo archivo `proyectiles.cpp`.
3. Copiar y pegar el codigo dado en c++
---

## **Documentación Técnica**
En este programa te situa en una situacion especifica, donde tu eres un mago de Aetheria con tres hechizo, tú eliges un hechizo para atacar a un enemigo y tu dirás la distancia a la que se encuentra. Dependiendo del hechizo seleccionado y la distancia al objetivo, el programa calcula el tiempo que tardará en impactar el proyectil.

Este programa se organiza y se comppila en una serie de pasos secuenciales. Ltodo dentro del main() en el caso de c++, que se encarga de la entrada, el procesamiento y la salida. En cuanto Python no necesita de una funcion principal para funcionar.

1. Entrada de Datos
Se solicita la distancia al enemigo (double d).
Se verifica si la entrada es válida.
Se muestra un menú para que el usuario seleccione uno de los tres hechizos disponibles.
2. Procesamiento de Datos
Se definen tres constantes (a = 120, b = 100, c = 80), que representan la velocidad de cada hechizo.
Según la opción elegida, se divide la distancia entre la velocidad correspondiente para calcular el tiempo de impacto.
Se almacena el resultado en x.
3. Salida de Datos
Se imprime un mensaje indicando qué hechizo fue seleccionado.
Se muestra el tiempo de impacto con dos decimales de precisión.

Organización del Código
El código se estructura en un solo bloque dentro de main():

variables: Se definen las constantes de velocidad y las variables de entrada (d) y selección (e).
Entrada de usuario: Se pide la distancia y se verifica su validez.
Selección de hechizo: Un while controla que la elección del usuario sea válida.
Cálculo del tiempo: Se usa la fórmula tiempo = distancia / velocidad.
Salida del resultado: Se imprime la información al usuario de cuanto tardo en impactar el hechizo seleccionado.

## Ejemplo de uso

Mago de Aetheria, has entrado en una pelea contra unos enemigos de la tierra.
¿A qué distancia se encuentra tu enemigo?
Distancia: 240
Elige un hechizo para combatir:
1. Hechizo de fuego
2. Hechizo de hielo
3. Hechizo de veneno
Opción: 1
Has elegido el hechizo de fuego.
Disparando el hechizo de fuego...
El hechizo de fuego ha demorado en impactar al enemigo en 2.00 segundos.

### **ERRORES COMUNES**
- Entrada no numérica en la distancia.
- Selección inválida de opción (solo 1, 2 o 3 permitidos).

---

### **CONCLUSIONES**
conclusion.

### **LICENCIA**
Aqui que pongo :p.

### **CONTRIBUCIONES**
Puedes contribuir a lo que sea con este codigo, es totalmente abiero, puedes hacer comentario, o de paso modificar el codigo en su totalidad.
