#include "menus.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

//-----------------------------------
// MENÚ PRINCIPAL
//-----------------------------------
void menu_principal() {
    bool continuar = true;
    int opcion;

    do {
        system("cls");

        cout << "\t\t\t###############" << endl;
		cout << "\t\t\t# PAPUMON :'v #" << endl;
        cout << "\t\t\t###############" << endl;

        cout << "\n\t1. Iniciar Juego" << endl;
        cout << "\t2. Salir" << endl;
        cout << "\n\tElija una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }

        switch (opcion) {
        case 1: {
            auto equipo1 = menu_seleccion("JUGADOR 1");
            auto equipo2 = menu_seleccion("JUGADOR 2");
            menu_batalla(equipo1, equipo2);
            system("pause");
            break;
        }
        case 2:
            cout << "\n\tSaliendo del juego..." << endl;
            continuar = false;
            break;

        default:
            cout << "\n\tOpción no válida. Intente de nuevo." << endl;
            break;
        }
    } while (continuar);
}

//-----------------------------------
// MENÚ DE SELECCIÓN DE PAPUMONES
//-----------------------------------

vector<papumon> menu_seleccion(const string& jugador) {
    vector<papumon> seleccionados;
    vector<papumon> todosPapumones = papumones();

    while (seleccionados.size() < 5) {
        system("cls");
        cout << "\t\t\t################################" << endl;
        cout << "\t\t\t#           " << jugador << "          #" << endl;
        cout << "\t\t\t#    ESCOGE A TUS PAPUMONES    #" << endl;
        cout << "\t\t\t################################" << endl;
        cout << "\nLista de Papumones disponibles:\n" << endl;
        for (size_t i = 0; i < todosPapumones.size(); ++i) {
            cout << i + 1 << ". " << todosPapumones[i].nombre << " (Tipo: " << todosPapumones[i].tipo << ")" << endl;
        }
        cout << "0. Salir (NO PERMITIDO hasta elegir 5 papumones)\n";

        cout << "\nSeleccion #" << seleccionados.size() + 1 << ": ";
        int opcion;
        cin >> opcion;

        if (cin.fail() || opcion < 1 || opcion > static_cast<int>(todosPapumones.size())) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opción inválida. Intenta de nuevo.\n";
            system("pause");
            continue;
        }

        bool yaSeleccionado = false;
        for (const auto& p : seleccionados) {
            if (p.nombre == todosPapumones[opcion - 1].nombre) {
                yaSeleccionado = true;
                break;
            }
        }

        if (yaSeleccionado) {
            cout << "Ya seleccionaste a ese Papumon. Elige otro.\n";

        }
        else {
            seleccionados.push_back(todosPapumones[opcion - 1]);
            cout << todosPapumones[opcion - 1].nombre << " agregado a tu equipo.\n";

        }
    }
    return seleccionados;
}

//-----------------------------------
// MENÚ DE BATALLA
//-----------------------------------
void menu_batalla(vector<papumon>& equipo1, vector<papumon>& equipo2) {
    int turno = 1;
    int indice1 = 0, indice2 = 0;

    while (indice1 < equipo1.size() && indice2 < equipo2.size()) {
        system("cls");

        auto& p1 = equipo1[indice1];
        auto& p2 = equipo2[indice2];

        cout << "TURNO #" << turno << endl;
        cout << "-----------------------------\n";
        cout << "JUGADOR 1: " << p1.nombre << " (HP: " << p1.vida << ", Aguante: " << p1.aguante << ")\n";
        cout << "JUGADOR 2: " << p2.nombre << " (HP: " << p2.vida << ", Aguante: " << p2.aguante << ")\n";
        cout << "-----------------------------\n";

        auto& atacante = (turno % 2 != 0) ? p1 : p2;
        auto& defensor = (turno % 2 != 0) ? p2 : p1;
        string jugador_turno = (turno % 2 != 0) ? "JUGADOR 1" : "JUGADOR 2";

        while (true) {
            cout << "\nTurno de " << jugador_turno << " (" << atacante.nombre << ")\n";
            cout << "ATAQUES:\n";
            for (size_t i = 0; i < atacante.ataques.size(); i++) {
                cout << i + 1 << ". " << atacante.ataques[i].nombre
                    << " (Poder: " << atacante.ataques[i].poder << ", Uso: " << atacante.ataques[i].uso << ")\n";
            }
            cout << "Curar aguante (0)\n";
            int eleccion;
            cout << "\nElige un ataque (1-" << atacante.ataques.size() << "): ";
            if (!(cin >> eleccion)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada inválida. Intenta de nuevo.\n";
                continue;
            }

            if (eleccion == 0) {
                if (atacante.aguante >= 50) {
                    cout << "Tienes mucho aguante.";
                    continue;
                }
                else {
                    atacante.aguante += 12;
					atacante.aguante = min(atacante.aguante, 50);
                    cout << atacante.nombre << " ha curado su aguante.\n";
                    break;
                }
            }

            if (eleccion < 1 || eleccion > static_cast<int>(atacante.ataques.size())) {
                cout << "Opción inválida. Intenta de nuevo.\n";
                continue;
            }

            if (atacante.aguante < atacante.ataques[eleccion - 1].uso) {
                cout << atacante.nombre << " se ha quedado sin aguante y no puede atacar.\n";
                continue;
            }

            int daño = max(0, atacante.ataques[eleccion - 1].poder - defensor.defensa);
            atacante.aguante -= atacante.ataques[eleccion - 1].uso;
            defensor.vida -= daño;
            defensor.vida = max(0, defensor.vida);

            cout << atacante.nombre << " usó " << atacante.ataques[eleccion - 1].nombre
                << " y causó " << daño << " de daño.\n";
            break;
        }

        if (p1.vida <= 0) {
            cout << p1.nombre << " fue derrotado!\n";
            indice1++;
        }

        if (p2.vida <= 0) {
            cout << p2.nombre << " fue derrotado!\n";
            indice2++;
        }

        if (p1.vida > 0 && p2.vida > 0) {
            turno++;
        }

        system("pause");
    }

    cout << "\n¡" << ((indice1 >= equipo1.size()) ? "Jugador 2" : "Jugador 1") << " gana la batalla!\n";
}
