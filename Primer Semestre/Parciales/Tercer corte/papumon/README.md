# Proyecto Papumon

## Integrantes del Equipo:
* [Nombre Completo del Compañero 1]
* [Nombre Completo del Compañero 2]

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

A pesar de ser un juego de consola, hemos implementado características que normalmente se encuentran en interfaces gráficas o juegos más complejos, enriqueciendo la experiencia del usuario:

### 4.1. Representación Visual Dinámica con Arte ASCII

* **¿Para qué se implementó?**
    Se implementó para darle una identidad visual única y atractiva a cada Papumon dentro del entorno de la consola, mejorando la inmersión del jugador a pesar de las limitaciones gráficas de una interfaz de línea de comandos.

* **¿Por qué se consideró necesario?**
    Aunque es un juego de consola, la representación visual es importante para diferenciar a los personajes y hacer la experiencia más agradable. El arte ASCII es una forma creativa y efectiva de lograr esto en un entorno de texto, permitiendo que cada Papumon tenga una apariencia distintiva.

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
    La función `display_battle_state` (en `menus.cpp`) es la encargada de iterar sobre este vector y imprimir cada línea con un desplazamiento calculado para alinear el arte en la pantalla de batalla, creando una visualización dinámica lado a lado:

    ```cpp
    // Fragmento de menus.cpp dentro de display_battle_state
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
    La función `draw_health_bar` en `menus.cpp` calcula la porción de la barra que debe estar "llena" (con `#`) basándose en la vida actual y máxima del Papumon, y luego imprime la barra de texto.

    ```cpp
    // Fragmento de menus.cpp
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
    Añade una capa estratégica al juego. No es solo atacar sin pensar; los jugadores deben considerar si tienen suficiente aguante para un ataque potente o si es mejor curarlo para turnos futuros, lo que enriquece la toma de decisiones tácticas.

* **¿Cómo se llevó a cabo su implementación?**
    La propiedad `aguante` está presente en la clase `papumon` y `uso` en la clase `ataque`. Durante los turnos de batalla, se verifica y consume el aguante. También se ofrece la opción de "curar aguante" que repone una cantidad fija, pero con un límite máximo para evitar el abuso.

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
    Esta aproximación es más eficiente en memoria y en rendimiento, ya que evita la creación y destrucción constante de objetos. Además, y más importante, permite que los cambios en las estadísticas (vida, aguante) de los Papumones persistan a lo largo de los turnos y entre los cambios de Papumon en batalla, manteniendo la coherencia del estado del juego.

* **¿Cómo se llevó a cabo su implementación?**
    Las funciones de batalla (`menu_batalla_vs_ia` y `menu_batalla`) reciben los equipos de Papumones como `vector<papumon>&` (referencias a vectores). Dentro del bucle de batalla, se utilizan referencias (`auto&`) a los Papumones activos (`jugador_papumon`, `ia_papumon`), asegurando que cualquier modificación a sus propiedades (vida, aguante) afecte directamente a los objetos originales en los vectores de equipo.

    ```cpp
    // Fragmento de menu_batalla_vs_ia (menus.cpp)
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

## 5. Justificación de la IA

La implementación de una Inteligencia Artificial en "Papumon Game" se justifica por varias razones clave:

* **Rejugabilidad y Accesibilidad:** Una IA proporciona un oponente constante y disponible, lo que permite a los jugadores disfrutar del juego en solitario sin depender de la disponibilidad de un segundo jugador. Esto aumenta significativamente la rejugabilidad y la accesibilidad del juego.
* **Curva de Aprendizaje y Práctica:** La IA sirve como un excelente compañero de entrenamiento para los nuevos jugadores, permitiéndoles familiarizarse con la mecánica del juego, los ataques y la gestión de Papumones antes de enfrentarse a un oponente humano.
* **Variedad de Experiencia de Juego:** Al ofrecer tanto un modo de jugador contra jugador como un modo de jugador contra IA, el juego presenta diferentes tipos de desafíos. La IA, aunque con una lógica sencilla, introduce un elemento de imprevisibilidad en la batalla.
* **Demostración de Habilidades de Programación:** La implementación de una IA, incluso una básica, demuestra la capacidad de diseñar y programar lógica de comportamiento para entidades no controladas por el usuario, un componente fundamental en el desarrollo de juegos. La IA actual prioriza curar aguante si está bajo y, de lo contrario, elige un ataque aleatorio que pueda usar, lo que le da un comportamiento reactivo y estratégico básico.

    ```cpp
    // Fragmento del turno de la IA en menu_batalla_vs_ia (menus.cpp)
    else { // Turno de la IA
        auto& atacante = ia_papumon;
        auto& defensor = jugador_papumon;

        cout << "\nTurno de la IA (" << atacante.nombre << ")\n";
        this_thread::sleep_for(chrono::seconds(1));

        bool attacked = false;
        // Estrategia de la IA: Prioriza curar aguante si es bajo
        if (atacante.aguante < 20) {
            if (atacante.aguante < 50) {
                atacante.aguante += 12;
                atacante.aguante = min(atacante.aguante, 50);
                cout << atacante.nombre << " ha curado su aguante.\n";
                attacked = true;
            }
        }

        if (!attacked) { // Si la IA no ha curado aguante, intenta atacar
            vector<int> usable_attacks;
            // Recopila los índices de los ataques que puede usar con su aguante actual
            for (size_t i = 0; i < atacante.ataques.size(); ++i) {
                if (atacante.aguante >= atacante.ataques[i].uso) {
                    usable_attacks.push_back(i);
                }
            }

            if (!usable_attacks.empty()) { // Si hay ataques utilizables
                // Elige un ataque al azar de la lista de ataques utilizables
                uniform_int_distribution<> distrib(0, usable_attacks.size() - 1);
                int chosen_attack_index = usable_attacks[distrib(gen)];

                // Calcula y aplica el daño, consume aguante
                int daño = max(0, atacante.ataques[chosen_attack_index].poder - defensor.defensa);
                atacante.aguante -= atacante.ataques[chosen_attack_index].uso;
                defensor.vida -= daño;
                defensor.vida = max(0, defensor.vida);

                cout << atacante.nombre << " usó " << atacante.ataques[chosen_attack_index].nombre
                     << " y causó " << daño << " de daño.\n";
                attacked = true;
            } else {
                // En caso de que no tenga ataques disponibles y no haya curado aguante
                if (atacante.aguante < 50) { // Si aún puede curar
                    atacante.aguante += 12;
                    atacante.aguante = min(atacante.aguante, 50);
                    cout << atacante.nombre << " no pudo atacar y curó su aguante.\n";
                    attacked = true;
                } else {
                    cout << atacante.nombre << " no pudo atacar ni curar.\n";
                }
            }
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
    ```

## 6. Cómo Compilarlo en C++ usando Visual Studio 2022

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

## 7. Conclusión

"Papumon Game" es una demostración robusta de cómo se pueden implementar las mecánicas de un juego de rol de batallas por turnos en un entorno de línea de comandos utilizando C++. El proyecto destaca por su sistema de combate estratégico, la inclusión de una IA para un solo jugador y la atención al detalle en la presentación visual a través del arte ASCII. Este proyecto no solo cumple con los requisitos funcionales de un juego de batallas, sino que también explora soluciones creativas para las limitaciones de la CLI, ofreciendo una experiencia de juego atractiva y rejugable. Es un testimonio de que la creatividad en el desarrollo de juegos no se limita a entornos gráficos complejos, sino que puede prosperar en la simplicidad y el ingenio de la programación en consola.
