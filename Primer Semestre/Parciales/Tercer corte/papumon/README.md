# Proyecto Papumon

## Integrantes del Equipo:
* [Dady Sneider Loaiza Loaiza]
* [David Hernandez Leyton]

---

## 1. Introducción

Papumon, es un pequeño minijuego inspirado en el famoso juego de Nintendo "Pokemon", el cual emula el sistema de batallas por turnos implementado en C++ utilizando la interfaz de línea de comandos (CLI). Este juego ofrece a los jugadores seleccionar y batallar con sus "Papumones", criaturas virtuales con habilidades para combatir y representaciones visuales distintivas en arte ASCII.

## 2. Problema

El programa "Papumon" aborda el desafío de crear un juego de batallas por turnos completamente funcional en el programa C++. Esto implica gestionar la lógica del juego, las estadísticas de los personajes, las interacciones del jugador y la representación visual. El objetivo es ofrecer una experiencia de juego completa que lo diferencie y tenga un valor agregado de los demas proyectos, esto con el fin de probar las capacidades de los estudiantes de elaborar un proyecto de esste nivel y comenzar a crear proyectos con POO (Programación orientada a objetos).

## 3. Explicación del Programa

"Papumon" es un juego de batallas por turnos donde los jugadores eligen un equipo de cinco Papumones para enfrentarse a otro jugador o a una Inteligencia Artificial. Cada Papumon tiene sus estadísticas (vida, defensa, aguante) y un conjunto de ataques de elementos, cada uno con un poder y un costo de aguante asociados.

El flujo principal del juego es el siguiente:
1.  **Menú Principal:** El jugador puede elegir entre iniciar una batalla contra otro jugador, contra la IA, o salir del juego.
2.  **Selección de Papumones:** Antes de la batalla, cada jugador (o el jugador contra la IA) selecciona cuidadosamente cinco Papumones de una lista de disponibles para formar su equipo. Se evita la selección de Papumones duplicados.
3.  **Batalla:**
    * La batalla se desarrolla por turnos.
    * Cada Papumon activo se muestra en pantalla junto con su barra de vida y aguante, y su arte ASCII distintivo.
    * En su turno, un jugador elige entre usar uno de los ataques de su Papumon o "curar" su aguante.
    * Los ataques consumen aguante y reducen la vida del Papumon oponente, teniendo en cuenta la defensa del defensor.
    * Si un Papumon pierde toda su vida, es derrotado y el siguiente Papumon del equipo entra en juego.
    * La batalla termina cuando un equipo derrota a todos los Papumones del oponente.

## 4. Explicaciónes del codigo.

### 4.1. Representación Visual con Arte ASCII

* **¿Para qué se implementó?**
    Se implementó para darle una identidad visual a cada Papumon dentro del entorno de la consola, mejorando la inmersión en el juego, a pesar de las limitaciones gráficas de una interfaz de línea de comandos.

* **¿Por qué se consideró necesario?**
    Aunque es un juego de consola, la representación visual es importante para diferenciar a los personajes y hacer la experiencia más agradable. El arte ASCII es una forma de lograr esto en un entorno de texto, permitiendo que cada Papumon tenga una apariencia distintiva.

