pedidos = []
n = int(input("Cuantos productos vas a llevar: "))
a1=0
b1=0
c1=0
for i in range (n):
    u = []
    a = input("Escribe tu nombre: ")
    b = float(input("Valor total del pedido: "))
    c = int(input("Seleccione: 1) en proceso. 2) Eviado. 3) Cancelado.:"))
    while (c < 1 or c > 3):
        c = int(input("Seleccione: 1) en proceso. 2) Eviado. 3) Cancelado.:"))
    if c == 1:
        a1+= 1
    elif c == 2:
        b1 += 1
        c1 += b
    u.append(a)
    u.append(b)
    u.append(c)
    pedidos.append(u)

print (pedidos)

print (f"total pedidos procesados: {a1}")
print (f"total pedidos enviados: {b1}")
print (f"monto total en ventas: {c1}")

if a1 >= n * 0.7:
    print("Alerta, muchos pedidos sin procesar")

