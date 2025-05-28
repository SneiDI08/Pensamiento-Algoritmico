#include "clases.h"

using namespace std; 

ataque::ataque(string nombre_ataque, int poder_ataque, int uso)
    : nombre(nombre_ataque), poder(poder_ataque), uso(uso) {
}

papumon::papumon(string nombre, string tipo, int vida, int defensa, int aguante, vector<ataque> ataques)
    : nombre(nombre), tipo(tipo), vida(vida), defensa(defensa), aguante(aguante), ataques(ataques) {
}


vector<ataque> ataques_viento() {
    return {
        ataque("Ráfaga Celeste", 15, 5),
        ataque("Viento Cortante", 20, 7),
        ataque("Torbellino Fantasma", 22, 10),
        ataque("Neblina Tempestad", 30, 15)
    };
}

vector<ataque> ataques_fuego() {
    return {
        ataque("Llama Ardiente", 15, 5),
        ataque("Lluvia de Fuego", 20, 7),
        ataque("Explosión Flamígera", 22, 10),
        ataque("Tormenta de Llamas", 32, 17)
    };
}

vector<ataque> ataques_agua() {
    return {
        ataque("Chorro de Agua", 15, 5),
        ataque("Tormenta de Agua", 20, 7),
        ataque("Maremoto", 22, 10),
        ataque("Oleada Salvaje", 30, 15)
    };
}

vector<ataque> ataques_tierra() {
    return {
        ataque("Terremoto", 15, 5),
        ataque("Roca Afilada", 20, 7),
        ataque("Desierto Enfurecido", 22, 10),
        ataque("Tormenta de Tierra", 32, 17)
    };
}

vector<ataque> ataques_normal() {
    return {
        ataque("Golpe Normal", 15, 5),
        ataque("Puño Feroz", 20, 7),
        ataque("Puño Desgarrador", 22, 10),
        ataque("Golpe Crítico", 30, 15)
    };
}

vector<papumon> papumones() {
    return {
        papumon("Ignivorax", "Fuego", 100, 5, 30, ataques_fuego()),
        papumon("Aquaflare", "Agua", 100, 5, 30, ataques_agua()),
        papumon("Terraclaw", "Tierra", 100, 5, 30, ataques_tierra()),
        papumon("Ventisca", "Viento", 100, 5,30, ataques_viento()),
        papumon("Normalis", "Normal", 100, 5,30, ataques_normal()),
        papumon("Flamemur", "Fuego", 100, 5, 30, ataques_fuego()),
        papumon("Pyroscale", "Fuego", 100, 5, 30, ataques_fuego()),
        papumon("Cratonix", "Tierra", 100, 5, 30, ataques_tierra()),
        papumon("Rocazor", "Tierra", 100, 5, 30, ataques_tierra()),
        papumon("Zephyroth", "Viento", 100, 5, 30, ataques_viento()),
        papumon("Galevore", "Viento", 100, 5, 30, ataques_viento()),
        papumon("Vivantor", "Normal", 100, 5, 30, ataques_normal()),
        papumon("Andrew", "Normal", 100, 5, 30, ataques_normal())
    };
}
