# Pensamiento Algorítmico - Proyectiles en Aetheria (Juego de Batalla de Papumones)

## Integrantes:
* Dady Sneider Loaiza Loaiza
* Kamila Guzman

---

## Desarrollos Innovadores

### Proyecto C++ (Juego de Batalla de Papumones)

Este proyecto representa un juego de batalla por turnos donde los jugadores seleccionan un equipo de "Papumones" para enfrentarse. Se han implementado las siguientes características y desarrollos innovadores:

* **Sistema de Clases Modularizado:**
    * **¿Para qué se implementó?** Para organizar la lógica del juego de manera limpia y reutilizable, separando las definiciones de las entidades del juego (`ataque` y `papumon`) en archivos de cabecera (`.h`) y su implementación en archivos de código fuente (`.cpp`). Esto promueve la modularidad y facilita el mantenimiento y la escalabilidad del código.
    * **¿Por qué se consideró necesario?** En un juego, hay múltiples entidades con propiedades y comportamientos. Agrupar estas propiedades en clases hace que el código sea más legible y manejable que usar variables globales o estructuras simples para cada entidad.
    * **¿Cómo se llevó a cabo su implementación?** Se crearon dos clases principales: `ataque` (con propiedades como nombre, poder y uso) y `papumon` (con nombre, tipo, vida, defensa, aguante y un vector de `ataques`). Se usaron constructores para inicializar sus propiedades.

* **Gestión de Colecciones de Objetos (Papumones y Ataques):**
    * **¿Para qué se implementó?** Para gestionar eficientemente las listas de ataques predefinidos por tipo (fuego, agua, tierra, viento, normal) y la lista de todos los Papumones disponibles en el juego. Esto permite un acceso fácil y organizado a las diferentes criaturas y sus habilidades.
    * **¿Por qué se consideró necesario?** Un juego de este tipo requiere un catálogo de personajes y sus movimientos. Utilizar `std::vector` de objetos de clase es una forma estándar y eficiente de manejar estas colecciones dinámicas.
    * **¿Cómo se llevó a cabo su implementación?** Se crearon funciones que retornan `std::vector<ataque>` (ej. `ataques_fuego()`) y `std::vector<papumon>` (`papumones()`). Estas funciones se encargan de inicializar y devolver colecciones de objetos con sus datos preestablecidos, permitiendo que la lógica del juego acceda a ellos de manera centralizada.

* **Sistema de Menús Interactivo y Robusto:**
    * **¿Para qué se implementó?** Para guiar al usuario a través de las diferentes fases del juego: menú principal, selección de equipo y la batalla. Incluye validación de entrada para mejorar la experiencia del usuario y evitar fallos del programa.
    * **¿Por qué se consideró necesario?** Una interfaz de usuario clara y con validación de entrada es crucial para cualquier aplicación interactiva. Evita que el programa se cuelgue debido a entradas inesperadas (ej. texto en lugar de números).
    * **¿Cómo se llevó a cabo su implementación?** Se definieron funciones separadas para cada menú (`menu_principal`, `menu_seleccion`, `menu_batalla`). Se utilizó `cin.fail()` y `cin.clear()` junto con `cin.ignore()` para manejar entradas inválidas, solicitando al usuario que reintente. El bucle `do-while` en `menu_principal` asegura que el juego se mantenga activo hasta que el usuario decida salir, y en `menu_seleccion`, se asegura que se elijan 5 Papumones antes de proceder.

* **Lógica de Batalla por Turnos con Gestión de Recursos (Vida y Aguante):**
    * **¿Para qué se implementó?** Para simular una batalla estratégica entre dos equipos de Papumones, gestionando la vida, el aguante (puntos de acción para ataques) y los turnos de los jugadores. Incorpora cálculo de daño y la posibilidad de curar aguante.
    * **¿Por qué se consideró necesario?** El corazón de un juego de combate es su sistema de batalla. La gestión de recursos como vida y aguante añade profundidad estratégica, obligando al jugador a tomar decisiones sobre cuándo atacar o recuperar.
    * **¿Cómo se llevó a cabo su implementación?** La función `menu_batalla` maneja el flujo de la pelea. Se alternan los turnos entre `equipo1` y `equipo2`. Cada Papumon tiene `vida` y `aguante`. Los ataques consumen `aguante` y causan `daño` al `defensor` (calculado como `poder - defensa`). Se incluyó una opción para curar aguante, con un límite para evitar que se abuse de esta mecánica. La batalla termina cuando un equipo se queda sin Papumones. Se usa `max(0, ...)` para evitar valores negativos en vida y daño, y `min(atacante.aguante, 50)` para limitar la curación de aguante.
