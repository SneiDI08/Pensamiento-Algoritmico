#include <iostream>
using namespace std;

int a = 10;

int main(){
  cout << "El valor de a es: " << a << endl;
  a += 5;
  cout << "El valor de a aumentado 5 es: " << a << endl;
  a -= 3;
  cout << "El valor de a reducido 3 es: " << a << endl;
  a *= 3;
  cout << "El valor de a multiplicado por 3 es: " << a << endl;
  a /= 4;
  cout << "El valor de a dividido entre 4 es: " << a << endl;

  return 0;
}
