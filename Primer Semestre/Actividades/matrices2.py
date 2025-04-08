print ("Rotación de una matriz 90° en sentido horario")
matrix = []
n = int(input())
for i in range(n):
    matrix.append(list(map(int, input().split())))

rotada = [[0] * n for _ in range(n)]

for i in range(n):
    for j in range(n):
        rotada[j][n - 1 - i] = matrix[i][j]

for r in rotada:
    print(r)
