//Primer ejercicion

/*
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
*/

// Hallar el procentajede un producto


/*
#include <iostream>
using namespace std;

int p = 1500000;
float d = 0.15;
int t = p*d; 

int main(){

  cout << "El precio del compu es: " << p << endl;
  cout << "El descuento es: " << t << endl;
  cout << "El precio final es: " << p-t;
  return 0;
  
}
*/


// Con una variable de valor 10 aumentar 5, reducimos 3, multiplicamos por 3 y dividimos entre 4.

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
