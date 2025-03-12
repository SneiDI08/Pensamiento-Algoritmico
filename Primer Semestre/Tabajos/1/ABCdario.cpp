#include <iostream>
using namespace std;
int main() {
    cout << "Letras minúsculas: ";
    for (char letra = 'a'; letra <= 'z'; ++letra) {
        cout << letra << " ";
    }
    cout << endl;

    cout << "Letras mayúsculas: ";
    for (char letra = 'A'; letra <= 'Z'; ++letra) {
        cout << letra << " ";
    }
    cout << endl;

    return 0;
}
