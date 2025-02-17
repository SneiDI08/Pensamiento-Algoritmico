#include <iostream>
#include "conio.h"
using namespace std;

double a;
double b;

int main() { 
  
  cout << "Coloca un numero\n";
  cin >> a;

  cout << "Coloca otro numero\n";
  cin >> b;

  cout << "La suma es: " << a+b;
  cout << "La resta es: " << a-b;
  cout << "La multiplicacion es: " << a*b;
  cout << "La division es: " << a/b << " y el resto es: " << a%b;


  return 0;
}
