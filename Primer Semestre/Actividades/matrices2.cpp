#include <iostream>
using namespace std;

int main() {
    int n, a = 1;
    int m[100][100] = {}, r[100][100] = {};

    cout << "Vamos a crear una matriz cuadrada y rotarla 90 grados a la derecha" << endl;
    cout << "Ingresa un numero para crear una matriz cuadrada: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = a;
            a++;
        }
    }

    cout << "Matriz original: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << "\t";
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[j][n - 1 - i] = m[i][j];
        }
    }

    cout << "Matriz rotada 90 grados a la derecha: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << r[i][j] << "\t";
        cout << endl;
    }

    return 0;
}
