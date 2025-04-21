#include <iostream>
using namespace std;

int main() {
    int variable = 5;

    int* aspersand = &variable;      // aspersand ahora es un puntero a entero
    int asterisk = *aspersand;       // asterisk toma el valor apuntado (5)
    int asterisk2 = *&variable;      // también toma el valor 5

    cout << "Dirección de variable: " << &variable << endl;
    cout << "Valor de variable: " << variable << endl;
    cout << "Valor desde *aspersand: " << asterisk << endl;
    cout << "Valor desde *&variable: " << asterisk2 << endl;

    return 0;
}
