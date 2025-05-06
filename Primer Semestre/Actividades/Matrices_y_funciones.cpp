#include <iostream>
using namespace std;

int Sum(int m[][100], int fila, int columna, int n);

int main() {
    int n;
    cout << "Digita el valor del cuadrado de tu matriz: ";
    cin >> n;

    int m[100][100];

    // Entrada de datos
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "Digita el valor de m[" << i << "][" << j << "]: ";
            cin >> m[i][j];
        }
    }

    // Mostrar matriz
    cout << "La matriz es:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << "La suma de los valores de la matriz es: " << Sum(m, 0, 0, n) << endl;

    return 0;
}


int Sum(int m[][100], int fila, int columna, int n) {
    if (fila >= n) return 0;
    if (columna >= n) return Sum(m, fila + 1, 0, n); 
    return m[fila][columna] + Sum(m, fila, columna + 1, n); 
}
