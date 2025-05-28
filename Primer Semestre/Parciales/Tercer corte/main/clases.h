#ifndef CLASES_H
#define CLASES_H

#include <string>
#include <vector>

class ataque {
public:
    std::string nombre;
    int poder;
    int uso;

    ataque(std::string nombre_ataque, int poder_ataque, int uso);
};

class papumon {
public:
    std::string nombre;
    std::string tipo;
    int vida;
    int defensa;
    int aguante;
    std::vector<ataque> ataques;
    std::vector<std::string> ascii_art; 

    papumon(std::string nombre, std::string tipo, int vida, int defensa, int aguante, std::vector<ataque> ataques, std::vector<std::string> ascii_art); // Updated constructor
};


std::vector<ataque> ataques_viento();
std::vector<ataque> ataques_fuego();
std::vector<ataque> ataques_agua();
std::vector<ataque> ataques_tierra();
std::vector<ataque> ataques_normal();
std::vector<papumon> papumones();

#endif