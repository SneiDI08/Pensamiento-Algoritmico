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
