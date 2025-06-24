#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"

#include <cstring>
#include <fstream>
#include <sstream>

fs::path solicitarArchivo() {
    fs::path nombre_archivo;

    while (true) {
        std::string entrada;
        std::cout << CIAN "Ingrese el nombre del archivo (o 'exit' para salir): " RESET_COLOR;
        std::cin >> entrada;

        if (entrada == "exit") {
            std::cout << BLANCO "Saliendo del programa...\n" RESET_COLOR;
            exit(0);
        }

        // Expansión de ~ al home del usuario
        if (!entrada.empty() && entrada[0] == '~') {

            #ifdef _WIN32
                const char* home = std::getenv("USERPROFILE");
            #else
                const char* home = std::getenv("HOME");
            #endif

            if (home) entrada.replace(0, 1, home);
        }

        nombre_archivo = fs::path(entrada); // Convertir la entrada a fs::path
        
        if (!fs::exists(nombre_archivo)) {
            std::cerr << ROJO "Error: El archivo no existe. Intente nuevamente." RESET_COLOR << '\n';
        }
        else break;
    }

    nombre_archivo = fs::absolute(nombre_archivo); // Convertir a ruta absoluta

    return nombre_archivo;
}

void solicitarPatron(std::string& patron) {
    while (true) {
        std::string entrada;
        std::cout << CIAN "Ingrese el patron a buscar (o 'exit' para salir): " RESET_COLOR;
        std::cin >> entrada;

        if (entrada == "exit") {
            std::cout << BLANCO "Saliendo del programa...\n" RESET_COLOR;
            exit(0);
        }

        if (!entrada.empty()) {
            patron = entrada;
            break;
        } else {
            std::cerr << ROJO "Error: El patron no puede estar vacío. Intente nuevamente." RESET_COLOR << '\n';
        }
    }
}

void input(std::string& texto, std::string& patron) {    
    fs::path nombre_archivo = solicitarArchivo();
    
    // Abrir el archivo para extraer el contenido
    std::ifstream archivo(nombre_archivo, std::ios::in);
    if (!archivo.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo: " + nombre_archivo.string());
    }

    std::stringstream buffer;
    buffer << archivo.rdbuf();
    texto = buffer.str();

    solicitarPatron(patron);
}
