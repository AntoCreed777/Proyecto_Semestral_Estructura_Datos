#include "../include/definiciones.hpp"
#include "../include/medidor.hpp"

#include <mutex>
#include <set>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#include <unistd.h>
#endif

using json = nlohmann::json;

#define NOMBRE_CARPETA_JSON fs::path("test/json")

static json resultados_array = json::array();
static json resultado_actual;
static std::string medicion_nombre;
static std::string medicion_tipo;
static std::string medicion_patron;

static std::mutex mtx;
static size_t memoria_acumulada_kb = 0;

static void acumular_memoria(size_t mem_usada) {
    memoria_acumulada_kb += mem_usada;
}

size_t get_memory_usage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024;
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss; // KB en Linux
    }
    return 0;
#endif
}

std::chrono::high_resolution_clock::time_point iniciar_timer() {
    return std::chrono::high_resolution_clock::now();
}

std::chrono::high_resolution_clock::time_point detener_timer() {
    return std::chrono::high_resolution_clock::now();
}

std::chrono::duration<double, std::milli> calcular_duracion(
    std::chrono::high_resolution_clock::time_point inicio,
    std::chrono::high_resolution_clock::time_point fin
) {
    return std::chrono::duration<double, std::milli>(fin - inicio);
}

size_t obtener_memoria_maxima_kb() {
    return get_memory_usage();
}

void iniciar_medicion(const std::string& nombre, const std::string& tipo, const std::string& patron) {
    std::lock_guard<std::mutex> lock(mtx);
    medicion_nombre = nombre;
    medicion_tipo = tipo;
    medicion_patron = patron;

    resultado_actual = json::object();
    resultado_actual["Nombre"] = nombre;
    resultado_actual["Tipo"] = tipo;
}

void registrar_construccion(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion) {
    std::lock_guard<std::mutex> lock(mtx);
    resultado_actual["memoria_construccion_inicio_kb"] = mem_inicio;
    resultado_actual["memoria_construccion_fin_kb"] = mem_fin;
    size_t usada = (mem_fin > mem_inicio) ? mem_fin - mem_inicio : 0;
    resultado_actual["memoria_construccion_usada_kb"] = usada;
    resultado_actual["tiempo_construccion_mili"] = duracion.count();

    acumular_memoria(usada);
}

void registrar_busqueda(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion, unsigned int ocurrencias) {
    std::lock_guard<std::mutex> lock(mtx);
    resultado_actual["memoria_busqueda_inicio_kb"] = mem_inicio;
    resultado_actual["memoria_busqueda_fin_kb"] = mem_fin;
    size_t usada = (mem_fin > mem_inicio) ? mem_fin - mem_inicio : 0;
    resultado_actual["memoria_busqueda_usada_kb"] = usada;
    resultado_actual["tiempo_busqueda_mili"] = duracion.count();

    acumular_memoria(usada);
}

void guardar_resultado() {
    std::lock_guard<std::mutex> lock(mtx);
    resultados_array.push_back(resultado_actual);
    resultado_actual = json::object();
}

void validar_carpeta_guardado() {
    if (!std::filesystem::exists(NOMBRE_CARPETA_JSON)) {
        if(!std::filesystem::create_directory(NOMBRE_CARPETA_JSON)){
            throw std::runtime_error("La carpeta no pudo ser creada: " + NOMBRE_CARPETA_JSON.string());
        }
    }

    if (!std::filesystem::is_directory(NOMBRE_CARPETA_JSON)) {
        throw std::runtime_error("La ruta para guardar los tests ya existe y no es una carpeta: " + NOMBRE_CARPETA_JSON.string());
    }
}

void guardar_resultados_finales(const std::string& nombre_archivo, const std::string& patron, unsigned int ocurrencias, size_t /*memoria_maxima_kb*/) {
    std::lock_guard<std::mutex> lock(mtx);

    std::string clave = "patron: " + patron
                      + ", ocurrencias: " + std::to_string(ocurrencias)
                      + ", memoria_total_usada_kb: " + std::to_string(memoria_acumulada_kb);

    json salida;
    salida[clave] = resultados_array;

    try {
        validar_carpeta_guardado();
    } catch (const std::exception &e) {
        throw e;
    }

    fs::path archivo = NOMBRE_CARPETA_JSON / (nombre_archivo + ".json");
    std::ofstream out(archivo);
    if (!out) {
        throw std::runtime_error("Error abriendo archivo " + archivo.string() + " para escritura\n");
    }

    out << std::setw(4) << salida << std::endl;
    out.close();

    resultados_array.clear();
    memoria_acumulada_kb = 0;
}

// Función para medir algoritmo
unsigned int medir_algoritmo(const std::string& nombre, unsigned int(*func)(const std::string&, const std::string&), 
                            const std::string& texto, const std::string& patron) {
    try {
        iniciar_medicion(nombre, "Algoritmo", patron);

        size_t mem_inicio = get_memory_usage();
        auto t_inicio = iniciar_timer();

        unsigned int ocurrencias = func(texto, patron);

        auto t_fin = detener_timer();
        size_t mem_fin = get_memory_usage();

        registrar_construccion(0, 0, std::chrono::duration<double, std::milli>(0)); // sin construcción
        registrar_busqueda(mem_inicio, mem_fin, calcular_duracion(t_inicio, t_fin), ocurrencias);
        guardar_resultado();

        return ocurrencias;
    } catch (...) {
        iniciar_medicion(nombre, "Algoritmo", patron);
        registrar_construccion(0, 0, std::chrono::duration<double, std::milli>(0));
        registrar_busqueda(0, 0, std::chrono::duration<double, std::milli>(0), 0);
        guardar_resultado();
        return 0;
    }
}

// Función para medir estructura
unsigned int medir_estructura(const std::string& nombre, std::function<std::unique_ptr<BaseStructure>(const std::string&)> constructor,
                             const std::string& texto, const std::string& patron) {
    try {
        iniciar_medicion(nombre, "Estructura", patron);

        size_t mem_inicio_const = get_memory_usage();
        auto t_inicio_const = iniciar_timer();

        auto estructura = constructor(texto);

        auto t_fin_const = detener_timer();
        size_t mem_fin_const = get_memory_usage();

        auto t_inicio_busq = iniciar_timer();
        unsigned int ocurrencias = estructura->buscar(patron);
        auto t_fin_busq = detener_timer();
        size_t mem_fin_busq = get_memory_usage();

        registrar_construccion(mem_inicio_const, mem_fin_const, calcular_duracion(t_inicio_const, t_fin_const));
        registrar_busqueda(mem_fin_const, mem_fin_busq, calcular_duracion(t_inicio_busq, t_fin_busq), ocurrencias);
        guardar_resultado();

        return ocurrencias;
    } catch (...) {
        iniciar_medicion(nombre, "Estructura", patron);
        registrar_construccion(0, 0, std::chrono::duration<double, std::milli>(0));
        registrar_busqueda(0, 0, std::chrono::duration<double, std::milli>(0), 0);
        guardar_resultado();
        return 0;
    }
}