* **¿Cómo se llevó a cabo su implementación?**
    Cada objeto `papumon` tiene un miembro `std::vector<std::string> ascii_art` que almacena las líneas de su representación ASCII. Estas representaciones se definen en el archivo `clases.cpp` al crear los Papumones:

    ```cpp
    // Ejemplo de cómo se define el arte ASCII para un Papumon en clases.cpp
    vector<string> ignivorax_art = {
        "   /\\_/\\   ",
        "  ( o.o )  ",
        "   > ^ <   ",
        "  /  Y  \\  ",
        " (_______) ",
        "  \"     \"  ",
        "           "
    };
    // Luego, se pasa al constructor de papumon
    papumon("Ignivorax", "Fuego", 100, 5, 30, ataques_fuego(), ignivorax_art),
    ```
    Según GEMINI (IA de google) se tenia que hacer una funcion la cual permita centrar el papumon  de la forma adecuada. La función `display_battle_state` (en `menus.cpp`) es la encargada de iterar sobre este vector y imprimir cada línea con un desplazamiento calculado para alinear el arte en la pantalla de batalla, creando una visualización lado a lado:

    ```cpp
    for (int i = 0; i < PAPUMON_ART_HEIGHT; ++i) {
        // Obtiene la línea actual del arte ASCII para cada Papumon
        string p1_art_line = (i < p1.ascii_art.size()) ? p1.ascii_art[i] : "";
        string p2_art_line = (i < p2.ascii_art.size()) ? p2.ascii_art[i] : "";

        // Calcula el offset para centrar cada pieza de arte dentro de su mitad
        int p1_line_offset = (PAPUMON_DISPLAY_WIDTH - p1_art_line.length()) / 2;
        int p2_line_offset = (PAPUMON_DISPLAY_WIDTH - p2_art_line.length()) / 2;

        cout << string(p1_line_offset, ' ') << p1_art_line;
        cout << string(ARENA_WIDTH - (p1_line_offset + p1_art_line.length()) - (p2_line_offset + p2_art_line.length()), ' ');
        cout << string(p2_line_offset, ' ') << p2_art_line << endl;
    }
    ```

### 4.2. Barras de Salud Visuales

* **¿Para qué se implementó?**
    En lugar de simplemente mostrar un número de puntos de vida, el juego presenta barras de salud progresivas (`[#####-----]`) que visualizan el estado de la vida de cada Papumon.

* **¿Por qué se consideró necesario?**
    Esto mejora la legibilidad y la inmersión del jugador. Una barra visual permite una evaluación mucho más rápida del estado de un Papumon en comparación con solo números, lo que es crucial en la dinámica de una batalla.

* **¿Cómo se llevó a cabo su implementación?**
    Según GEMINI (IA de google) la función `draw_health_bar` en `menus.cpp` calcula la porción de la barra que debe estar "llena" (con `#`) basándose en la vida actual y máxima del Papumon, y luego imprime la barra de texto.

    ```cpp
    void draw_health_bar(int current_hp, int max_hp, int length, int x_offset) {
        // Calcula cuántos '#' debe tener la barra
        int filled_length = static_cast<int>(static_cast<double>(current_hp) / max_hp * length);
        cout << string(x_offset, ' '); // Aplica el offset para centrar la barra
        cout << "[";
        for (int i = 0; i < length; ++i) {
            if (i < filled_length) {
                cout << "#"; // Parte llena de la barra
            } else {
                cout << "-"; // Parte vacía de la barra
            }
        }
        cout << "]";
        cout << " " << current_hp << "/" << max_hp << " HP"; // Muestra los valores numéricos
    }
    ```
    Esta función es llamada por `display_battle_state` para ambos Papumones en el campo.

### 4.3. Gestión de Recursos con "Aguante"

* **¿Para qué se implementó?**
    Más allá de solo puntos de vida, hemos introducido un sistema de "aguante" como recurso para los ataques. Cada ataque tiene un costo de aguante, y los Papumones deben gestionar este recurso sabiamente.

* **¿Por qué se consideró necesario?**
    Añade una capa estratégica al juego. No es solo atacar sin pensar; los jugadores deben considerar si tienen suficiente aguante para un ataque potente o si es mejor curarlo para turnos futuros.

