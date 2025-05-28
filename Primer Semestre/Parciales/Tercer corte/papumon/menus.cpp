#include "menus.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

void draw_papumon_ascii(const papumon& p, int x_offset);
void draw_health_bar(int current_hp, int max_hp, int length, int x_offset);
void display_battle_state(const papumon& p1, const papumon& p2, int turno, const string& player1_name, const string& player2_name);


void menu_principal() {
    bool continuar = true;
    int opcion;

    do {
        system("cls");

        cout << "\t\t\t###############" << endl;
        cout << "\t\t\t# PAPUMON :v  #" << endl;
        cout << "\t\t\t###############" << endl;

        cout << "\n\t1. Iniciar Juego (Vs. Jugador)" << endl;
        cout << "\t2. Iniciar Juego (Vs. IA)" << endl;
        cout << "\t3. Salir" << endl;
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
        case 2: {
            auto equipo_jugador = menu_seleccion("JUGADOR");
            vector<papumon> todosPapumones = papumones();
            vector<papumon> equipo_ia;

            random_device rd;
            mt19937 g(rd());
            shuffle(todosPapumones.begin(), todosPapumones.end(), g);

            for (int i = 0; i < 5; ++i) {
                equipo_ia.push_back(todosPapumones[i]);
            }
            cout << "\nLa IA ha seleccionado a sus Papumones.\n";
            system("pause");
            menu_batalla_vs_ia(equipo_jugador, equipo_ia);
            system("pause");
            break;
        }
        case 3:
            cout << "\n\tSaliendo del juego..." << endl;
            continuar = false;
            break;

        default:
            cout << "\n\tOpción no válida. Intente de nuevo." << endl;
            system("pause");
            break;
        }
    } while (continuar);
}

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

        int opcion;
        cout << "\nSeleccion #" << seleccionados.size() + 1 << ": ";
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
            system("pause");
        }
        else {
            seleccionados.push_back(todosPapumones[opcion - 1]);
            cout << todosPapumones[opcion - 1].nombre << " agregado a tu equipo.\n";
            system("pause");
        }
    }
    return seleccionados;
}


void menu_batalla(vector<papumon>& equipo1, vector<papumon>& equipo2) {
    int turno = 1;
    int indice1 = 0, indice2 = 0;
    const int MAX_HP = 100;

    while (indice1 < equipo1.size() && indice2 < equipo2.size()) {
        system("cls");

        auto& p1 = equipo1[indice1];
        auto& p2 = equipo2[indice2];

        display_battle_state(p1, p2, turno, "JUGADOR 1", "JUGADOR 2");

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
            cout << "\nElige una opcion (1-" << atacante.ataques.size() << "): ";
            if (!(cin >> eleccion)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada inválida. Intenta de nuevo.\n";
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                display_battle_state(p1, p2, turno, "JUGADOR 1", "JUGADOR 2");
                continue;
            }

            if (eleccion == 0) {
                if (atacante.aguante >= 50) {
                    cout << "Tienes mucho aguante.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                    system("cls");
                    display_battle_state(p1, p2, turno, "JUGADOR 1", "JUGADOR 2");
                    continue;
                }
                else {
                    atacante.aguante += 12;
                    atacante.aguante = min(atacante.aguante, 50);
                    cout << atacante.nombre << " ha curado su aguante.\n";
                    this_thread::sleep_for(chrono::seconds(2));
                    break;
                }
            }

            if (eleccion < 1 || eleccion > static_cast<int>(atacante.ataques.size())) {
                cout << "Opción inválida. Intenta de nuevo.\n";
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                display_battle_state(p1, p2, turno, "JUGADOR 1", "JUGADOR 2");
                continue;
            }

            if (atacante.aguante < atacante.ataques[eleccion - 1].uso) {
                cout << atacante.nombre << " se ha quedado sin aguante y no puede atacar.\n";
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                display_battle_state(p1, p2, turno, "JUGADOR 1", "JUGADOR 2");
                continue;
            }

            int daño = max(0, atacante.ataques[eleccion - 1].poder - defensor.defensa);
            atacante.aguante -= atacante.ataques[eleccion - 1].uso;
            defensor.vida -= daño;
            defensor.vida = max(0, defensor.vida);

            cout << atacante.nombre << " usó " << atacante.ataques[eleccion - 1].nombre
                << " y causó " << daño << " de daño.\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }

        if (p1.vida <= 0) {
            cout << p1.nombre << " fue derrotado!\n";
            this_thread::sleep_for(chrono::seconds(2));
            indice1++;
        }

        if (p2.vida <= 0) {
            cout << p2.nombre << " fue derrotado!\n";
            this_thread::sleep_for(chrono::seconds(2));
            indice2++;
        }

        if (p1.vida > 0 && p2.vida > 0) {
            turno++;
        }
        else {
            turno = 1;
        }
    }

    system("cls");
    cout << "\n¡" << ((indice1 >= equipo1.size()) ? "JUGADOR 2" : "JUGADOR 1") << " gana la batalla!\n";
    this_thread::sleep_for(chrono::seconds(3));
}

