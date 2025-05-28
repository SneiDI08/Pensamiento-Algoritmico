#ifndef MENUS_H
#define MENUS_H

#include <vector>
#include <string>
#include "clases.h" 

using std::vector;
using std::string;

void menu_principal();
vector<papumon> menu_seleccion(const string& jugador);
void menu_batalla(vector<papumon>& equipo1, vector<papumon>& equipo2);
void menu_batalla_vs_ia(vector<papumon>& equipo_jugador, vector<papumon>& equipo_ia); // New declaration

#endif