* **¿Cómo se llevó a cabo su implementación?**
    La propiedad `aguante` está presente en la clase `papumon` y `uso` en la clase `ataque`. Durante los turnos de batalla, se verifica y consume el aguante. También se ofrece la opción de "curar aguante" que repone una cantidad fija, pero con un límite máximo para evitar el abuso.
  ---

    ```cpp
    // Fragmento del turno del Jugador en menu_batalla_vs_ia (menus.cpp)
    if (eleccion == 0) { // Opción para curar aguante
        if (atacante.aguante >= 50) { // Límite para no curar si ya tiene mucho
            cout << "Tienes mucho aguante.\n";
            // ... (manejo de espera y actualización de pantalla) ...
            continue;
        } else {
            atacante.aguante += 12; // Cantidad de aguante curado
            atacante.aguante = min(atacante.aguante, 50); // Asegura no exceder el límite
            cout << atacante.nombre << " ha curado su aguante.\n";
            // ... (manejo de espera) ...
            break;
        }
    }
    // ...
    if (atacante.aguante < atacante.ataques[eleccion - 1].uso) {
        cout << atacante.nombre << " se ha quedado sin aguante y no puede atacar.\n";
        // ... (manejo de espera y actualización de pantalla) ...
        continue;
    }
    // ...
    atacante.aguante -= atacante.ataques[eleccion - 1].uso; // Se consume el aguante al atacar
    ```

### 4.4. Reutilización de Objetos Papumon para Batallas

* **¿Para qué se implementó?**
    En lugar de crear nuevas instancias de Papumones para cada batalla o turno, se trabaja directamente con referencias a los objetos `papumon` existentes en los vectores de equipo.

* **¿Por qué se consideró necesario?**
    Esta aproximación es más eficiente en memoria y en rendimiento, ya que evita la creación y destrucción constante de objetos. Además, y más importante, permite que los cambios en las estadísticas (vida, aguante) de los Papumones persistan a lo largo de los turnos y entre los cambios de Papumon en batalla.

* **¿Cómo se llevó a cabo su implementación?**
    Las funciones de batalla (`menu_batalla_vs_ia` y `menu_batalla`) reciben los equipos de Papumones como `vector<papumon>&` (referencias a vectores). Dentro del bucle de batalla, se utilizan referencias (`auto&`) a los Papumones activos (`jugador_papumon`, `ia_papumon`), asegurando que cualquier modificación a sus propiedades (vida, aguante) afecte directamente a los objetos originales en los vectores de equipo.

    ```cpp
    void menu_batalla_vs_ia(vector<papumon>& equipo_jugador, vector<papumon>& equipo_ia) {
        // ...
        while (indice_jugador < equipo_jugador.size() && indice_ia < equipo_ia.size()) {
            // Se obtienen referencias a los Papumones activos del equipo
            auto& jugador_papumon = equipo_jugador[indice_jugador];
            auto& ia_papumon = equipo_ia[indice_ia];
            // ... cualquier cambio a 'jugador_papumon' o 'ia_papumon'
            // modifica directamente el objeto dentro del vector 'equipo_jugador' o 'equipo_ia'
        }
        // ...
    }
    ```
    ### 4.5. Batalla PVE

1.  **Prioridad de Curación de Aguante:**
        * La IA primero verifica si el `aguante` de su Papumon activo es bajo (actualmente, `menor a 20`).
        * Si es así, y si el aguante no ha alcanzado ya su límite de curación (50), la IA **priorizará curar su aguante** en 12 puntos. Esto es crucial para asegurar que la IA no se quede sin recursos para atacar.

        ```cpp
        if (atacante.aguante < 20) { // Si el aguante es bajo
            if (atacante.aguante < 50) { // Y si puede curar más
                atacante.aguante += 12;
                atacante.aguante = min(atacante.aguante, 50);
                cout << atacante.nombre << " ha curado su aguante.\n";
                attacked = true;
            }
        }
        ```

    2.  **Selección de Ataque Aleatoria:**
        * Si la IA ya realizó una acción (curó aguante) o si no necesitaba curarlo, procederá a intentar atacar.
        * Primero, recopila una lista (`vector<int> usable_attacks`) de los **índices de todos los ataques** que su Papumon activo puede usar con su `aguante` actual (es decir, `atacante.aguante >= ataque.uso`).
        * Si esta lista de ataques utilizables no está vacía, la IA **elige uno de estos ataques al azar** utilizando `uniform_int_distribution` y `mt19937`.
        * Una vez elegido el ataque, se calcula y aplica el `daño` al Papumon del jugador, y se consume el `aguante` del Papumon de la IA.

        ```cpp
        if (!attacked) { // Si la IA no ha curado aguante
            vector<int> usable_attacks;
            for (size_t i = 0; i < atacante.ataques.size(); ++i) {
                if (atacante.aguante >= atacante.ataques[i].uso) {
                    usable_attacks.push_back(i); // Agrega índices de ataques que puede usar
                }
            }

            if (!usable_attacks.empty()) { // Si hay ataques que puede usar
                uniform_int_distribution<> distrib(0, usable_attacks.size() - 1);
                int chosen_attack_index = usable_attacks[distrib(gen)]; // Elige uno al azar

                // ... (cálculo y aplicación de daño) ...
                cout << atacante.nombre << " usó " << atacante.ataques[chosen_attack_index].nombre
                     << " y causó " << daño << " de daño.\n";
                attacked = true;
            }
            // ... (manejo de caso si no hay ataques usables) ...
        }
        ```

    3.  **Manejo de Sin Opciones:**
        * En el raro caso de que el Papumon de la IA no tenga aguante para ningún ataque disponible y tampoco haya podido curar su aguante (por ejemplo, porque ya estaba casi al máximo), la IA simplemente informará que no pudo realizar ninguna acción.

    Esta estrategia básica pero efectiva asegura que la IA sea un oponente funcional y que sus acciones sean lógicas dentro del contexto del juego, proporcionando un desafío justo y variado en cada partida.
    
