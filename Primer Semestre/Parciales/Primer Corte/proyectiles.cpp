#include <iostream>
using namespace std;//El using namespace std se usa para no tener que escribir std:: antes de elementos que pertenecen al espacio de nombres

int main(){
    const int a = 120, b = 100, c = 80 ; //Aqui definimos las variables de velocidad de cada hechizo como usualmente lo hariamos, pero en este caso definimos "cons" lo cual evita que el valor de la variable sea modificada dentro del programa 
    int x;
    int d;
    
    cout<<"Mago de Aetheria, has entrado en una pelea contra unos enemigos de la tierra"<<endl;

    cout<<"¿A que distancia se encuentra tu enemigo?"<<endl;
    cout<<"Distancia: ";
    cin>>d;
    int e=0;
        
    while (e<1 || e>3){ //Este bloque de codigo hace que el usuario solo sea incapaz de digitar opciones incorrectas.
    
        cout<<"Elige un hechizo para combatir"<<endl;
        cout<<"1. Hechizo de fuego (Largo alcance)"<<endl;
        cout<<"2. Hechizo de hielo (Largo alcance)"<<endl;
        cout<<"3. Hechizo de veneno (Largo alcance)"<<endl;
    
        cin>>e;
        if(e == 1){
        
            cout<<"Has elegido el hechizo de fuego"<<endl;
            cout<<"Disparando el hechizo de fuego"<<endl;
            x = d/a;
            cout<<"El hechizo de fuego ha demora en impactar al enemigo en "<<x<<" segundos";
        }
        else if(e == 2){
            cout<<"Has elegido el hechizo de hielo"<<endl;
            cout<<"Disparando el hechizo de hielo"<<endl;
            x = d/b;
            cout<<"El hechizo de hielo ha demora en impactar al enemigo en "<<x<< " segundos";
        }
        else if(e == 3){
            cout<<"Has elegido el hechizo de veneno"<<endl;
            cout<<"Disparando el hechizo de veneno"<<endl;
            x = d/c;
            cout<<"El hechizo de veneno ha demora en impactar al enemigo en "<<x<< " segundos";
        }
        else{
            cout<<"Elige un hechizo valido"<<endl;
        }
    }
  return 0;
}