void menu_batalla_vs_ia(vector<papumon>& equipo_jugador, vector<papumon>& equipo_ia) {
    int turno = 1;
    int indice_jugador = 0, indice_ia = 0;
    const int MAX_HP = 100;

    random_device rd;
    mt19937 gen(rd());

    while (indice_jugador < equipo_jugador.size() && indice_ia < equipo_ia.size()) {
        system("cls");

        auto& jugador_papumon = equipo_jugador[indice_jugador];
        auto& ia_papumon = equipo_ia[indice_ia];

        display_battle_state(jugador_papumon, ia_papumon, turno, "JUGADOR", "IA");

        if (turno % 2 != 0) {
            auto& atacante = jugador_papumon;
            auto& defensor = ia_papumon;

            while (true) {
                cout << "\nTurno de JUGADOR (" << atacante.nombre << ")\n";
                cout << "ATAQUES:\n";
                for (size_t i = 0; i < atacante.ataques.size(); i++) {
                    cout << i + 1 << ". " << atacante.ataques[i].nombre
                        << " (Poder: " << atacante.ataques[i].poder << ", Uso: " << atacante.ataques[i].uso << ")\n";
                }
                cout << "Curar aguante (0)\n";
                int eleccion;
                cout << "\nElige una opcion (1-" << atacante.ataques.size() << "): ";
                if (!(cin >> eleccion)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Entrada inválida. Intenta de nuevo.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                    system("cls");
                    display_battle_state(jugador_papumon, ia_papumon, turno, "JUGADOR", "IA");
                    continue;
                }

                if (eleccion == 0) {
                    if (atacante.aguante >= 50) {
                        cout << "Tienes mucho aguante.\n";
                        this_thread::sleep_for(chrono::seconds(1));
                        system("cls");
                        display_battle_state(jugador_papumon, ia_papumon, turno, "JUGADOR", "IA");
                        continue;
                    }
                    else {
                        atacante.aguante += 12;
                        atacante.aguante = min(atacante.aguante, 50);
                        cout << atacante.nombre << " ha curado su aguante.\n";
                        this_thread::sleep_for(chrono::seconds(2));
                        break;
                    }
                }

                if (eleccion < 1 || eleccion > static_cast<int>(atacante.ataques.size())) {
                    cout << "Opción inválida. Intenta de nuevo.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                    system("cls");
                    display_battle_state(jugador_papumon, ia_papumon, turno, "JUGADOR", "IA");
                    continue;
                }

                if (atacante.aguante < atacante.ataques[eleccion - 1].uso) {
                    cout << atacante.nombre << " se ha quedado sin aguante y no puede atacar.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                    system("cls");
                    display_battle_state(jugador_papumon, ia_papumon, turno, "JUGADOR", "IA");
                    continue;
                }

                int daño = max(0, atacante.ataques[eleccion - 1].poder - defensor.defensa);
                atacante.aguante -= atacante.ataques[eleccion - 1].uso;
                defensor.vida -= daño;
                defensor.vida = max(0, defensor.vida);

                cout << atacante.nombre << " usó " << atacante.ataques[eleccion - 1].nombre
                    << " y causó " << daño << " de daño.\n";
                this_thread::sleep_for(chrono::seconds(2));
                break;
            }
        }
        else {
            auto& atacante = ia_papumon;
            auto& defensor = jugador_papumon;

            cout << "\nTurno de la IA (" << atacante.nombre << ")\n";
            this_thread::sleep_for(chrono::seconds(1));

            bool attacked = false;
            if (atacante.aguante < 20) {
                if (atacante.aguante < 50) {
                    atacante.aguante += 12;
                    atacante.aguante = min(atacante.aguante, 50);
                    cout << atacante.nombre << " ha curado su aguante.\n";
                    attacked = true;
                }
            }

            if (!attacked) {
                vector<int> usable_attacks;
                for (size_t i = 0; i < atacante.ataques.size(); ++i) {
                    if (atacante.aguante >= atacante.ataques[i].uso) {
                        usable_attacks.push_back(i);
                    }
                }

                if (!usable_attacks.empty()) {
                    uniform_int_distribution<> distrib(0, usable_attacks.size() - 1);
                    int chosen_attack_index = usable_attacks[distrib(gen)];

                    int daño = max(0, atacante.ataques[chosen_attack_index].poder - defensor.defensa);
                    atacante.aguante -= atacante.ataques[chosen_attack_index].uso;
                    defensor.vida -= daño;
                    defensor.vida = max(0, defensor.vida);

                    cout << atacante.nombre << " usó " << atacante.ataques[chosen_attack_index].nombre
                        << " y causó " << daño << " de daño.\n";
                    attacked = true;
                }
                else {
                    if (atacante.aguante < 50) {
                        atacante.aguante += 12;
                        atacante.aguante = min(atacante.aguante, 50);
                        cout << atacante.nombre << " no pudo atacar y curó su aguante.\n";
                        attacked = true;
                    }
                    else {
                        cout << atacante.nombre << " no pudo atacar ni curar.\n";
                    }
                }
            }
            this_thread::sleep_for(chrono::seconds(2));
        }

        if (jugador_papumon.vida <= 0) {
            cout << jugador_papumon.nombre << " fue derrotado!\n";
            this_thread::sleep_for(chrono::seconds(2));
            indice_jugador++;
        }

        if (ia_papumon.vida <= 0) {
            cout << ia_papumon.nombre << " fue derrotado!\n";
            this_thread::sleep_for(chrono::seconds(2));
            indice_ia++;
        }

        if (jugador_papumon.vida > 0 && ia_papumon.vida > 0) {
            turno++;
        }
        else {
            turno = 1;
        }
    }

    system("cls");
    cout << "\n¡" << ((indice_jugador >= equipo_jugador.size()) ? "IA" : "JUGADOR") << " gana la batalla!\n";
    this_thread::sleep_for(chrono::seconds(3));
}

