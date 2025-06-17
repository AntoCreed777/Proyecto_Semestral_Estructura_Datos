#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"
#include "linenoise.h"

#include <cstring>
#include <sys/select.h>

#define ARCHIVO_HISTORY_FILES "history_files.txt"
#define ARCHIVO_HISTORY_PATRON "history_patron.txt"

void completionArchivo(const char *buf, linenoiseCompletions *lc) {
    std::string prefix(buf);
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.find(prefix) == 0) {
                linenoiseAddCompletion(lc, filename.c_str());
            }
        }
    }
}

void completionPatron(const char *buf, linenoiseCompletions *lc) {
    // Sugerencias de patrones comunes
    if (strlen(buf) == 0) {
        linenoiseAddCompletion(lc, "Hola");
        linenoiseAddCompletion(lc, "Mundo");
    }
}

char* hintsArchivo(const char* buf, int* color, int* bold) {
    *color = 36; *bold = 0;
    return nullptr;
}

char* hintsPatron(const char* buf, int* color, int* bold) {
    *color = 35; *bold = 0;
    return nullptr;
}

void solicitarArchivo(fs::path& nombre_archivo) {
    // --- Inicialización de callbacks y carga de historial para linenoise (archivos) ---
    linenoiseHistoryFree();     // Limpiar historial en memoria para evitar mezclar los historiales
    linenoiseHistoryLoad(ARCHIVO_HISTORY_FILES);        // Cargar historial de archivos
    linenoiseSetCompletionCallback(completionArchivo);  // Autocompletado de archivos
    linenoiseSetHintsCallback(hintsArchivo);            // Sugerencias de color para archivos
    // -------------------------------------------------------------------------------

    while (true) {
        char* input = linenoise(CIAN "Ingrese el nombre del archivo (o 'exit' para salir): " RESET_COLOR);
        if (input == NULL) break;

        std::string entrada(input);
        linenoiseFree(input);

        if (entrada == "exit") {
            std::cout << BLANCO "Saliendo del programa...\n" RESET_COLOR;
            linenoiseHistorySave(ARCHIVO_HISTORY_FILES);
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
        if (fs::exists(nombre_archivo)) {
            nombre_archivo = fs::absolute(nombre_archivo); // Convertir a ruta absoluta
            linenoiseHistoryAdd(entrada.c_str());
            break;
        } else {
            std::cerr << ROJO "Error: El archivo no existe. Intente nuevamente." RESET_COLOR << '\n';
        }
    }

    /* Save the history on disk. */
    if (linenoiseHistorySave(ARCHIVO_HISTORY_FILES) == -1) {
        throw std::runtime_error("No se pudo guardar el historial de archivos");
    }
}

void solicitarPatron(std::string& patron) {
    // --- Inicialización de callbacks y carga de historial para linenoise (archivos) ---
    linenoiseHistoryFree();     // Limpiar historial en memoria para evitar mezclar los historiales
    linenoiseHistoryLoad(ARCHIVO_HISTORY_PATRON);        // Cargar historial de archivos
    linenoiseSetCompletionCallback(completionArchivo);  // Autocompletado de archivos
    linenoiseSetHintsCallback(hintsArchivo);            // Sugerencias de color para patrones
    // -------------------------------------------------------------------------------
    
    while (true) {
        char* input = linenoise(CIAN "Ingrese el patrón a buscar (o 'exit' para salir): " RESET_COLOR);
        if (!input) break;

        std::string entrada(input);
        linenoiseFree(input);

        if (entrada == "exit") {
            std::cout << BLANCO "Saliendo del programa...\n" RESET_COLOR;
            linenoiseHistorySave(ARCHIVO_HISTORY_PATRON);
            exit(0);
        }

        if (!entrada.empty()) {
            patron = entrada;
            linenoiseHistoryAdd(entrada.c_str());
            break;
        } else {
            std::cerr << ROJO "Error: El patrón no puede estar vacío. Intente nuevamente." RESET_COLOR << '\n';
        }
    }

    /* Save the history on disk. */
    if (linenoiseHistorySave(ARCHIVO_HISTORY_PATRON) == -1) {
        throw std::runtime_error("No se pudo guardar el historial de patrones");
    }
}

void input(fs::path& nombre_archivo, std::string& patron) {    
    solicitarArchivo(nombre_archivo);
    solicitarPatron(patron);
}
