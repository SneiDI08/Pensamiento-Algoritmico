#include <iostream>
using namespace std;
int main() {
    int matriz_coordenadas[100][3]; 
    int caras[100][10]; 
    int a = 0, b = 0, al = 0;
    int opcion;
    while (true) {
        cout << "\n############################\n";
        cout << "#####        MENÚ      #####\n";
        cout << "############################\n";
        cout << "1. Ingresar vértices\n";
        cout << "2. Ingresar caras\n";
        cout << "3. Mostrar matrices\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        if (opcion == 1) {
            cout << "\nCuántos vértices quieres no puedes pasarte de los 100: ";
            cin >> a;
            al = a;
            cout << "\n################################\n";
            cout << "##### Ingrese las coordenadas #####\n";
            cout << "################################\n\n";
            for (int i = 0; i < a; i++) {
                cout << "Vértice " << i + 1 << "\n";
                cout << "Ingrese x: "; cin >> matriz_coordenadas[i][0];
                cout << "Ingrese y: "; cin >> matriz_coordenadas[i][1];
                cout << "Ingrese z: "; cin >> matriz_coordenadas[i][2];
            }
        }
        else if (opcion == 2) {
            if (al < 3) {
                cout << "\nPrimero debes ingresar los vértices, al menos 3." << endl;
            } else {
                cout << "¿Cuántas caras quieres conectar?: ";
                cin >> b;
                while (b > a) {
                    cout << "Error: No puedes tener más caras que vértices." << endl;
                    cin >> b;
                }
                cout << "\n################################\n";
                cout << "##### Ingrese las caras #####\n";
                cout << "################################\n\n";
                for (int i = 0; i < b; i++) {
                    int c;
                    cout << "Cara " << i + 1 << "\n";
                    cout << "¿Cuántos vértices tiene la cara?: ";
                    cin >> c;
                    while (c < 3 || c > a) {
                        cout << "Error: Una cara debe tener al menos 3 vértices y no puede exceder los existentes." << endl;
                        cin >> c;
                    }
                    for (int j = 0; j < c; j++) {
                        cout << "Ingrese el índice del vértice " << j + 1 << " para la cara (1 - " << a << "): ";
                        cin >> caras[i][j];
                        while (caras[i][j] < 1 || caras[i][j] > a) {
                            cout << "Error: El vértice debe estar entre 1 y " << a << "." << endl;
                            cin >> caras[i][j];
                        }
                    }
                    caras[i][c] = -1;
                }
            }
        }
        else if (opcion == 3) {
            if (a == 0) {
                cout << "\nNo hay datos ingresados aún." << endl;
            } else {
                cout << "\n#### Matriz de coordenadas ####\n";
                for (int i = 0; i < a; i++) {
                    cout << "Vértice " << i + 1 << ": x = " << matriz_coordenadas[i][0] << ", y = " << matriz_coordenadas[i][1] << ", z = " << matriz_coordenadas[i][2] << endl;
                }
                cout << "\n#### Caras ####\n";
                for (int i = 0; i < b; i++) {
                    cout << "Cara " << i + 1 << ": ";
                    for (int j = 0; j < 10 && caras[i][j] != -1; j++) {
                        cout << caras[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }
        else if (opcion == 4) {
            cout << "\nSaliendo del programa..." << endl;
            break;
        }
        else {
            cout << "\nOpción no válida, intenta de nuevo." << endl;
        }
    }
    return 0;
}
