import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import datetime

FILAS = 10
COLUMNAS = 10
CELL_SIZE = 50
TOTAL_ESPACIOS = 0  
TARIFAS_POR_MINUTO = {
    'carro': 150,
    'moto': 100,
    'bus': 200
}
HORAS_PICO = [
    (7, 0, 9, 0),
    (17, 0, 19, 0)
]
TARIFA_ADICIONAL_PICO = 50 
TIEMPO_GRACIA_RESERVA_MINUTOS = 3 
TIEMPO_GRACIA_ESTACIONAMIENTO_MINUTOS = 3 

COLORES = {
    'X': '#7f8c8d', 
    'P': '#2ecc71', 
    'R': '#f1c40f',
    'E': '#3498db',
    'S': '#e74c3c',
    'O_carro': '#9b59b6',
    'O_moto': '#1abc9c',
    'O_bus': '#e67e22',
    'E_TEXT': '#3498db',
    'S_TEXT': '#e74c3c'
}

class ParqueaderoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Sistema de Gestión de Parqueadero")
        self.root.geometry("1200x800") 

        self.mapa = []
        self.vehiculos = {}

        self.setup_ui()
        self.inicializar_mapa() 
        self.dibujar_mapa() 
        self.actualizar_lista_vehiculos() 
        self.actualizar_estadisticas() 
        self.actualizar_reloj() 
        self.verificar_reservas_expiradas() 

    def setup_ui(self):
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        map_frame = ttk.LabelFrame(main_frame, text="Mapa del Parqueadero", padding="10")
        map_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5, pady=5)

        self.canvas = tk.Canvas(map_frame, bg="#bdc3c7", width=COLUMNAS * CELL_SIZE, height=FILAS * CELL_SIZE, relief="ridge", bd=2)
        self.canvas.pack(fill=tk.BOTH, expand=True)

        control_frame = ttk.Frame(main_frame, padding="10")
        control_frame.pack(side=tk.RIGHT, fill=tk.Y, padx=5, pady=5)

        self.reloj_label = ttk.Label(control_frame, text="", font=("Arial", 14, "bold"))
        self.reloj_label.pack(pady=10)

        vehicle_control_frame = ttk.LabelFrame(control_frame, text="Control de Vehículos", padding="10")
        vehicle_control_frame.pack(pady=10, fill=tk.X)

        ttk.Label(vehicle_control_frame, text="Placa:").grid(row=0, column=0, padx=5, pady=5, sticky="w")
        self.placa_entry = ttk.Entry(vehicle_control_frame, width=20)
        self.placa_entry.grid(row=0, column=1, padx=5, pady=5, sticky="ew")

        ttk.Label(vehicle_control_frame, text="Tipo de Vehículo:").grid(row=1, column=0, padx=5, pady=5, sticky="w")
        self.tipo_var = tk.StringVar(value="carro") # Default value
        tipo_options = [("Carro", "carro"), ("Moto", "moto"), ("Bus", "bus")]
        for i, (text, value) in enumerate(tipo_options):
            ttk.Radiobutton(vehicle_control_frame, text=text, variable=self.tipo_var, value=value).grid(row=1, column=1+i, padx=5, pady=2, sticky="w")

        ttk.Button(vehicle_control_frame, text="Ingresar Vehículo", command=self.ingresar_vehiculo).grid(row=2, column=0, columnspan=3, pady=5, sticky="ew")
        ttk.Button(vehicle_control_frame, text="Retirar Vehículo", command=self.retirar_vehiculo).grid(row=3, column=0, columnspan=3, pady=5, sticky="ew")
        ttk.Button(vehicle_control_frame, text="Reservar Espacio", command=self.reservar_espacio_ui).grid(row=4, column=0, columnspan=3, pady=5, sticky="ew")

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
            "Buses Ocupados:": "Buses"
        }
        for i, (label_text, key) in enumerate(stats_data.items()):
            ttk.Label(stats_frame, text=label_text).grid(row=i, column=0, padx=5, pady=2, sticky="w")
            self.stats_labels[key] = ttk.Label(stats_frame, text="0", font=("Arial", 10, "bold"))
            self.stats_labels[key].grid(row=i, column=1, padx=5, pady=2, sticky="e")

        # lista de vehiculos reservados
        list_frame = ttk.LabelFrame(control_frame, text="Vehículos Estacionados / Reservados", padding="10")
        list_frame.pack(pady=10, fill=tk.BOTH, expand=True)

        columns = ("Placa", "Tipo", "Hora Entrada/Reserva")
        self.tree = ttk.Treeview(list_frame, columns=columns, show="headings")
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=100, anchor="center")
        self.tree.pack(fill=tk.BOTH, expand=True)

        scrollbar = ttk.Scrollbar(list_frame, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscrollcommand=scrollbar.set)
        scrollbar.pack(side="right", fill="y")

    def inicializar_mapa(self):
        
        global TOTAL_ESPACIOS
        TOTAL_ESPACIOS = 0

        self.mapa = [['X' for _ in range(COLUMNAS)] for _ in range(FILAS)]

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
                TOTAL_ESPACIOS += 1

        self.mapa[0][0] = 'E' 
        self.mapa[0][1] = 'E_TEXT' 
        self.mapa[FILAS-1][COLUMNAS-1] = 'S' 
        self.mapa[FILAS-1][COLUMNAS-2] = 'S_TEXT' 

    def dibujar_mapa(self):
        """
        Dibuja el mapa de aparcamiento en el lienzo.
        Cada celda se dibuja con su correspondiente color y contenido.
        """
        self.canvas.delete("all")

        for i in range(FILAS):
            for j in range(COLUMNAS):
                x1 = j * CELL_SIZE
                y1 = i * CELL_SIZE
                x2 = x1 + CELL_SIZE
                y2 = y1 + CELL_SIZE
                tipo_celda = self.mapa[i][j]

                color = COLORES.get(tipo_celda, '#7f8c8d')

                if tipo_celda == 'P':
                    color = COLORES['P']
                elif tipo_celda.startswith('O_'): 
                    color = COLORES[tipo_celda]
                elif tipo_celda == 'R':
                    color = COLORES['R']
                elif tipo_celda == 'E':
                    color = COLORES['E']
                elif tipo_celda == 'S':
                    color = COLORES['S']
                elif tipo_celda == 'E_TEXT': 
                    color = COLORES['E_TEXT']
                elif tipo_celda == 'S_TEXT': 
                    color = COLORES['S_TEXT']

                self.canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline='#34495e', width=1) # Dark outline

                # Dibuja la entrada y salida de texto
                if tipo_celda == 'E_TEXT':
                    self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text="ENTRADA", font=("Arial", 10, "bold"), fill='white')
                elif tipo_celda == 'S_TEXT':
                    self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text="SALIDA", font=("Arial", 10, "bold"), fill='white')

                # Visualizar la matrícula y el icono si hay un vehículo o una reserva
                placa_en_celda = None
                tipo_vehiculo_actual = None
                for placa, datos in self.vehiculos.items():
                    v_type, vi, vj, _ = datos
                    if vi == i and vj == j:
                        placa_en_celda = placa
                        tipo_vehiculo_actual = v_type # Obtener el tipo de vehículo real (carro, moto, bus, R)
                        break

                if placa_en_celda:
                    display_text = placa_en_celda
                    icon_text = ""
                    if tipo_vehiculo_actual == 'carro':
                        icon_text = "CARRO"
                    elif tipo_vehiculo_actual == 'moto':
                        icon_text = "MOTO"
                    elif tipo_vehiculo_actual == 'bus':
                        icon_text = "BUS"
                    elif tipo_vehiculo_actual == 'R': 
                        icon_text = "RES"
                        display_text = placa_en_celda 
                    
                    if icon_text and icon_text != "RES": 
                        self.canvas.create_text((x1+x2)//2, y1 + CELL_SIZE/3 + 2, text=icon_text, font=("Arial", 10, "bold"), fill='white') 
                        self.canvas.create_text((x1+x2)//2, y1 + 2*CELL_SIZE/3 - 2, text=display_text, font=("Arial", 7, "bold"), fill='white') 
                    else: 
                        self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text=display_text, font=("Arial", 8, "bold"), fill='white') 
                elif tipo_celda == 'R' and not placa_en_celda: 
                    self.canvas.create_text((x1+x2)//2, (y1+y2)//2, text="RES", font=("Arial", 8, "bold"), fill='white') 

                
                if tipo_celda == 'P' or tipo_celda.startswith('O_') or tipo_celda == 'R':
                    
                    self.canvas.create_line(x1, y1, x2, y1, fill='white', dash=(2,2), width=1)
                    self.canvas.create_line(x1, y2, x2, y2, fill='white', dash=(2,2), width=1)
                    
                    self.canvas.create_line(x1, y1, x1, y2, fill='white', dash=(2,2), width=1)
                    self.canvas.create_line(x2, y1, x2, y2, fill='white', dash=(2,2), width=1)

        self.root.update_idletasks() 

    def actualizar_lista_vehiculos(self):
        """Actualiza la tabla de vehículos estacionados."""
        for item in self.tree.get_children():
            self.tree.delete(item) 
        for placa, datos in self.vehiculos.items():
            tipo, _, _, hora = datos
            
            display_tipo = "Reservado" if tipo == 'R' else tipo.capitalize()
            self.tree.insert('', 'end', values=(placa, display_tipo, hora.strftime("%Y-%m-%d %H:%M:%S")))

    def actualizar_estadisticas(self):
        ocupados = 0
        carros_ocupados = 0
        motos_ocupadas = 0
        buses_ocupados = 0
        reservados = 0

        for placa, datos in self.vehiculos.items():
            tipo, _, _, _ = datos
            if tipo == 'R': 
                reservados += 1
            else: 
                ocupados += 1
                if tipo == 'carro':
                    carros_ocupados += 1
                elif tipo == 'moto':
                    motos_ocupadas += 1
                elif tipo == 'bus':
                    buses_ocupados += 1

        total_ocupados_y_reservados = ocupados + reservados
        disponibles = TOTAL_ESPACIOS - total_ocupados_y_reservados

        porcentaje = (total_ocupados_y_reservados / TOTAL_ESPACIOS) * 100 if TOTAL_ESPACIOS > 0 else 0

        self.stats_labels["Totales"].config(text=str(TOTAL_ESPACIOS))
        self.stats_labels["Ocupados"].config(text=f"{ocupados} (Reservados: {reservados})")
        self.stats_labels["Disponibles"].config(text=str(disponibles))
        self.stats_labels["Ocupación"].config(text=f"{porcentaje:.1f}%")
        self.stats_labels["Carros"].config(text=str(carros_ocupados))
        self.stats_labels["Motos"].config(text=str(motos_ocupadas))
        self.stats_labels["Buses"].config(text=str(buses_ocupados))

    def actualizar_reloj(self):
        ahora = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.reloj_label.config(text=ahora)
        self.root.after(1000, self.actualizar_reloj) 

    def es_hora_pico(self, hora_actual):

        for h_inicio, m_inicio, h_fin, m_fin in HORAS_PICO:
            inicio_pico = hora_actual.replace(hour=h_inicio, minute=m_inicio, second=0, microsecond=0)
            fin_pico = hora_actual.replace(hour=h_fin, minute=m_fin, second=0, microsecond=0)
            if inicio_pico <= hora_actual <= fin_pico:
                return True
        return False

    def calcular_costo(self, tipo_vehiculo, tiempo_estacionado_minutos, hora_entrada):
        

        tiempo_a_cobrar_minutos = max(0, tiempo_estacionado_minutos - TIEMPO_GRACIA_ESTACIONAMIENTO_MINUTOS)

        tarifa_base_por_minuto = TARIFAS_POR_MINUTO.get(tipo_vehiculo, 0)
        costo_total = 0

        for i in range(int(tiempo_a_cobrar_minutos)):

            minuto_real_cobrado = hora_entrada + datetime.timedelta(minutes=TIEMPO_GRACIA_ESTACIONAMIENTO_MINUTOS + i)
            
            costo_minuto = tarifa_base_por_minuto
            if self.es_hora_pico(minuto_real_cobrado):
                costo_minuto += TARIFA_ADICIONAL_PICO
            costo_total += costo_minuto
        return costo_total

    def ingresar_vehiculo(self):
        placa = self.placa_entry.get().strip().upper()
        tipo = self.tipo_var.get() # 'carro', 'moto', 'bus'

        if not placa:
            messagebox.showwarning("Error", "Debes ingresar una placa.")
            return

        for p, datos in self.vehiculos.items():
            if p == placa and datos[0] != 'R': 
                messagebox.showwarning("Error", "Este vehículo ya está en el parqueadero.")
                return

        espacio_encontrado = False
        
        if placa in self.vehiculos and self.vehiculos[placa][0] == 'R':
            
            del self.vehiculos[placa]
            
            _, i, j, _ = self.vehiculos[placa] 
            res_tipo, res_i, res_j, res_hora = self.vehiculos[placa]
            del self.vehiculos[placa]

            self.mapa[res_i][res_j] = f'O_{tipo}' 
            self.vehiculos[placa] = (tipo, res_i, res_j, datetime.datetime.now()) 
            espacio_encontrado = True
        else:
            
            for i in range(FILAS):
                for j in range(COLUMNAS):
                    if self.mapa[i][j] == 'P': 
                        self.mapa[i][j] = f'O_{tipo}' 
                        self.vehiculos[placa] = (tipo, i, j, datetime.datetime.now())
                        espacio_encontrado = True
                        break
                if espacio_encontrado:
                    break

        if espacio_encontrado:
            self.dibujar_mapa()
            self.actualizar_lista_vehiculos()
            self.actualizar_estadisticas()
            messagebox.showinfo("Éxito", f"Vehículo {placa} ingresado como {tipo.capitalize()}.")
        else:
            messagebox.showinfo("Parqueadero Lleno", "No hay espacios disponibles.")

    def retirar_vehiculo(self):
        """Gestiona la salida de vehículos del aparcamiento y calcula el coste."""
        placa = self.placa_entry.get().strip().upper()
        if not placa:
            messagebox.showwarning("Error", "Debes ingresar una placa.")
            return

        if placa not in self.vehiculos or self.vehiculos[placa][0] == 'R':
            messagebox.showwarning("Error", "Vehículo no encontrado en el parqueadero (o es solo una reserva).")
            return

        tipo, i, j, hora_entrada = self.vehiculos.pop(placa)

        self.mapa[i][j] = 'P'

        # Calcula el costo del tiempo
        tiempo_estacionado = datetime.datetime.now() - hora_entrada
        minutos = tiempo_estacionado.total_seconds() / 60
        
        costo = self.calcular_costo(tipo, minutos, hora_entrada)

        self.dibujar_mapa()
        self.actualizar_lista_vehiculos()
        self.actualizar_estadisticas()
        messagebox.showinfo("Pago de Parqueadero",
                             f"Vehículo: {placa}\n"
                             f"Tiempo estacionado: {int(minutos)} minutos\n"
                             f"Total a pagar: ${costo:,.0f}") # Currency format

    def reservar_espacio_ui(self):
        """
        Solicita al usuario la fila y la columna para reservar un espacio específico.
        Esta función se llama desde el botón UI.
        """
        placa = self.placa_entry.get().strip().upper()
 

        if not placa:
            messagebox.showwarning("Error", "Ingrese la placa del vehículo para la reserva.")
            return

        if placa in self.vehiculos:
            messagebox.showwarning("Error", "Este vehículo ya está en el parqueadero o ya tiene una reserva activa.")
            return

        try:
            fila = simpledialog.askinteger("Fila", f"Ingrese fila para reservar (0-{FILAS-1}):", parent=self.root, minvalue=0, maxvalue=FILAS-1)
            if fila is None: 
                return
            columna = simpledialog.askinteger("Columna", f"Ingrese columna para reservar (0-{COLUMNAS-1}):", parent=self.root, minvalue=0, maxvalue=COLUMNAS-1)
            if columna is None: 
                return
        except Exception as e:
            messagebox.showwarning("Error", f"Entrada de fila/columna inválida: {e}")
            return

        if not (0 <= fila < FILAS and 0 <= columna < COLUMNAS):
            messagebox.showwarning("Error", "Fila y columna fuera de rango.")
            return

        self._reservar_espacio(placa, fila, columna)

    def _reservar_espacio(self, placa, fila, columna):
        """
        Lógica interna para reservar un espacio específico.
        Asume que placa, fila y columna ya están validadas.
        """
        if self.mapa[fila][columna] == 'P': 
            self.mapa[fila][columna] = 'R' 
            self.vehiculos[placa] = ('R', fila, columna, datetime.datetime.now())
            self.dibujar_mapa()
            self.actualizar_lista_vehiculos() 
            self.actualizar_estadisticas()
            messagebox.showinfo("Reserva Exitosa", f"Espacio reservado para la placa {placa} en ({fila}, {columna}). Tendrá {TIEMPO_GRACIA_RESERVA_MINUTOS} minutos para ingresar.")
        else:
            messagebox.showerror("Error", "El espacio seleccionado ya está ocupado o no es un espacio de parking válido.")

    def verificar_reservas_expiradas(self):
        """
        Comprueba si hay reservas caducadas y libera los espacios.
        Esta función se llama periódicamente.
        """
        reservas_a_eliminar = []
        ahora = datetime.datetime.now()

        for placa, datos in list(self.vehiculos.items()): 
            tipo, fila, columna, hora_reserva = datos
            if tipo == 'R':
                tiempo_transcurrido = ahora - hora_reserva
                if tiempo_transcurrido.total_seconds() / 60 > TIEMPO_GRACIA_RESERVA_MINUTOS:
                    reservas_a_eliminar.append(placa)
                    if self.mapa[fila][columna] == 'R':
                        self.mapa[fila][columna] = 'P'
                    messagebox.showinfo("Reserva Expirada", f"La reserva para la placa {placa} en ({fila}, {columna}) ha expirado.")

        for placa in reservas_a_eliminar:
            del self.vehiculos[placa]

        if reservas_a_eliminar:
            self.dibujar_mapa()
            self.actualizar_lista_vehiculos()
            self.actualizar_estadisticas()

        self.root.after(5000, self.verificar_reservas_expiradas)

if __name__ == "__main__":
    root = tk.Tk()
    app = ParqueaderoApp(root)
    root.mainloop()
