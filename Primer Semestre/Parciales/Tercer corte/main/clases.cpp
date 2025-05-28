#include "clases.h"

using namespace std;

ataque::ataque(string nombre_ataque, int poder_ataque, int uso)
    : nombre(nombre_ataque), poder(poder_ataque), uso(uso) {
}

// Updated constructor to accept ascii_art
papumon::papumon(string nombre, string tipo, int vida, int defensa, int aguante, vector<ataque> ataques, vector<string> ascii_art)
    : nombre(nombre), tipo(tipo), vida(vida), defensa(defensa), aguante(aguante), ataques(ataques), ascii_art(ascii_art) {
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
};

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
    // Define ASCII art for each Papumon
    vector<string> ignivorax_art = {
        "  /\\_/\\  ",
        " ( o.o ) ",
        "  > ^ <  ",
        " (  =  ) ",
        "  \\_ _/  ",
        "   / \\   ",
        "  `---'  "
    };

    vector<string> aquaflare_art = {
        "   _ _   ",
        "  / o \\  ",
        " (  _  ) ",
        "  \\_=_/  ",
        "  /   \\  ",
        " /_____\\ ",
        " `-----' "
    };

    vector<string> terraclaw_art = {
        "   .--.  ",
        "  /    \\ ",
        " | O  O |",
        " |  __  |",
        "  \\_--_/",
        "  /    \\ ",
        "  `----' "
    };

    vector<string> ventisca_art = {
        "   .--.  ",
        "  / __ \\ ",
        " ( (__) )",
        "  \\ \\__/ ",
        "   \\__ \\ ",
        "    \\  \\ ",
        "     \\_/ "
    };

    vector<string> normalis_art = {
        "      .--.",
        "     |o_o |",
        "     |:_/ |",
        "    //   \\ \\",
        "   (|     | )",
        "  /'\\_   _/`\\",
        "  \\___)=(___/"
    };

    // Use a generic art for the rest if you don't define unique ones
    vector<string> generic_art = {
        "  _ _ _  ",
        " ( o o ) ",
        "  \\   /  ",
        "   \\ /   ",
        "    V    ",
        "   / \\   ",
        "  /   \\  "
    };

    return {
        papumon("Ignivorax", "Fuego", 100, 5, 30, ataques_fuego(), ignivorax_art),
        papumon("Aquaflare", "Agua", 100, 5, 30, ataques_agua(), aquaflare_art),
        papumon("Terraclaw", "Tierra", 100, 5, 30, ataques_tierra(), terraclaw_art),
        papumon("Ventisca", "Viento", 100, 5, 30, ataques_viento(), ventisca_art),
        papumon("Normalis", "Normal", 100, 5, 30, ataques_normal(), normalis_art),
        papumon("Flamemur", "Fuego", 100, 5, 30, ataques_fuego(), generic_art), 
        papumon("Pyroscale", "Fuego", 100, 5, 30, ataques_fuego(), generic_art), 
        papumon("Cratonix", "Tierra", 100, 5, 30, ataques_tierra(), generic_art), 
        papumon("Rocazor", "Tierra", 100, 5, 30, ataques_tierra(), generic_art), 
        papumon("Zephyroth", "Viento", 100, 5, 30, ataques_viento(), generic_art), 
        papumon("Galevore", "Viento", 100, 5, 30, ataques_viento(), generic_art), 
        papumon("Vivantor", "Normal", 100, 5, 30, ataques_normal(), generic_art), 
        papumon("Andrew", "Normal", 100, 5, 30, ataques_normal(), generic_art) 
    };
}