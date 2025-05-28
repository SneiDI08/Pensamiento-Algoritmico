import tkinter as tk
from tkinter import ttk, messagebox
import datetime

# --- Constantes Globales ---
FILAS = 10  # Número de filas en el mapa del parqueadero
COLUMNAS = 10  # Número de columnas en el mapa del parqueadero
CELL_SIZE = 50  # Tamaño de cada celda en píxeles
TARIFA = 100  # Tarifa por minuto (ej. $100 por minuto)
TOTAL_ESPACIOS = 0  # Se calculará dinámicamente en base al mapa

# Definición de colores para los diferentes tipos de celdas
COLORES = {
    'X': '#7f8c8d',  # Caminos (gris oscuro)
    'P': '#2ecc71',  # Espacio de parking disponible (verde)
    'R': '#f1c40f',  # Espacio reservado (amarillo)
    'E': '#3498db',  # Entrada (azul)
    'S': '#e74c3c',  # Salida (rojo)
    'O_optimus': '#9b59b6',  # Vehículo tipo 'optimus' ocupando un espacio (morado)
    'O_bumblebee': '#1abc9c', # Vehículo tipo 'bumblebee' ocupando un espacio (verde azulado)
    'O_megatron': '#e67e22', # Vehículo tipo 'megatron' ocupando un espacio (naranja)
    'E_TEXT': '#3498db', # Color para el texto de entrada
    'S_TEXT': '#e74c3c'  # Color para el texto de salida
}