* **Rejugabilidad y Accesibilidad:** Una IA proporciona un oponente constante y disponible, lo que permite a los jugadores disfrutar del juego en solitario sin depender de la disponibilidad de un segundo jugador.

* **Variedad de Experiencia de Juego:** Al ofrecer tanto un modo de jugador contra jugador como un modo de jugador contra IA, el juego presenta diferentes tipos de desafíos.

### 5. Uso de Librerías y Encabezados Estándar de C++

El proyecto "Papumon" hace un uso de las librerías estándar de C++ para manejar diversas funcionalidades, desde la entrada/salida hasta la generación de números aleatorios y la manipulación de cadenas de texto. A continuación, se detallan las principales librerías utilizadas y su propósito:

* **`<string>`:**
    * **Propósito:** Proporciona la clase `std::string` para trabajar con cadenas de caracteres de manera más segura y flexible que los arreglos de caracteres tradicionales de C.
    * **Uso en el proyecto:** Se utiliza ampliamente para nombres de Papumones, nombres de ataques, tipos de Papumones y para construir las líneas de arte ASCII.
    * **Ejemplo:**
        ```cpp
        #include <string> // Incluido en clases.h, menus.h, menus.cpp
        // ...
        std::string nombre; // Declaración de una variable de tipo string
        // ...
        papumon::papumon(std::string nombre, /* ... */) : nombre(nombre) { /* ... */ } // Uso en el constructor
        ```

* **`<vector>`:**
    * **Propósito:** Proporciona la plantilla de clase `std::vector`, que es un contenedor de secuencia que permite almacenar elementos de un mismo tipo de forma dinámica (su tamaño puede crecer o reducirse en tiempo de ejecución).
    * **Uso en el proyecto:** Es esencial para almacenar:
        * Los ataques de un Papumon (`std::vector<ataque> ataques;`).
        * Los equipos de Papumones de cada jugador (`std::vector<papumon> equipo_jugador;`).
        * El arte ASCII de cada Papumon (`std::vector<std::string> ascii_art;`), donde cada `string` es una línea del dibujo.
    * **Ejemplo:**
        ```cpp
        #include <vector> // Incluido en clases.h, menus.h
        // ...
        class papumon {
        public:
            std::vector<ataque> ataques; // Vector de objetos 'ataque'
            std::vector<std::string> ascii_art; // Vector de strings para el arte ASCII
        };
        // ...
        void menu_batalla_vs_ia(vector<papumon>& equipo_jugador, vector<papumon>& equipo_ia) { /* ... */ } // Paso de equipos como vectores
        ```

