# Proyecto LOIHER PARKING Game

## Integrantes del Equipo: 
* Dady Sneider Loaiza Loaiza
* David Hernandez Leyton 

---

## 1. Introducción

Bienvenido al proyecto "gestion de parqueaderos", en este proyecto se realizo un sistema de organizacion de parqueo segun llegada y tipo de vehiculo con este sistema se desea tambien poder calcular el valor segun tiempo y todo dependiendo de si es hora pico o no. 

## 2. Problema (¿De qué es el programa?)
El programa es un **sistema de gestión de parqueaderos** que simula las operaciones básicas de un estacionamiento real, diseñado en **Python**. Su objetivo es administrar la entrada, salida y estadía de vehículos mediante un **mapa visual** (mínimo 8x8) que muestra vías de acceso, entrada/salida y espacios accesibles. Registra la **placa** y **hora de entrada** de cada vehículo, calcula tarifas según el tiempo de permanencia y actualiza en tiempo real la disponibilidad de espacios (libres `[L]`/ocupados `[O]`). El sistema resuelve problemas como la gestión manual de registros, el cálculo impreciso de cobros y la falta de visibilidad de espacios disponibles. Ejemplo: un vehículo con placa `ABC123` ingresa, el mapa se actualiza, y al salir se calcula el pago (ej: 2 horas × $3.000/h = $6.000). Requisitos mínimos incluyen generación del mapa, rutas accesibles, registro de datos y cobro automático. Posibles mejoras: base de datos, interfaz gráfica (Tkinter) o sistema de reservas. 

## 3. Explicación del Programa

Este sistema de registro de vehiculos es un gran reto personal de autocrecimiento, este sistema fue desarrollado en Python con interfaz gráfica (Tkinter) que permite administrar la entrada, salida y reserva de vehículos en un estacionamiento.

El flujo principal del juego es el siguiente:
1.  **Mapeo del parueadero:** sencillamente es la parte visual para ver las rutas de salida y los espacios de parqueo libres o si ya estan ocupados.
2.  **Tipos de vehiculos:** Solo hay registro de tres tipos de vehiculos y cada vehiculo tiene una tarifa personalizada   
3.  **Calculo de tarifas:** esta funcion ayuda a calcular la tarifa por tiempo de cada tipo de vehiculo, adicionalmente en esta funcion tenemos un adicional que es un incremento cuando es hora pico.

## 4. Explicación de Cosas Usualmente no Vistas

A pesar de ser un sistema que visualmente se ve basico, se implementaron funciones adicionales a los aspectos basicos del documento base, esos son:

* **Poder reservar un espacio:** en el sistema se creo una funcion adicional a la de registar entrada y salida de vehiculos, eesa funcion es poder reservar un espacio para un tipo en especifico de vehiculo. En este se tiene que registrar la entrada del vehiculo y asi se libera ese espacio. La decicion del por qué implementarla, es que mucha gente desea llegar a un lugar publico como un centro comercial, pero en fechas importantes como el dia de la madre se desea contar con un lugar en el parqueadero y no dar vueltas y vueltas hasta contar con suerte, por eso se puede reservar con tiempo y no batallar con ese problema.

* **Espera de 3 minutos:** gracias a la funcion de reservacion, se genero una necesidad, de llegar en menos de 3 minutos para que el el espacio ya reservado se mantenga para esa persona, despues de pasados lo 3 minutos el espacio quedara libre, ya sea para un vehiculo en llegada o una reserva nueva.

* **La hora pico:** aqui las horas pico son tomadas en cuenta gracias a que es hora donde mucha gente en sus vehiculos estan saliendo de sus trabajos, universidades, etc. y tienen su transporte y lo desean sacar a asa hora se les cobrara una tarifa diferente a una comun. Esta funcio se implemento gracias a estudio del mercado actual en zonas empresariales como conecta (Bogotá), zona franca (Bogotá), zona industrial montevideo (Bogotá), etc. parqueaderos que estan en los espacios cerca a las zonas ya mencionadas generan mas ganancias a esas horas que en un horario de tipo 3pm, gracias a que las personas entrar a trabajan tipo 7 y salen a las 6.

* **Parqueo gratis:** esta funcion es sencilla, cuando registras que entraste al parqueadero a una hora en especifico y a los tres minutos o menos, registras tu salida, el tiempo en el parqueadero es gratis. Esto se penso para aquellas personas que tienen que recoger familiares en lugares como el aeropuerto o terminal de trasnporte y su vehiculo solo se demoro 3 minutos en el parqeuadero, seria injusto tener que pagar por algo tan insignificante.

---
## 5. Conclusión

## **Implementación Exitosa**
El sistema desarrollado cumple integralmente con los objetivos planteados inicialmente, superando los requisitos mínimos mediante:

- Un **mapa visual interactivo** de 10x10 celdas que muestra en tiempo real la disponibilidad de espacios, vías de circulación y zonas especiales (entrada/salida)
- Un **sistema de registro automatizado** que captura placa, tipo de vehículo y timestamp de ingreso
- **Cálculo dinámico de tarifas** considerando:  
  ✓ Diferenciación por tipo de vehículo (carro/moto/bus)  
  ✓ Horas pico con recargo automático  
  ✓ Periodo de gracia antes de iniciar cobro  

## **Valor Añadido**
El proyecto incorporó características avanzadas no solicitadas inicialmente:

```python
# Sistema de reservas con expiración automática
def verificar_reservas_expiradas(self):
    ahora = datetime.datetime.now()
    if (ahora - hora_reserva).total_seconds()/60 > TIEMPO_GRACIA:
        liberar_espacio()
```
Este proyecto demuestra que con herramientas básicas (Python + Tkinter) pueden desarrollarse sistemas operacionales completos. La solución no solo cumple con los requisitos académicos, sino que establece las bases para una aplicación real con:

* Precisión en gestión de espacios

* Transparencia en cálculo de tarifas
  
* Flexibilidad para adaptarse a necesidades futuras
