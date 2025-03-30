#include <iostream>

using namespace std;

int main() {
    int a = 0, b = 0;
    int* matriz_coordenadas = nullptr;
    int* cantidad_vertices_por_cara = nullptr;
    int** matriz_caras = nullptr;
    int opcion;

    do {
        cout << "\n############################";
        cout << "\n#        MENÚ             #";
        cout << "\n############################";
        cout << "\n1. Ingresar vértices";
        cout << "\n2. Ingresar caras";
        cout << "\n3. Mostrar matrices";
        cout << "\n4. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\n¿Cuántos vértices necesitas?\nNúmero de vértices: ";
            while (!(cin >> a) || a <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Por favor, ingresa un número válido: ";
            }

            matriz_coordenadas = new int[a * 3];

            cout << "\nIngresa las coordenadas de los vértices:\n";
            for (int i = 0; i < a; i++) {
                cout << "Vértice " << i + 1 << "\nX: ";
                cin >> matriz_coordenadas[i * 3];
                cout << "Y: ";
                cin >> matriz_coordenadas[i * 3 + 1];
                cout << "Z: ";
                cin >> matriz_coordenadas[i * 3 + 2];
            }
        }
        else if (opcion == 2) {
            if (a == 0) {
                cout << "\nPrimero debes ingresar los vértices.";
                continue;
            }

            cout << "\n¿Cuántas caras necesitas?\nNúmero de caras: ";
            while (!(cin >> b) || b <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Por favor, ingresa un número válido: ";
            }

            cantidad_vertices_por_cara = new int[b];
            matriz_caras = new int*[b];

            for (int i = 0; i < b; i++) {
                cout << "Cantidad de vértices para la cara " << i + 1 << ": ";
                cin >> cantidad_vertices_por_cara[i];

                matriz_caras[i] = new int[cantidad_vertices_por_cara[i]];

                for (int j = 0; j < cantidad_vertices_por_cara[i]; j++) {
                    cout << "Vértice " << j + 1 << " (índice): ";
                    cin >> matriz_caras[i][j];
                }
            }
        }
        else if (opcion == 3) {
            if (a == 0) {
                cout << "\nNo hay datos ingresados aún.";
                continue;
            }

            cout << "\n#### Matriz de coordenadas ####\n";
            for (int i = 0; i < a; i++) {
                cout << "Vértice " << i + 1 << ": ";
                cout << "x = " << matriz_coordenadas[i * 3] << ", ";
                cout << "y = " << matriz_coordenadas[i * 3 + 1] << ", ";
                cout << "z = " << matriz_coordenadas[i * 3 + 2] << endl;
            }

            if (b > 0) {
                cout << "\n#### Matriz de caras ####\n";
                for (int i = 0; i < b; i++) {
                    cout << "Cara " << i + 1 << ": ";
                    for (int j = 0; j < cantidad_vertices_por_cara[i]; j++) {
                        cout << matriz_caras[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }
        else if (opcion == 4) {
            cout << "\nSaliendo del programa...";
        }
        else {
            cout << "\nOpción no válida, intenta de nuevo.";
        }

    } while (opcion != 4);

    delete[] matriz_coordenadas;
    delete[] cantidad_vertices_por_cara;
    for (int i = 0; i < b; i++) {
        delete[] matriz_caras[i];
    }
    delete[] matriz_caras;

    return 0;
}