* **`<cstdlib>`:**
    * **Propósito:** Contiene funciones para utilidades generales, incluyendo `system()`, que permite ejecutar comandos del sistema operativo.
    * **Uso en el proyecto:** Principalmente para la función `system("cls");` (en Windows) que limpia la pantalla de la consola, proporcionando una interfaz de usuario más limpia y actualizada en cada turno de batalla o cambio de menú.
    * **Ejemplo:**
        ```cpp
        #include <cstdlib> // Incluido en menus.cpp
        // ...
        system("cls"); // Limpia la pantalla de la consola
        ```

* **`<algorithm>`:**
    * **Propósito:** Proporciona una colección de funciones para operaciones en rangos de elementos, como `min()`, `max()`, `shuffle()`, etc.
    * **Uso en el proyecto:**
        * `min()`: Se utiliza para limitar el `aguante` y la `vida` de los Papumones, asegurando que no excedan sus valores máximos o no sean negativos.
        * `max()`: Para asegurar que el daño infligido no sea negativo.
        * `shuffle()`: Para la selección aleatoria del equipo de la IA en `menu_seleccion` (si se hubiera implementado así, en este código se usa una selección aleatoria más directa en `main` o al inicio de `menu_batalla_vs_ia`).
    * **Ejemplo:**
        ```cpp
        #include <algorithm> // Incluido en menus.cpp
        // ...
        atacante.aguante = min(atacante.aguante, 50); // Limita el aguante a 50
        int daño = max(0, atacante.ataques[eleccion - 1].poder - defensor.defensa); // Daño mínimo de 0
        ```

* **`<random>`:**
    * **Propósito:** Proporciona herramientas avanzadas para la generación de números aleatorios..
    * **Uso en el proyecto:** Es crucial para la lógica de la IA. Se utiliza `std::random_device` como fuente de semilla no determinística y `std::mt19937` como el motor de números pseudoaleatorios. `std::uniform_int_distribution` se emplea para generar índices aleatorios dentro de un rango específico (por ejemplo, para seleccionar un ataque aleatorio).
    * **Ejemplo:**
        ```cpp
        #include <random> // Incluido en menus.cpp
        // ...
        random_device rd; // Fuente de entropía
        mt19937 gen(rd()); // Motor de números aleatorios, sembrado con rd
        // ...
        uniform_int_distribution<> distrib(0, usable_attacks.size() - 1); // Distribución para un rango
        int chosen_attack_index = usable_attacks[distrib(gen)]; // Genera un índice aleatorio
        ```

* **`<chrono>` y `<thread>`:**
    * **Propósito:**
        * `<chrono>`: Proporciona tipos y funciones para manejar duraciones y puntos en el tiempo.
        * `<thread>`: Permite la creación y gestión de hilos, incluyendo funciones para pausar la ejecución del hilo actual.
    * **Uso en el proyecto:** Se utilizan en conjunto para introducir pausas controladas en la ejecución del programa (`this_thread::sleep_for`). Esto es util para mejorar la experiencia del usuario en la consola, permitiendo que los mensajes de acción y los cambios en la pantalla sean leídos y procesados por el jugador antes de que la pantalla se actualice o se pase al siguiente turno.
    * **Ejemplo:**
        ```cpp
        #include <chrono> // Incluido en menus.cpp
        #include <thread> // Incluido en menus.cpp
        // ...
        this_thread::sleep_for(chrono::seconds(2)); // Pausa la ejecución por 2 segundos
        ```
### 6. Integración de la Inteligencia Artificial (IA) en el Proceso de Desarrollo del Proyecto

A continuación, se detalla cómo la IA pudo haber sido utilizada en el proceso de construcción del Papumon Game:

#### 6.1. Organización y Estructuración del Código

* **Identificación de Patrones:** Las herramientas de IA pueden analizar el código existente o las ideas iniciales para sugerir cómo organizar las clases, funciones y la estructura general del proyecto. Por ejemplo, al definir las propiedades de un "Papumon" o de un "ataque", la IA puede haber ayudado a identificar que estos conceptos requerirían sus propias clases (`papumon`, `ataque`) y cómo deberían relacionarse (un `papumon` tiene varios `ataque`s).
* **Refactorización y Nomenclatura:** La IA puede ofrecer sugerencias para refactorizar código repetitivo o complejo en funciones más pequeñas y manejables. También es excelente para proponer nombres claros y consistentes para variables, funciones y clases (por ejemplo, `menu_batalla_vs_ia` vs. `menu_batalla`, o `display_battle_state`).