class ParqueaderoApp:
    def __init__(self, root):
        """
        Inicializa la aplicación del parqueadero.
        Configura la ventana principal, el lienzo, los controles y las estructuras de datos.
        """
        self.root = root
        self.root.title("Sistema de Gestión de Parqueadero")
        self.root.geometry("1200x800") # Tamaño de la ventana principal

        # --- Variables de estado ---
        # self.mapa: Representación de la cuadrícula del parqueadero.
        # 'X': Camino, 'P': Parking, 'R': Reservado, 'O_tipo': Ocupado por tipo de vehículo,
        # 'E': Entrada, 'S': Salida, 'E_TEXT': Texto Entrada, 'S_TEXT': Texto Salida
        self.mapa = []
        self.vehiculos = {}  # Diccionario para almacenar vehículos: {placa: (tipo, fila, columna, hora_entrada)}

        # --- Configuración de la interfaz de usuario ---
        self.setup_ui()
        self.inicializar_mapa() # Inicializa el mapa del parqueadero
        self.dibujar_mapa() # Dibuja el mapa inicial en el lienzo
        self.actualizar_lista_vehiculos() # Carga la lista de vehículos
        self.actualizar_estadisticas() # Carga las estadísticas iniciales
        self.actualizar_reloj() # Inicia el reloj

    def setup_ui(self):
        """Configura los elementos de la interfaz de usuario."""
        # Frame principal para organizar los elementos
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        # --- Sección del Mapa (Izquierda) ---
        map_frame = ttk.LabelFrame(main_frame, text="Mapa del Parqueadero", padding="10")
        map_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5, pady=5)

        self.canvas = tk.Canvas(map_frame, bg="#bdc3c7", width=COLUMNAS * CELL_SIZE, height=FILAS * CELL_SIZE, relief="ridge", bd=2)
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # --- Sección de Controles y Estadísticas (Derecha) ---
        control_frame = ttk.Frame(main_frame, padding="10")
        control_frame.pack(side=tk.RIGHT, fill=tk.Y, padx=5, pady=5)

        # Reloj
        self.reloj_label = ttk.Label(control_frame, text="", font=("Arial", 14, "bold"))
        self.reloj_label.pack(pady=10)

        # Controles de Vehículos
        vehicle_control_frame = ttk.LabelFrame(control_frame, text="Control de Vehículos", padding="10")
        vehicle_control_frame.pack(pady=10, fill=tk.X)

        ttk.Label(vehicle_control_frame, text="Placa:").grid(row=0, column=0, padx=5, pady=5, sticky="w")
        self.placa_entry = ttk.Entry(vehicle_control_frame, width=20)
        self.placa_entry.grid(row=0, column=1, padx=5, pady=5, sticky="ew")

        ttk.Label(vehicle_control_frame, text="Tipo de Vehículo:").grid(row=1, column=0, padx=5, pady=5, sticky="w")
        self.tipo_var = tk.StringVar(value="optimus") # Valor por defecto
        tipo_options = [("Carro", "optimus"), ("Moto", "bumblebee"), ("Otro", "megatron")]
        for i, (text, value) in enumerate(tipo_options):
            ttk.Radiobutton(vehicle_control_frame, text=text, variable=self.tipo_var, value=value).grid(row=1, column=1+i, padx=5, pady=2, sticky="w")

        ttk.Button(vehicle_control_frame, text="Ingresar Vehículo", command=self.ingresar_vehiculo).grid(row=2, column=0, columnspan=2, pady=5, sticky="ew")
        ttk.Button(vehicle_control_frame, text="Retirar Vehículo", command=self.retirar_vehiculo).grid(row=3, column=0, columnspan=2, pady=5, sticky="ew")
        ttk.Button(vehicle_control_frame, text="Reservar Espacio", command=self.reservar_espacio).grid(row=4, column=0, columnspan=2, pady=5, sticky="ew")

        # Estadísticas del Parqueadero
        stats_frame = ttk.LabelFrame(control_frame, text="Estadísticas", padding="10")
        stats_frame.pack(pady=10, fill=tk.X)

        self.stats_labels = {}
        stats_data = {
            "Total de Espacios:": "Totales",
            "Espacios Ocupados:": "Ocupados",
            "Espacios Disponibles:": "Disponibles",
            "Porcentaje de Ocupación:": "Ocupación",
            "Carros Ocupados:": "Carros",
            "Motos Ocupadas:": "Motos",
            "Otros Vehículos Ocupados:": "Otros"
        }
        for i, (label_text, key) in enumerate(stats_data.items()):
            ttk.Label(stats_frame, text=label_text).grid(row=i, column=0, padx=5, pady=2, sticky="w")
            self.stats_labels[key] = ttk.Label(stats_frame, text="0", font=("Arial", 10, "bold"))
            self.stats_labels[key].grid(row=i, column=1, padx=5, pady=2, sticky="e")

        # Lista de Vehículos Estacionados
        list_frame = ttk.LabelFrame(control_frame, text="Vehículos Estacionados / Reservados", padding="10")
        list_frame.pack(pady=10, fill=tk.BOTH, expand=True)

        columns = ("Placa", "Tipo", "Hora Entrada/Reserva")
        self.tree = ttk.Treeview(list_frame, columns=columns, show="headings")
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=100, anchor="center") # Ajustar ancho de columna
        self.tree.pack(fill=tk.BOTH, expand=True)

        # Scrollbar para el Treeview
        scrollbar = ttk.Scrollbar(list_frame, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscrollcommand=scrollbar.set)
        scrollbar.pack(side="right", fill="y")


    def inicializar_mapa(self):
        """
        Inicializa la cuadrícula del mapa del parqueadero.
        Define los caminos, espacios de parking, entrada y salida.
        """
        global TOTAL_ESPACIOS # Acceder a la variable global

        # Crear un mapa vacío con caminos 'X'
        self.mapa = [['X' for _ in range(COLUMNAS)] for _ in range(FILAS)]

        # Definir los espacios de parking 'P'
        parking_spots = [
            (1,1), (1,2), (1,3), (1,4),
            (3,1), (3,2), (3,3), (3,4),
            (5,1), (5,2), (5,3), (5,4),
            (7,1), (7,2), (7,3), (7,4),
            (1,6), (1,7), (1,8), (1,9),
            (3,6), (3,7), (3,8), (3,9),
            (5,6), (5,7), (5,8), (5,9),
            (7,6), (7,7), (7,8), (7,9)
        ]

        for r, c in parking_spots:
            if 0 <= r < FILAS and 0 <= c < COLUMNAS:
                self.mapa[r][c] = 'P'
                TOTAL_ESPACIOS += 1 # Contar los espacios de parking

        # Definir la entrada y salida
        self.mapa[0][0] = 'E' # Entrada
        self.mapa[0][1] = 'E_TEXT' # Texto para entrada
        self.mapa[FILAS-1][COLUMNAS-1] = 'S' # Salida
        self.mapa[FILAS-1][COLUMNAS-2] = 'S_TEXT' # Texto para salida

    def dibujar_mapa(self):
        """
        Dibuja el mapa del parqueadero en el lienzo (canvas).
        Cada celda se dibuja con su color y contenido correspondiente.
        """
        self.canvas.delete("all") # Limpiar el lienzo antes de redibujar

        for i in range(FILAS): # FILAS
            for j in range(COLUMNAS): # COLUMNAS
                x1 = j * CELL_SIZE
                y1 = i * CELL_SIZE
                x2 = x1 + CELL_SIZE
                y2 = y1 + CELL_SIZE
                tipo = self.mapa[i][j]

                # Obtener el color de la celda, por defecto gris oscuro para caminos
                color = COLORES.get(tipo, '#7f8c8d')

                # Colores específicos para tipos de celda que no son 'X'
                if tipo == 'P':
                    color = COLORES['P']
                elif tipo.startswith('O_'): # Vehículo ocupando un espacio (ej. 'O_optimus')
                    color = COLORES[tipo]
                elif tipo == 'R': # Espacio reservado
                    color = COLORES['R']
                elif tipo == 'E': # Entrada
                    color = COLORES['E']
                elif tipo == 'S': # Salida
                    color = COLORES['S']
                elif tipo == 'E_TEXT': # Celda de texto de entrada
                    color = COLORES['E_TEXT']
                elif tipo == 'S_TEXT': # Celda de texto de salida
                    color = COLORES['S_TEXT']

                # Dibujar el rectángulo de la celda
                self.canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline='#34495e', width=1) # Contorno oscuro

                # Dibujar texto de ENTRADA/SALIDA
                if tipo == 'E_TEXT':
                    self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text="ENTRADA", font=("Arial", 10, "bold"), fill='white')
                elif tipo == 'S_TEXT':
                    self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text="SALIDA", font=("Arial", 10, "bold"), fill='white')

                # Mostrar placa e icono si hay vehículo o reserva
                placa_en_celda = None
                tipo_vehiculo_actual = None
                for placa, datos in self.vehiculos.items():
                    v_type, vi, vj, _ = datos
                    if vi == i and vj == j:
                        placa_en_celda = placa
                        tipo_vehiculo_actual = v_type # Obtener el tipo real del vehículo (optimus, bumblebee, megatron, R)
                        break

                if placa_en_celda:
                    display_text = placa_en_celda
                    icon_text = ""
                    if tipo_vehiculo_actual == 'optimus':
                        icon_text = "CARRO"
                    elif tipo_vehiculo_actual == 'bumblebee':
                        icon_text = "MOTO"
                    elif tipo_vehiculo_actual == 'megatron':
                        icon_text = "BUS"
                    elif tipo_vehiculo_actual == 'R': # Si es una reserva
                        icon_text = "RES"
                        display_text = placa_en_celda # Mostrar la placa de la reserva

                    # Centrar el texto y el icono
                    if icon_text and icon_text != "RES": # Si es un vehículo con icono de texto (no una reserva)
                        self.canvas.create_text((x1+x2)//2, y1 + CELL_SIZE/3 + 2, text=icon_text, font=("Arial", 10, "bold"), fill='white') # Ajuste de posición
                        self.canvas.create_text((x1+x2)//2, y1 + 2*CELL_SIZE/3 - 2, text=display_text, font=("Arial", 7, "bold"), fill='white') # Ajuste de posición y tamaño de fuente
                    else: # Si es "RES" o solo la placa (para reservas o casos sin icono específico)
                        self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text=display_text, font=("Arial", 8, "bold"), fill='white') # Ajuste de tamaño de fuente
                elif tipo == 'R' and not placa_en_celda: # Si la celda está marcada como 'R' pero no hay placa asociada (ej. reserva sin placa en vehiculos)
                    self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text="RES", font=("Arial", 8, "bold"), fill='white') # Ajuste de tamaño de fuente


                # Dibujar líneas discontinuas para simular divisiones de parking
                if tipo == 'P' or tipo.startswith('O_') or tipo == 'R':
                    # Líneas horizontales en la parte superior e inferior de los spots
                    self.canvas.create_line(x1, y1, x2, y1, fill='white', dash=(2,2), width=1)
                    self.canvas.create_line(x1, y2, x2, y2, fill='white', dash=(2,2), width=1)
                    # Líneas verticales a los lados de los spots
                    self.canvas.create_line(x1, y1, x1, y2, fill='white', dash=(2,2), width=1)
                    self.canvas.create_line(x2, y1, x2, y2, fill='white', dash=(2,2), width=1)

        self.root.update_idletasks() # Fuerza la actualización del canvas

    def actualizar_lista_vehiculos(self):
        """Actualiza la tabla de vehículos estacionados."""
        for item in self.tree.get_children():
            self.tree.delete(item) # Borra todos los elementos actuales
        for placa, datos in self.vehiculos.items():
            tipo, _, _, hora = datos
            # Asegurarse de que las reservas también se muestren
            display_tipo = "Reservado" if tipo == 'R' else tipo.capitalize().replace('optimus', 'Carro').replace('bumblebee', 'Moto').replace('megatron', 'Otro')
            self.tree.insert('', 'end', values=(placa, display_tipo, hora.strftime("%Y-%m-%d %H:%M:%S")))

    def actualizar_estadisticas(self):
        """Actualiza las etiquetas de estadísticas del parqueadero."""
        ocupados = 0
        carros_ocupados = 0
        motos_ocupadas = 0
        otros_ocupados = 0

        for placa, datos in self.vehiculos.items():
            tipo, _, _, _ = datos
            if tipo != 'R': # Contar solo vehículos que están físicamente en el parqueadero
                ocupados += 1
                if tipo == 'optimus':
                    carros_ocupados += 1
                elif tipo == 'bumblebee':
                    motos_ocupadas += 1
                elif tipo == 'megatron':
                    otros_ocupados += 1

        disponibles = TOTAL_ESPACIOS - ocupados
        # Asegúrate de que TOTAL_ESPACIOS no sea cero para evitar división por cero
        porcentaje = (ocupados / TOTAL_ESPACIOS) * 100 if TOTAL_ESPACIOS > 0 else 0

        self.stats_labels["Totales"].config(text=str(TOTAL_ESPACIOS))
        self.stats_labels["Ocupados"].config(text=str(ocupados))
        self.stats_labels["Disponibles"].config(text=str(disponibles))
        self.stats_labels["Ocupación"].config(text=f"{porcentaje:.1f}%")
        self.stats_labels["Carros"].config(text=str(carros_ocupados))
        self.stats_labels["Motos"].config(text=str(motos_ocupadas))
        self.stats_labels["Otros"].config(text=str(otros_ocupados))

    def actualizar_reloj(self):
        """Actualiza la etiqueta del reloj cada segundo."""
        ahora = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.reloj_label.config(text=ahora)
        self.root.after(1000, self.actualizar_reloj) # Llama a esta función de nuevo después de 1000ms (1 segundo)

    def ingresar_vehiculo(self):
        """Gestiona la entrada de un vehículo al parqueadero."""
        placa = self.placa_entry.get().strip().upper()
        tipo = self.tipo_var.get() # 'optimus', 'bumblebee', 'megatron'

        if not placa:
            messagebox.showwarning("Error", "Debes ingresar una placa.")
            return

        # Verificar si la placa ya está en el parqueadero (ocupando un espacio)
        for p, datos in self.vehiculos.items():
            if p == placa and datos[0] != 'R': # Si ya está y no es solo una reserva
                messagebox.showwarning("Error", "Este vehículo ya está en el parqueadero.")
                return

        espacio_encontrado = False
        # 1. Intentar ocupar una reserva existente para esta placa
        if placa in self.vehiculos and self.vehiculos[placa][0] == 'R':
            _, i, j, _ = self.vehiculos[placa]
            self.mapa[i][j] = f'O_{tipo}' # Ocupar el espacio reservado
            self.vehiculos[placa] = (tipo, i, j, datetime.datetime.now()) # Actualizar datos del vehículo
            espacio_encontrado = True
        else:
            # 2. Si no hay reserva, buscar el primer espacio 'P' libre
            for i in range(FILAS):
                for j in range(COLUMNAS):
                    if self.mapa[i][j] == 'P': # Buscar un espacio de parking libre
                        self.mapa[i][j] = f'O_{tipo}' # Marcar como ocupado
                        self.vehiculos[placa] = (tipo, i, j, datetime.datetime.now())
                        espacio_encontrado = True
                        break
                if espacio_encontrado:
                    break

        if espacio_encontrado:
            self.dibujar_mapa()
            self.actualizar_lista_vehiculos()
            self.actualizar_estadisticas()
            messagebox.showinfo("Éxito", f"Vehículo {placa} ingresado como {tipo.capitalize().replace('optimus', 'Carro').replace('bumblebee', 'Moto').replace('megatron', 'Otro')}.")
        else:
            messagebox.showinfo("Parqueadero Lleno", "No hay espacios disponibles.")

    def retirar_vehiculo(self):
        """Gestiona la salida de un vehículo del parqueadero y calcula el costo."""
        placa = self.placa_entry.get().strip().upper()
        if not placa:
            messagebox.showwarning("Error", "Debes ingresar una placa.")
            return

        # Verificar si la placa está en los vehículos y no es solo una reserva
        if placa not in self.vehiculos or self.vehiculos[placa][0] == 'R':
            messagebox.showwarning("Error", "Vehículo no encontrado en el parqueadero (o es solo una reserva).")
            return

        # Recuperar datos del vehículo
        tipo, i, j, hora_entrada = self.vehiculos.pop(placa)

        # Marcar el espacio como libre 'P' (parking)
        self.mapa[i][j] = 'P'

        # Calcular tiempo y costo
        tiempo_estacionado = datetime.datetime.now() - hora_entrada
        minutos = tiempo_estacionado.total_seconds() / 60
        costo = int(minutos) * TARIFA

        self.dibujar_mapa()
        self.actualizar_lista_vehiculos()
        self.actualizar_estadisticas()
        messagebox.showinfo("Pago de Parqueadero",
                             f"Vehículo: {placa}\n"
                             f"Tiempo estacionado: {int(minutos)} minutos\n"
                             f"Total a pagar: ${costo:,.0f}") # Formato de moneda

    def reservar_espacio(self):
        """Permite reservar un espacio en el parqueadero."""
        placa = self.placa_entry.get().strip().upper()
        if not placa:
            messagebox.showwarning("Error", "Debes ingresar una placa para la reserva.")
            return

        # Verificar si la placa ya tiene una reserva o está ocupando un espacio
        if placa in self.vehiculos:
            messagebox.showwarning("Error", "Este vehículo ya está en el parqueadero o ya tiene una reserva activa.")
            return

        # Buscar el primer espacio 'P' libre para reservar
        espacio_reservado = False
        for i in range(FILAS):
            for j in range(COLUMNAS):
                if self.mapa[i][j] == 'P': # Buscar un espacio de parking libre
                    self.mapa[i][j] = 'R' # Marcar como Reservado
                    # Almacenar la reserva en vehiculos, con un tipo 'R' para identificarla
                    self.vehiculos[placa] = ('R', i, j, datetime.datetime.now())
                    espacio_reservado = True
                    break
            if espacio_reservado:
                break

        if espacio_reservado:
            self.dibujar_mapa()
            self.actualizar_lista_vehiculos() # La lista mostrará la reserva
            self.actualizar_estadisticas()
            messagebox.showinfo("Reserva Exitosa", f"Espacio reservado para la placa {placa}.")
        else:
            messagebox.showinfo("Parqueadero Lleno", "No hay espacios disponibles para reservar.")

# Punto de entrada de la aplicación
if __name__ == "__main__":
    root = tk.Tk()
    app = ParqueaderoApp(root)
    root.mainloop()