void draw_papumon_ascii(const papumon& p, int x_offset) {
    for (const string& line : p.ascii_art) {
        cout << string(x_offset, ' ') << line << endl;
    }
}

void draw_health_bar(int current_hp, int max_hp, int length, int x_offset) {
    int filled_length = static_cast<int>(static_cast<double>(current_hp) / max_hp * length);
    cout << string(x_offset, ' ');
    cout << "[";
    for (int i = 0; i < length; ++i) {
        if (i < filled_length) {
            cout << "#";
        }
        else {
            cout << "-";
        }
    }
    cout << "]";
    cout << " " << current_hp << "/" << max_hp << " HP";
}

void display_battle_state(const papumon& p1, const papumon& p2, int turno, const string& player1_name, const string& player2_name) {
    const int ARENA_WIDTH = 80;
    const int PAPUMON_DISPLAY_WIDTH = ARENA_WIDTH / 2;
    const int PAPUMON_ART_HEIGHT = 7;

    cout << string(ARENA_WIDTH, '=') << endl;
    cout << string((ARENA_WIDTH - string("######### PAPUMON BATTLE ARENA #########").length()) / 2, ' ') << "######### PAPUMON BATTLE ARENA #########" << endl;
    cout << string(ARENA_WIDTH, '=') << endl;
    cout << "\n";

    string p1_name_line = player1_name + ": " + p1.nombre;
    string p2_name_line = player2_name + ": " + p2.nombre;

    cout << p1_name_line;
    cout << string(ARENA_WIDTH - p1_name_line.length() - p2_name_line.length(), ' ');
    cout << p2_name_line << endl;

    int health_bar_length = 20;
    int p1_hp_offset = (PAPUMON_DISPLAY_WIDTH - (health_bar_length + to_string(p1.vida).length() + to_string(100).length() + 6)) / 2;
    int p2_hp_offset = (PAPUMON_DISPLAY_WIDTH - (health_bar_length + to_string(p2.vida).length() + to_string(100).length() + 6)) / 2;

    draw_health_bar(p1.vida, 100, health_bar_length, p1_hp_offset);
    cout << string(ARENA_WIDTH - (p1_hp_offset + health_bar_length + to_string(p1.vida).length() + to_string(100).length() + 6) - (p2_hp_offset), ' ');
    draw_health_bar(p2.vida, 100, health_bar_length, p2_hp_offset);
    cout << endl;

    string p1_aguante_line = "Aguante: " + to_string(p1.aguante);
    string p2_aguante_line = "Aguante: " + to_string(p2.aguante);

    cout << p1_aguante_line;
    cout << string(ARENA_WIDTH - p1_aguante_line.length() - p2_aguante_line.length(), ' ');
    cout << p2_aguante_line << endl;

    for (int i = 0; i < PAPUMON_ART_HEIGHT; ++i) {
       
        string p1_art_line = (i < p1.ascii_art.size()) ? p1.ascii_art[i] : "";
        string p2_art_line = (i < p2.ascii_art.size()) ? p2.ascii_art[i] : "";

        int p1_line_offset = (PAPUMON_DISPLAY_WIDTH - p1_art_line.length()) / 2;
        int p2_line_offset = (PAPUMON_DISPLAY_WIDTH - p2_art_line.length()) / 2;

        cout << string(p1_line_offset, ' ') << p1_art_line;

        cout << string(ARENA_WIDTH - (p1_line_offset + p1_art_line.length()) - (p2_line_offset + p2_art_line.length()), ' ');
        cout << string(p2_line_offset, ' ') << p2_art_line << endl;
    }

    cout << "\n" << string(ARENA_WIDTH, '-') << endl;
    cout << string((ARENA_WIDTH - (string("TURNO #") + to_string(turno)).length()) / 2, ' ') << "TURNO #" << turno << endl;
    cout << string(ARENA_WIDTH, '-') << endl;
}