#### 6.2. Asistencia en la Construcción Lógica del Código

* **Diseño de Algoritmos:** Al abordar problemas como el cálculo de daño, la gestión de aguante o la alternancia de turnos, la IA puede ayudar a esbozar la lógica del algoritmo. Por ejemplo, al preguntar "cómo calcular el daño en un RPG por turnos considerando ataque y defensa", la IA podría sugerir `daño = max(0, poder_ataque - defensa_defensor)`.
* **Generación de Fragmentos de Código:** Para tareas repetitivas o para implementar patrones comunes (como un bucle de juego, un menú interactivo, o la lectura segura de entrada del usuario), la IA puede generar fragmentos de código listos para usar o para adaptar, acelerando el desarrollo. Por ejemplo, el bucle `while(true)` para la validación de entrada del jugador o la lógica para alternar turnos.
* **Propuesta de Estrategias para la IA del Oponente:** Aunque la IA del juego es sencilla, herramientas de IA pueden ayudar a conceptualizar y refinar su lógica. Por ejemplo, al pedir "dame una estrategia simple para una IA en un juego por turnos", la IA podría sugerir priorizar la curación si la salud/recursos son bajos, y luego atacar al azar.

#### 6.3. Corrección de Errores

* **Análisis de Errores de Compilación de Ejecución:** Cuando surgen errores de compilación (como `undeclared identifier` o `type mismatch`) o errores en tiempo de ejecución (segmentation faults, lógica incorrecta), la IA puede analizar los mensajes de error y el código circundante para identificar la causa raíz y proponer soluciones.
* **Detección de Bugs Lógicos:** Para problemas donde el código compila pero no se comporta como se espera (ej. el aguante no se cura correctamente, el daño no se aplica bien), la IA puede revisar la lógica y señalar posibles fallos o casos no considerados. Por ejemplo, el uso de `min` y `max` para asegurar que las variables de vida y aguante se mantengan dentro de rangos válidos.

#### 6.4. Petición de Ayuda y Clarificación de Conceptos

* **Explicación de Sintaxis/Conceptos:** Cuando se encuentra con una característica de C++ desconocida o un concepto complejo (como paso por referencia `&`, generadores de números aleatorios en `<random>`, o las peculiaridades de `std::vector`), la IA puede proporcionar explicaciones claras, ejemplos de código y mejores prácticas.
* **Optimización de Rendimiento/Legibilidad:** La IA puede ofrecer consejos sobre cómo escribir código más eficiente o más legible, por ejemplo, sugiriendo el uso de referencias `auto&` para evitar copias innecesarias de objetos grandes como `papumon` en los bucles de batalla.
* **Documentación:** La IA es una herramienta excelente para generar o mejorar la documentación del código, incluyendo comentarios, descripciones de funciones y secciones para el `README.md`, como esta misma.

## 7. Cómo Compilarlo en C++ usando Visual Studio 2022

Para compilar y ejecutar el proyecto "Papumon Game" en Visual Studio 2022, sigue estos pasos:

1.  **Descargar el Repositorio:** Clona o descarga el repositorio del proyecto en tu máquina local. Asegúrate de tener la carpeta `Papumon_CLI_Game` en la raíz de tu proyecto.

2.  **Abrir Visual Studio 2022:** Inicia Visual Studio 2022.

3.  **Crear un Nuevo Proyecto:**
    * En la pantalla de inicio de Visual Studio, selecciona "Crear un proyecto nuevo".
    * En la barra de búsqueda de plantillas, busca "Aplicación de consola" y selecciona "Aplicación de consola (C++)".
    * Haz clic en "Siguiente".
    * Asigna un nombre al proyecto (ej. `PapumonGameProject`) y elige una ubicación para guardarlo. Asegúrate de que la "Ubicación" del proyecto sea el directorio *padre* donde se encuentra la carpeta `Papumon_CLI_Game`.
    * Haz clic en "Crear".

