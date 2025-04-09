#include <iostream>
using namespace std;

int main() {
    int n, a = 1;
    int matriz  [100][100];

    cout << "Ingrese el tamaño de la matriz: ";
    cin >> n;
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = a;
            a++;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << "La suma de la matriz es: ";

    int suma = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            suma += matriz[i][j];
        }
    }
    cout << suma << endl;
    return 0;
}
