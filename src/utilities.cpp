#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"

void solicitarArchivo(fs::path& nombre_archivo) {
    while (true) {
        std::cout << "Ingrese el nombre del archivo (o 'exit' para salir): ";
        std::string entrada;
        std::getline(std::cin, entrada);

        if (entrada == "exit") {
            std::cout << "Saliendo del programa...\n";
            exit(0);
        }

        nombre_archivo = entrada; // Convertir la entrada a fs::path
        if (fs::exists(nombre_archivo)) {
            nombre_archivo = fs::absolute(nombre_archivo); // Convertir a ruta absoluta
            break;
        } else {
            std::cerr << ROJO "Error: El archivo no existe. Intente nuevamente." RESET_COLOR << '\n';
        }
    }
}

void solicitarPatron(std::string& patron) {
    while (true) {
        std::cout << "Ingrese el patrón a buscar (o 'exit' para salir): ";
        std::getline(std::cin, patron);

        if (patron == "exit") {
            std::cout << "Saliendo del programa...\n";
            exit(0);
        }

        if (!patron.empty()) {
            break;
        } else {
            std::cerr << ROJO "Error: El patrón no puede estar vacío. Intente nuevamente." RESET_COLOR << '\n';
        }
    }
}

void input(fs::path& nombre_archivo, std::string& patron) {
    solicitarArchivo(nombre_archivo);
    solicitarPatron(patron);
}