4.  **Configurar Archivos de Origen:**
    * En el "Explorador de soluciones" (generalmente a la derecha), expande tu proyecto (ej. `PapumonGameProject`).
    * Haz clic derecho en la carpeta "Archivos de código fuente" y selecciona "Agregar" -> "Elemento existente...".
    * Navega a la carpeta `Papumon_CLI_Game` dentro de tu repositorio descargado.
    * Selecciona `main.cpp`, `clases.cpp`, y `menus.cpp`. Haz clic en "Agregar".
    * Repite el proceso para los "Archivos de encabezado": haz clic derecho en la carpeta "Archivos de encabezado", selecciona "Agregar" -> "Elemento existente...", y selecciona `clases.h` y `menus.h`. Haz clic en "Agregar".
    * **Importante:** Elimina el archivo `*.cpp` que Visual Studio crea por defecto con el nuevo proyecto (generalmente `PapumonGameProject.cpp` o `Source.cpp` en "Archivos de código fuente") para evitar conflictos de múltiples funciones `main`. Haz clic derecho sobre él y selecciona "Eliminar".

5.  **Compilar y Ejecutar:**
    * Asegúrate de que la configuración de la solución sea "Depuración" y "x64" (o "x86" si tu sistema es de 32 bits, aunque x64 es lo más común).
    * Haz clic en el botón "Iniciar depuración" (el triángulo verde) o ve a "Depurar" -> "Iniciar depuración" (o Ctrl + F5 para iniciar sin depurar).

Visual Studio compilará el código y ejecutará el programa en una ventana de consola.

## 8. Conclusión

"Papumon" es una demostración de cómo se pueden implementar las mecánicas de un juegode batallas por turnos en un entorno de línea de comandos utilizando C++. El proyecto destaca por su sistema de combate estratégico, la inclusión de una IA para un solo jugador y la atención al detalle en la presentación visual a través del arte ASCII. Este proyecto no solo cumple con los requisitos funcionales de un juego de batallas, sino que también explora soluciones creativas para las limitaciones de la CLI, ofreciendo una experiencia de juego atractiva y rejugable. Es un testimonio de que la creatividad en el desarrollo de juegos no se limita a entornos gráficos complejos, sino que puede prosperar en la simplicidad y el ingenio de la programación en consola.

---

### **9. CONTRIBUCIONES**
Puedes contribuir a lo que sea con este codigo, es totalmente abiero, puedes hacer comentario, o de paso modificar el codigo en su totalidad.

---

### **10. ATRIBUCIONES Y RECONOCIMIENTOS**

Este proyecto se ha desarrollado con la valiosa ayuda y el conocimiento compartido por diversos creadores de contenido educativo. Agradecemos su contribución que ha sido fundamental para la implementación de ciertas funcionalidades y la comprensión de conceptos clave en C++.

Extendemos un especial reconocimiento a:

* **Tutos Edgar**
    * **Contribución:** Su contenido y explicaciones fueron cruciales para la elaboración de la estructura y la lógica de los menús interactivos del juego.
    * **Recurso Específico:** Video disponible en [youtube.com/1](https://www.youtube.com/watch?v=ogi2b30Klcg&t=102s&pp=ygUUY3JlYXIgdW4gbWVudSBlbiBjKys%3D) (Se recomienda verificar el enlace y, si es posible, especificar el título del video para mayor claridad).

* **Programación ATS**
    * **Contribución:** Sus recursos fueron de gran ayuda para profundizar en la comprensión y aplicación del concepto de clases en C++, pilar fundamental de la organización de este proyecto.
    * **Recurso Específico:** Video disponible en [youtube.com/2](https://www.youtube.com/watch?v=tbVHbfIVxs4&t=350s&pp=ygUNY2xhc2VzIGVuIGMrKw%3D%3D) (Se recomienda verificar el enlace y, si es posible, especificar el título del video para mayor claridad).

---
