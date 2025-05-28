# Proyecto Papumon Game

## Integrantes del Equipo:
* [Tu Nombre Completo]
* [Nombre Completo del Compañero 1]
* [Nombre Completo del Compañero 2]

---

## 1. Introducción

Bienvenido al proyecto "Papumon Game", un emocionante juego de rol de batallas por turnos implementado en C++ utilizando la interfaz de línea de comandos (CLI). Este juego ofrece a los jugadores la oportunidad de coleccionar, seleccionar y batallar con sus "Papumones" favoritos, criaturas con habilidades únicas y representaciones visuales distintivas en arte ASCII. Diseñado para ser intuitivo y atractivo, "Papumon Game" proporciona una experiencia de juego nostálgica y desafiante directamente desde tu terminal.

## 2. Problema (¿De qué es el programa?)

El programa "Papumon Game" aborda el desafío de crear un juego de rol de batallas por turnos completamente funcional dentro de un entorno de línea de comandos. Esto implica gestionar la lógica del juego, las estadísticas de los personajes, las interacciones del jugador y la representación visual sin el uso de una interfaz gráfica de usuario. El objetivo es ofrecer una experiencia de juego completa y envolvente, superando las limitaciones inherentes a un entorno de texto.

## 3. Explicación del Programa

"Papumon Game" es un juego de batallas por turnos donde los jugadores eligen un equipo de cinco Papumones para enfrentarse a otro jugador o a una Inteligencia Artificial. Cada Papumon tiene sus propias estadísticas (vida, defensa, aguante) y un conjunto de ataques únicos, cada uno con un poder y un costo de aguante asociados.

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

## 4. Explicación de Cosas Usualmente no Vistas

A pesar de ser un juego de consola, hemos implementado características que normalmente se encuentran en interfaces gráficas o juegos más complejos:

* **Representación Visual Dinámica con Arte ASCII:** A diferencia de muchos programas de consola que solo usan texto plano para la información, "Papumon Game" muestra un arte ASCII detallado para cada Papumon en la pantalla de batalla. Este arte ASCII no es estático; se carga dinámicamente para cada Papumon, dándoles una personalidad visual única en el campo de batalla. Esto se logra almacenando el arte ASCII como un `std::vector<std::string>` dentro de la clase `papumon` y renderizándolo línea por línea con offsets calculados para centrarlo y alinearlo en la interfaz.

* **Barras de Salud Visuales:** En lugar de simplemente mostrar un número de puntos de vida, el juego presenta barras de salud progresivas (`[#####-----]`) que visualizan el estado de la vida de cada Papumon. Esto mejora la legibilidad y la inmersión del jugador, permitiendo una rápida evaluación de la situación de la batalla. La longitud de la barra llena se calcula proporcionalmente a la vida actual y máxima del Papumon.

* **Gestión de Recursos con "Aguante":** Más allá de solo puntos de vida, hemos introducido un sistema de "aguante" como recurso para los ataques. Cada ataque tiene un costo de aguante, y los Papumones deben gestionar este recurso sabiamente. Además, los jugadores pueden elegir una acción de "curar aguante" en su turno, añadiendo una capa estratégica a la gestión de recursos que va más allá del simple ataque/defensa.

* **Reutilización de Objetos Papumon para Batallas:** En lugar de crear nuevas instancias de Papumones para cada batalla, se trabaja directamente con referencias a los objetos `papumon` existentes en los vectores de equipo (`vector<papumon>&`). Esto permite que los cambios de vida y aguante persistan a lo largo de los turnos de batalla, incluso cuando un Papumon es derrotado y se pasa al siguiente, manteniendo la coherencia del estado del juego.

## 5. Justificación de la IA

La implementación de una Inteligencia Artificial en "Papumon Game" se justifica por varias razones clave:

* **Rejugabilidad y Accesibilidad:** Una IA proporciona un oponente constante y disponible, lo que permite a los jugadores disfrutar del juego en solitario sin depender de la disponibilidad de un segundo jugador. Esto aumenta significativamente la rejugabilidad y la accesibilidad del juego.

* **Curva de Aprendizaje y Práctica:** La IA sirve como un excelente compañero de entrenamiento para los nuevos jugadores, permitiéndoles familiarizarse con la mecánica del juego, los ataques y la gestión de Papumones antes de enfrentarse a un oponente humano.

* **Variedad de Experiencia de Juego:** Al ofrecer tanto un modo de jugador contra jugador como un modo de jugador contra IA, el juego presenta diferentes tipos de desafíos. La IA, aunque con una lógica sencilla, introduce un elemento de imprevisibilidad en la batalla.

* **Demostración de Habilidades de Programación:** La implementación de una IA, incluso una básica, demuestra la capacidad de diseñar y programar lógica de comportamiento para entidades no controladas por el usuario, un componente fundamental en el desarrollo de juegos. La IA actual prioriza curar aguante si está bajo y, de lo contrario, elige un ataque aleatorio que pueda usar, lo que le da un comportamiento reactivo y estratégico básico.

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
