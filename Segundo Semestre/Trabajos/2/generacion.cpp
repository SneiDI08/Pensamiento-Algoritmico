#include <iostream>
#include <vector>
using namespace std;
vector<double> Ecuacion(int x, int c, float r, int a) {
    vector<double> datos;
    double xn = (double)x / (double)c; 
    
    for (int i = 0; i < a; i++) {
        xn = r * xn * (1 - xn);
        datos.push_back(xn);
    }
    
    return datos;
}

int main() {
    int c;  
    int x;  
    int a;  
    float r;

    cout << "############# LA ECUACION LOGISTICA ##############" << endl;
    cout << "\nCapacidad maxima del ambiente: "; cin >> c;
    cout << "\nPoblacion inicial: "; cin >> x;
    cout << "\nTasa de crecimiento: "; cin >> r;
    cout << "\nNumero de generaciones: "; cin >> a;

    vector<double> resultados = Ecuacion(x, c, r, a);

    cout << "\nResultados normalizados (0 a 1):" << endl;
    for (int i = 0; i < resultados.size(); i++) {
        cout << "Generacion " << i+1 << ": " << resultados[i] << endl;
    }

    return 0;
}
