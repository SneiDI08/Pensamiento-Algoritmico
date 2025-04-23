#include <iostream>
using namespace std;

int main()
{
    int d = 6;
    int n;
    int p = 0;
    int lista [d];
    
    
    for (int i = 0; i <= 6; i++){
        
        cout << "Ingresa la temperatura";
        cin >> n;
        lista[i] = n;
        
    }
    
    cout << "\n\n###PROMEDIO DE TEMPERATURA DE TU SEMANA###\n\n";
    
    for (int i = 0; i <= 6; i++){
        
        p += lista[i];
        
    }
    p = p/7;
    cout << p;
    
    if (p > 30){
        
        cout << "\nHa sido una semana calurosa.";
        
    }
    else {
        
        cout << "\nHa sido una semana muy fria";
        
    }
    return 0;
}
