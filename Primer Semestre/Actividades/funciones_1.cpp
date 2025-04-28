//Para que sirve las funciones: Construir a partir de piezas pequeñas o modulos, los cuales son mas manejables que el programa original.
//Hace que el desarrollo sea mas facil y rapido, ademas de que se puede reutilizar el codigo.

#include <iostream>
using namespace std;

//<Tipo> <Nombre>(<Parametros>){<Cuerpo>}
    //Tipo: int, float, double, char, string, void, etc.
    //Nombre: Nombre de la funcion.
    //Parametros: Variables que se pasan a la funcion.
    //Cuerpo: Codigo que se ejecuta cuando se llama a la funcion.
int suma (int a, int b){
    return a + b;
}

int main() {

    cout << "Suma: " << suma(5, 3);
    
    return 0;
}
